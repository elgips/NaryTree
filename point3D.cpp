/*
 * point3D.cpp
 *
 *  Created on: Dec 30, 2020
 *      Author: gips
 */
#include "point3D.h"

point3D::point3D(){
	x=0.0;
	y=0.0;
	z=0.0;
	index=0;
}
point3D::point3D(double _x,double _y,double _z){
	x=_x;
	y=_y;
	z=_z;
	index=0;
}
point3D::point3D(const point3D& _p){
	x=_p.x;
	y=_p.y;
	z=_p.z;
	index=0;
}
point3D point3D::Rx(double theta){
	point3D temp;
	temp.x=x;
	double st=sin(theta),ct=cos(theta);
	temp.y=ct*y-st*z;
	temp.z=st*y+ct*z;
	return temp;
}
point3D point3D::Ry(double theta){
	point3D temp;
	double st=sin(theta),ct=cos(theta);
	temp.x=ct*x+st*z;
	temp.y=y;
	temp.z=st*x+ct*z;
	return temp;
}
point3D point3D::Rz(double theta){
	point3D temp;
	double st=sin(theta),ct=cos(theta);
	temp.x=ct*x-st*y;
	temp.y=st*x+ct*y;
	temp.z=z;
	return temp;
}
point3D point3D::MatrixRotate(double* _M[3][3]){ //_M is symmetric
	point3D temp;
	temp.x=x*(*_M)[0][0]+y*(*_M)[0][1]+z*(*_M)[0][2];
	temp.y=x*(*_M)[0][1]+y*(*_M)[1][1]+z*(*_M)[1][2];
	temp.z=x*(*_M)[0][2]+y*(*_M)[1][2]+z*(*_M)[2][2];
	return temp;
}
double point3D::norm(){
	return sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0));
}
void point3D::normalize(){
	double nrm=norm();
	x=x/nrm;
	y=y/nrm;
	z=z/nrm;
}
void point3D::set(double _x,double _y,double _z){
	x=_x;
	y=_y;
	z=_z;
}
double point3D::DotProd(point3D _p){
	return x*_p.x+y*_p.y+z*_p.z;
}
/*project the point on a given normal vector*/
point3D point3D::projection(point3D _p_hat){
	double x_p,y_p,z_p,C;
	C=DotProd(_p_hat);
	x_p=C*_p_hat.x;
	y_p=C*_p_hat.y;
	z_p=C*_p_hat.z;
	return point3D(x_p,y_p,z_p);
}
void point3D::gramSh(vector<point3D> _vp){
	vector<point3D>::iterator ip;
	for(ip=_vp.begin();ip<_vp.end();ip++){
		ip->normalize();
		point3D proj=projection(*ip);
		x=x-proj.x;
		y=y-proj.y;
		z=z-proj.z;
		//		if(x==0&&y==0&&z==0){
		//#warning "The vectors are linearly dependent" ;
		//		}
		////			terminate();
		//		}
		normalize();
	}
}
string point3D::point2String(){
	return to_string(index)+" "+to_string(x)+" "+ to_string(y) + " "+ to_string(z);
}
void point3D::setIndex(long unsigned int _index){
	this->index=_index;
}
void point3D::operator=(const point3D& _p){
	this->x=_p.x;
	this->y=_p.y;
	this->z=_p.z;

}

