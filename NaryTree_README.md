# NaryTree — turtle interpreter: L-system string → 3D branch model

**Stage 2 of 3** in the *branch-model state-estimation* project
(Elad Gips, Technion — Center for Agricultural Engineering Research).
See [`ARCHITECTURE.md`](./ARCHITECTURE.md) for how this repo fits into the
whole pipeline; this README is the standalone reference for *this* repo.

> **Scope:** the project's end goal is *whole-plant* state estimation vs
> measurements. NaryTree **already represents a whole tree** (an N-ary tree of
> branches) — the single-branch scoping lives in the estimator (`1DMLE`), not
> here. See `ARCHITECTURE.md` §2.

NaryTree takes the bracketed **turtle string** produced by
[`LSYS_PARA`](../LSYS_PARA) and interprets it into a concrete **3D structural
model of a branch**: two parallel N-ary trees — one of 3D *points* (nodes) and
one of *stream-lines* (the segments between nodes, each carrying an orientation
frame and a width). It then exports that model as solid geometry
(cones + spheres) for meshing / visualization.

In the language of the research write-up, this is the code that realizes a
branch as *"a collection of points with growth functions along the branch"* —
here, the geometric realization of one grown instance.

---

## 1. Where it sits

```
LSYS_PARA  ──►  NaryTree  ──►  1DMLE
(grammar)      (this repo)     (estimation)
```

* **Input:** a turtle string such as
  `F(0.02)+F(0.03)[--F(0.03)]+F(0.04)` — typically the file `LSYOUT.txt`
  emitted by LSYS_PARA.
* **Output:** text files of Altair/HyperMesh TCL commands describing the
  branch as solid cones (segments) and spheres (nodes) — ready to be built
  into a mesh or rendered.

---

## 2. Build & run

Requires only a C++14 compiler. No external dependencies.

```bash
cmake -S . -B build
cmake --build build
./build/narytree  [input.txt]  [streams_out.txt]  [points_out.txt]
```

All three paths are optional and fall back to the original hard-coded
defaults if omitted. Or compile by hand:

```bash
g++ -std=c++14 -Wall main.cpp point3D.cpp streamLine3DW.cpp -o narytree
```

> **Important:** build the **`W` variant** (`streamLine3DW.cpp`, which pulls in
> `streamLine3DW.h`). The non-`W` `streamLine3D.cpp/.h` is an earlier version
> **without** the `width` field and is intentionally *excluded* from the build;
> compiling both together produces duplicate `class streamLine3D` definitions.

---

## 3. Data model

### 3.1 `point3D` (`point3D.h` / `point3D.cpp`)

A 3D point that doubles as a 3D vector.

| Member | Meaning |
|---|---|
| `x, y, z` | coordinates |
| `w` | width / radius associated with the point (used at export) |
| `index` | node id, assigned during interpretation |

Key methods:

* `Rx / Ry / Rz(theta)` — rotate the vector about the global X/Y/Z axes.
* `MatrixRotate(M)` — rotate by a supplied 3×3 matrix.
* `norm() / normalize()` — length / in-place unit-normalization.
* `DotProd(p)` — dot product.
* `projection(p_hat)` — component of `this` along unit vector `p_hat`.
* `gramSh(vp)` — **Gram–Schmidt**: orthogonalize `this` against the vectors in
  `vp` (then re-normalize). This is how orthonormal orientation frames are built.
* `Distance(p)` — Euclidean distance to `p` (used to set cone lengths on export).
* `operator=` / copy-ctor copy `x,y,z,w` (note: `index` is intentionally reset
  to 0 by the copy-ctor — see *Known issues*).

### 3.2 `streamLine3D` (`streamLine3DW.h` / `streamLine3DW.cpp`)

A **directed segment with a local orientation frame** — the L-system "turtle"
state. One stream-line spans from its start point to its end point.

| Member | Meaning |
|---|---|
| `pI` | pointer to the **start** point (the incoming node) |
| `pE` | pointer to the **end** point (`NULL`/`0x0` until a child extends it) |
| `pH` | **Heading** unit vector — the direction the turtle faces |
| `pL` | **Left** unit vector |
| `pU` | **Up** unit vector |
| `w` | width (radius) of the segment |
| `index` | segment id |

`pH, pL, pU` form a right-handed orthonormal frame, constructed with `gramSh`.
The constructors accept various partial specifications (heading only, heading +
left, two endpoints, etc.) and complete the frame via Gram–Schmidt, falling
back to global axes when a supplied vector is degenerate.

