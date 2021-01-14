/*
 * streamLine3D.cpp
 *
 *  Created on: Dec 30, 2020
 *      Author: gips
 */
#include "streamLine3D.h"
streamLine3D::streamLine3D(){
	point3D PI(0,0,0),X(1,0,0),Y(0,1,0),Z(0,0,1);
	point3D *PI1=&PI,*PE1=0x0;
	pH=X;
	pL=Y;
	pU=Z;
	pI=PI1;
	pE=PE1;
}
//streamLine3D::streamLine3D(point3D _pi){
//	point3D X(1,0,0),Y(0,1,0),Z(0,0,1);
//	point3D *PI1=&_pi,*PE1=0x0;
//	pH=X;
//	pL=Y;
//	pU=Z;
//	pI=PI1;
//	pE=PE1;
//}
streamLine3D::streamLine3D(point3D* _pi){
	point3D X(1,0,0),Y(0,1,0),Z(0,0,1);
	point3D *PE1=0x0;
	pH=X;
	pL=Y;
	pU=Z;
	pI=_pi;
	pE=PE1;
}
streamLine3D::streamLine3D(point3D *_pi,point3D _pH0,point3D _pL0,point3D _pU0){
	point3D X(1,0,0),Y(0,1,0),Z(0,0,1),PH(_pH0),PL(_pL0),PU(_pU0);
	point3D *PE1=0x0;
	vector<point3D> vP;
	PH.normalize();
	pH=PH;
	vP.push_back(PH);
	PL.gramSh(vP);
	if(PL.norm()==0){
		PL=Y;
		PL.gramSh(vP);
		if(PL.norm()==0){
			PL=Z;
			PL.gramSh(vP);
		}
	}
	PL.normalize();
	pL=PL;
	vP.push_back(PL);
	PU.gramSh(vP);
	if(PU.norm()==0){
		PU=Z;
		PU.gramSh(vP);
		if(PU.norm()==0){
			PU=X;
			PU.gramSh(vP);
		}
	}

	PU.normalize();
	pU=PU;
	pI=_pi;
	pE=PE1;
}
streamLine3D::streamLine3D(point3D *_pi,point3D _pH0){
	point3D X(1,0,0),Y(0,1,0),Z(0,0,1),PH(_pH0),PL(Y),PU(Z);
	point3D *PE1=0x0;
	vector<point3D> vP;
	PH.normalize();
	pH=PH;
	vP.push_back(PH);
	PL.gramSh(vP);
	if(PL.norm()==0){
		PL=Z;
		PL.gramSh(vP);
	}
	PL.normalize();
	pL=PL;
	vP.push_back(PL);
	PU.gramSh(vP);
	if(PU.norm()==0){
		PU=X;
		PU.gramSh(vP);
	}
	PU.normalize();
	pU=PU;
	pI=_pi;
	pE=PE1;
}
//streamLine3D::streamLine3D(point3D _pi,point3D _pH0,point3D _pL0){
//	point3D X(1,0,0),Y(0,1,0),Z(0,0,1),PH(_pH0),PL(_pL0),PU(Z);
//	point3D *PE1=0x0;
//	vector<point3D> vP;
//	PH.normalize();
//	pH=PH;
//	vP.push_back(PH);
//	PL.gramSh(vP);
//	if(PL.norm()==0){
//		PL=Y;
//		PL.gramSh(vP);
//		if(PL.norm()==0){
//			PL=Z;
//			PL.gramSh(vP);
//		}
//	}
//	PL.normalize();
//	pL=PL;
//	vP.push_back(PL);
//	PU.gramSh(vP);
//	if(PU.norm()==0){
//		PU=Z;
//		PU.gramSh(vP);
//		if(PU.norm()==0){
//			PU=X;
//			PU.gramSh(vP);
//		}
//	}
//	PU.normalize();
//	pU=PU;
//	pI=&_pi;
//	pE=PE1;
//}
streamLine3D::streamLine3D(point3D *_pi,point3D *_pe){
	pI=_pi;
	pE=_pe;
	point3D X(1,0,0),Y(0,1,0),Z(0,0,1),PH(_pe->x-_pi->x,_pe->y-_pi->y,_pe->z-_pi->z),PL(Y),PU(Z);
	vector<point3D> vP;
	PH.normalize();
	pH=PH;
	vP.push_back(PH);
	PL.gramSh(vP);
	if(PL.norm()==0){
		PL=Z;
		PL.gramSh(vP);
	}
	PL.normalize();
	pL=PL;
	vP.push_back(PL);
	PU.gramSh(vP);
	if(PU.norm()==0){
		PU=X;
		PU.gramSh(vP);
	}
	PU.normalize();
	pU=PU;

}
streamLine3D::streamLine3D(streamLine3D *_s){
	point3D PH(_s->pH),PL(_s->pL),PU(_s->pU),PE1(*(_s->pE)),PI1(*(_s->pI));
	point3D *PI=&PI1,*PE=&PE1;
	pI=PI;
	if(PE!=0x0){
	pE=PE;
	}
	else pE=0x0;
	pH=PH;
	pL=PL;
	pU=PU;
}
void streamLine3D::updateDirRx(double _theta){
	pH=pH.Rx(_theta);
	pL=pL.Rx(_theta);
	pU=pU.Rx(_theta);
}
void streamLine3D::updateDirRy(double _theta){
	pH=pH.Ry(_theta);
	pL=pL.Ry(_theta);
	pU=pU.Ry(_theta);
}
void streamLine3D::updateDirRz(double _theta){
	pH=pH.Rz(_theta);
	pL=pL.Rz(_theta);
	pU=pU.Rz(_theta);
}
void streamLine3D::childStream(point3D* _pE,streamLine3D* _parentStream,streamLine3D* _childStream,double dist){
	_pE->x=_parentStream->pI->x+_parentStream->pH.x*dist;
	_pE->y=_parentStream->pI->y+_parentStream->pH.y*dist;
	_pE->z=_parentStream->pI->z+_parentStream->pH.z*dist;
	_parentStream->pE=_pE;
	_childStream->pI=_pE;
	_childStream->pH=_parentStream->pH;
	_childStream->pL=_parentStream->pL;
	_childStream->pU=_parentStream->pU;
}
	void streamLine3D::rotateStream(double* _M[3][3]){//_M is symmetric rotation matrix
		point3D PH(pH),PL(pL),PU(pU);
		pH=PH.MatrixRotate(_M);
		pH.normalize();
		pL=PL.MatrixRotate(_M);
		pL.normalize();
		pU=PU.MatrixRotate(_M);
		pU.normalize();
	}
	void streamLine3D::rotateStreamAndPoints(double* _M[3][3]){//_M is symmetric rotation matrix
		point3D PH(pH),PL(pL),PU(pU);
		pH=PH.MatrixRotate(_M);
		pH.normalize();
		pL=PL.MatrixRotate(_M);
		pL.normalize();
		pU=PU.MatrixRotate(_M);
		pU.normalize();
		pI->MatrixRotate(_M);
		pE->MatrixRotate(_M);
	}
