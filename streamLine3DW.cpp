/*
 * streamLine3D.cpp
 *
 *  Created on: Dec 30, 2020
 *      Author: gips
 */
#include "streamLine3DW.h"
streamLine3D::streamLine3D(){
	point3D PI(0,0,0),X(1,0,0),Y(0,1,0),Z(0,0,1);
	point3D *PI1=&PI,*PE1=0x0;
	pH=X;
	pL=Y;
	pU=Z;
	pI=PI1;
	pE=PE1;
	w=1;
	index=0;
}
streamLine3D::streamLine3D(double _w){
	point3D PI(0,0,0),X(1,0,0),Y(0,1,0),Z(0,0,1);
	point3D *PI1=&PI,*PE1=0x0;
	pH=X;
	pL=Y;
	pU=Z;
	pI=PI1;
	pE=PE1;
	w=_w;
	index=0;
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
	w=1;
	index=0;
}
streamLine3D::streamLine3D(point3D* _pi,double _w){
	point3D X(1,0,0),Y(0,1,0),Z(0,0,1);
	point3D *PE1=0x0;
	pH=X;
	pL=Y;
	pU=Z;
	pI=_pi;
	pE=PE1;
	w=_w;
	index=0;
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
		w=1;
	}

	PU.normalize();
	pU=PU;
	pI=_pi;
	pE=PE1;
	index=0;
}
streamLine3D::streamLine3D(point3D *_pi,point3D _pH0,point3D _pL0,point3D _pU0,double _w){
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
	w=_w;
	index=0;

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
	w=1;
	index=0;

}
streamLine3D::streamLine3D(point3D *_pi,point3D _pH0,double _w){
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
	w=_w;
	index=0;
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
	point3D X(1,0,0),Y(0,1,0),Z(0,0,1),PU(_pe->x-_pi->x,_pe->y-_pi->y,_pe->z-_pi->z),PL(Y),PH(X);
	vector<point3D> vP;
	PU.normalize();
	pU=PU;
	vP.push_back(PU);
	PH.gramSh(vP);
	if(PH.norm()==0){
		PH=Y;
		PH.gramSh(vP);
	}
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
	w=1.0;
	index=0;

}
streamLine3D::streamLine3D(point3D *_pi,point3D *_pe,double _w){
	pI=_pi;
	pE=_pe;
	point3D X(1,0,0),Y(0,1,0),Z(0,0,1),PU(_pe->x-_pi->x,_pe->y-_pi->y,_pe->z-_pi->z),PL(Y),PH(X);
	vector<point3D> vP;
	PU.normalize();
	pU=PU;
	vP.push_back(PU);
	PH.gramSh(vP);
	if(PH.norm()==0){
		PH=Y;
		PH.gramSh(vP);
	}
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
	w=_w;
	index=0;

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
	w=_s->w;
	index=0;
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
void streamLine3D::childStream(point3D* _pE,streamLine3D* _parentStream,streamLine3D* _childStream,double dist,double _w){
	_pE->x=_parentStream->pI->x+_parentStream->pH.x*dist;
	_pE->y=_parentStream->pI->y+_parentStream->pH.y*dist;
	_pE->z=_parentStream->pI->z+_parentStream->pH.z*dist;
	_parentStream->pE=_pE;
	_childStream->pI=_pE;
	_childStream->pH=_parentStream->pH;
	_childStream->pL=_parentStream->pL;
	_childStream->pU=_parentStream->pU;
	_childStream->w=_w;
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
void streamLine3D::setIndex(long unsigned int _index){
	this->index=_index;
}

void streamLine3D::RotH(const double& theta){
// point3D pHT(this->pH.x,this->pH.y,this->pH.z);
 point3D pLT(cos(theta)*this->pL.x+sin(theta)*this->pU.x,cos(theta)*this->pL.y+sin(theta)*this->pU.y,cos(theta)*this->pL.z+sin(theta)*this->pU.z);
 point3D pUT(-sin(theta)*this->pL.x+cos(theta)*this->pU.x,-sin(theta)*this->pL.y+cos(theta)*this->pU.y,-sin(theta)*this->pL.z+cos(theta)*this->pU.z);
//this->pH=pHT;
this->pL=pLT;
this->pU=pUT;
}

void streamLine3D::RotL(const double& theta){
// point3D pLT(this->pL.x,this->pL.y,this->pL.z);
 point3D pHT(cos(theta)*this->pH.x+sin(theta)*this->pU.x,cos(theta)*this->pH.y+sin(theta)*this->pU.y,cos(theta)*this->pH.z+sin(theta)*this->pU.z);
 point3D pUT(-sin(theta)*this->pH.x+cos(theta)*this->pU.x,-sin(theta)*this->pH.y+cos(theta)*this->pU.y,-sin(theta)*this->pH.z+cos(theta)*this->pU.z);
this->pH=pHT;
//this->pL=pLT;
this->pU=pUT;
}

void streamLine3D::RotU(const double& theta){
// point3D pUT(this->pU.x,this->pU.y,this->pU.z);
 point3D pHT(cos(theta)*this->pH.x-sin(theta)*this->pL.x,cos(theta)*this->pH.y-sin(theta)*this->pL.y,cos(theta)*this->pH.z-sin(theta)*this->pL.z);
 point3D pUT(sin(theta)*this->pH.x+cos(theta)*this->pL.x,sin(theta)*this->pH.y+cos(theta)*this->pL.y,sin(theta)*this->pH.z+cos(theta)*this->pL.z);
this->pH=pHT;
//this->pL=pLT;
this->pU=pUT;
}