Frame rotations (the turtle's turns):

* `RotH(theta)` — **roll** about Heading.
* `RotL(theta)` — **pitch** about Left.
* `RotU(theta)` — **yaw** about Up.
* `childStream(pE, parent, child, dist, w)` — set `pE = parent.pI + parent.pH*dist`,
  link it as the parent's end, and initialize `child` at `pE` inheriting the
  parent's frame and width. This is the "move forward and spawn the next
  segment" operation.

### 3.3 `node<T>` (`EtzNary.hpp`)

A generic **N-ary tree node** (`Etz` = "tree" in Hebrew). Template over the
payload `T`.

| Member | Meaning |
|---|---|
| `value` | payload (`point3D` or `streamLine3D`) |
| `children` | `vector<node*>` |
| `parent` | back-pointer |

Static / member operations:

* `newNode(value, parent)` — heap-allocate a node.
* `appendChild(parent, child)` — attach `child` under `parent` (guarded by
  `notMyPapa`, which walks ancestors to reject cycles).
* `isMember(root, x)` — is `x` in the subtree rooted at `root`?
* `copySubTree(root)` / `copySubTreeAux` — deep-copy a subtree.
* `cutBranch(branch)` — detach `branch` from its parent.
* `topToBottom2Text` / `TreePrintAux` — depth-first dump of the tree.

### 3.4 `streamTree3D` (`streamTree.hpp`)

The top-level structure. Holds **two parallel trees**:

```cpp
NodeP* P;   // node<point3D>*    — the tree of points (nodes)
NodeS* S;   // node<streamLine3D>* — the tree of segments (stream-lines)
```

Each stream's `pI` points at the corresponding point node's `value`, so the two
trees stay in registration. `defD` (default segment length), `PI`, and
`defDeg` (default turn angle = π/2) are the interpreter defaults.

---

## 4. Function walkthrough — the interpreter

### `streamTree3D::stringTurtling2StreamT(string s)`

The heart of the repo: a single left-to-right pass over the turtle string,
mutating the current `(NPt, NSt)` cursor into the point/stream trees. Command
characters (an optional `(value)` overrides the default magnitude):

| Symbol | Action | Frame op |
|---|---|---|
| `F` / `F(D)` | move **forward** by `D`, add a point + segment | `childStream(...)` |
| `+` / `+(a)` | **yaw** +a | `RotU(+a)` |
| `-` / `-(a)` | **yaw** −a | `RotU(-a)` |
| `&` / `&(a)` | **pitch** | `RotL(+a)` |
| `^` / `^(a)` | **pitch** (opposite) | `RotL(-a)` |
| `\` / `\(a)` | **roll** | `RotH(+a)` |
| `/` / `/(a)` | **roll** (opposite) | `RotH(-a)` |
| `!` / `!(w)` | set **width** of current node/segment | — |
| `[` | **push** — start a lateral branch at the current node | descend into new child |
| `]` | **pop** — return to the branch point | ascend |

This is the standard Prusinkiewicz-style turtle interpretation (yaw/pitch/roll
about Heading/Left/Up), extended with a per-segment width `!` and
parametric magnitudes in parentheses.

### Exporters

All three write **Altair/HyperMesh TCL** command scripts (`*solidcone`,
`*solidspherefull`, `*boolean_merge_solids`, `*collectorcreateonly`). Widths
are emitted in `e-2` (×0.01) units.

* `pointExport(file, T)` — a sphere at every node (radius = node width).
* `streamExport(file, T)` — a cone per segment: apex/axis from `pI`, `pL`, `pH`;
  length from `pE->Distance(*pI)`; radius from `w`.
* `TreeExport(file, T)` — segments **and** nodes, each followed by a boolean
  merge, so the result is one fused solid tree.
* `rotateTree(M)` / `rotateStreams` / `rotatePoints` — rigid-rotate the whole
  model by a 3×3 matrix.
* `copySubTree(node)` — extract the sub-branch rooted at a chosen point node as
  a new `streamTree3D` (keeps points and streams in sync via
  `getStreamNodeFromPointNodeVal`).

---

## 5. File map

| File | Role |
|---|---|
| `main.cpp` | reads a turtle string from disk, builds the tree, exports streams + points |
| `point3D.{h,cpp}` | 3D point/vector + linear-algebra helpers |
| `streamLine3DW.{h,cpp}` | segment + orientation frame + width (**the build uses this**) |
| `streamLine3D.{h,cpp}` | legacy, width-less segment — **not built** |
| `EtzNary.hpp` | generic N-ary tree `node<T>` |
| `streamTree.hpp` | `streamTree3D`: dual trees, the interpreter, exporters |
| `TreTrns.hpp` | **legacy prototype** (own duplicate `point3D`, buggy `MatrixRotate`) — not built |
| `CMakeLists.txt`, `.gitignore` | build + hygiene |

---

## 6. Known issues / next steps

Fixed already (see the project `CHANGES.md`): the missing `point3D::w` /
`Distance()` that made the repo un-buildable; a stale case-colliding
`StreamTree.hpp`; a dangling pointer in the default `streamLine3D` ctor; the
`isMember` accumulation bug; the `cutBranch` pointer comparison; and an
uninitialized `subTree` in `copySubTree`.

Still open, and worth a test harness before trusting:

* **`]` branch-pop** advances the string index in only one of its two paths;
  exercise it on multi-branch strings before relying on depth handling.
* **Ownership / leaks:** everything is raw `new`/`newNode` with no `delete`.
  Consider `unique_ptr`/`shared_ptr` or a destructor on `streamTree3D`.
* **`point3D` copy-ctor resets `index` to 0** — deliberate today, but surprising;
  document or revisit if you start copying nodes with meaningful ids.
* `TreTrns.hpp` and the non-`W` `streamLine3D` are legacy; consider deleting.

---

## 7. Background

The motivation, the FSPM context, and the estimation goal are in the
conference presentation and the write-up
(*"Development of a method for estimating the state of a branch model"*).
Those are the authoritative source for *why*; this repo is the *how* for the
structural stage. See [`ARCHITECTURE.md`](./ARCHITECTURE.md).
