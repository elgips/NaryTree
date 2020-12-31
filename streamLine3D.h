/*
 * streamLine3D.h
 *
 *  Created on: Dec 30, 2020
 *      Author: gips
 */

#ifndef STREAMLINE3D_H_
#define STREAMLINE3D_H_
#include"point3D.h"
//using namespace std;
class streamLine3D{
public:
//	point3D *Xg,*Yg,*Zg;
//	point3D *pI,*pH,*pL,*pU,*pE;
	point3D *pI,*pE,*Xg,*Yg,*Zg,pH,pL,pU;
	streamLine3D();
	streamLine3D(point3D _pi);
	streamLine3D(point3D* _pi);
	streamLine3D(point3D _pi,point3D _pH0,point3D _pL0,point3D _pU0);
	streamLine3D(point3D _pi,point3D _pH0);
	streamLine3D(point3D _pi,point3D _pH0,point3D _pL0);
	streamLine3D(point3D *_pi,point3D *_pe);
	streamLine3D(streamLine3D *_s);
	void updateDirRx(double _theta);
	void updateDirRy(double _theta);
	void updateDirRz(double _theta);
	streamLine3D childStream(double dist);
	void rotateStream(double _M[3][3]);
	void rotateStreamAndPoints(double _M[3][3]);
};



#endif /* STREAMLINE3D_H_ */
