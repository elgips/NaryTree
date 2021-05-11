/*
 * point3D.h
 *
 *  Created on: Dec 30, 2020
 *      Author: gips
 */

#ifndef POINT3D_H_
#define POINT3D_H_
#include <vector>
#include <string.h>
#include <iostream>
#include <math.h>
using namespace std;
class point3D{
public:
	double x;
	double y;
	double z;
	long unsigned int index;
	point3D();
	point3D(double _x,double _y,double _z);
	point3D(const point3D& _p);
	point3D Rx(double theta);
	point3D Ry(double theta);
	point3D Rz(double theta);
	point3D MatrixRotate(double *_M[3][3]);
	double norm();
	void normalize();
	void set(double _x,double _y,double _z);
	double DotProd(point3D _p);
	/*project the point on a given normal vector*/
	point3D projection(point3D _p_hat);
	void gramSh(vector<point3D> _vp);
	string point2String();
	void setIndex(long unsigned int _index);
	void operator=(const point3D& _p);
};




#endif /* POINT3D_H_ */
