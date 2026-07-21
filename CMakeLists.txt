cmake_minimum_required(VERSION 3.10)
project(NaryTree CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
add_compile_options(-Wall -Wextra)

add_executable(narytree
    main.cpp
    point3D.cpp
    streamLine3DW.cpp
)
# Header-only pieces (EtzNary.hpp, streamTree.hpp) are included by the sources above.
