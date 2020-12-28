/*
 * TreTrns.hpp
 *
 *  Created on: Dec 21, 2020
 *      Author: gips
 */

#ifndef TRETRNS_HPP_
#define TRETRNS_HPP_
#define DL 1
#define PI 3.14
#define eps 1e-6
#include "EtzNary.hpp"
#include "LSYS_PARA.h"

using namespace std;

class point3D{
public:
	double x;
	double y;
	double z;
	point3D(){
		x=0;
		y=0;
		z=0;
	}
	point3D(double _x,double _y,double _z){
		x=_x;
		y=_y;
		z=_z;
	}
	point3D(point3D _p){
		x=_p.x;
		y=_p.y;
		z=_p.z;
	}

	point3D Rx(double theta){
		point3D temp;
		temp.x=x;
		double st=sin(theta),ct=cos(theta);
		temp.y=ct*y-st*z;
		temp.z=st*y+ct*z;
		return temp;
	}
	point3D Ry(double theta){
		point3D temp;
		double st=sin(theta),ct=cos(theta);
		temp.x=ct*x+st*z;
		temp.y=y;
		temp.z=st*x+ct*z;
		return temp;
	}
	point3D Rz(double theta){
		point3D temp;
		double st=sin(theta),ct=cos(theta);
		temp.x=ct*x-st*y;
		temp.y=st*x+ct*y;
		temp.z=z;
		return temp;
	}
	point3D MatrixRotate(double _M[3][3]){ //_M is symmetric
		point3D temp;
		temp.x=x*_M[1][1]+y*_M[1][2]+y*_M[1][3];
		temp.y=x*_M[1][2]+y*_M[2][2]+y*_M[2][3];
		temp.z=x*_M[1][3]+y*_M[2][3]+y*_M[3][3];
		return temp;
	}
	double norm(){
		return sqrt(x^2+y^2+z^2);
	}

	void normalize(){
		double nrm=norm();
		x=x/nrm;
		y=y/nrm;
		z=z/nrm;
	}
	double DotProd(point3D _p){
		return x*_p.x+y*_p.y+z*_p.z;
	}
	/*project the point on a given normal vector*/
	point3D projection(point3D _p_hat){
		double x_p,y_p,z_p,C;
		C=DotProd(_p_hat);
		x_p=C*_p_hat.x;
		y_p=C*_p_hat.y;
		z_p=C*_p_hat.z;
		return point3D(x_p,y_p,z_p);
	}
	void gramSh(vector<point3D> _vp){
		vector<point3D>::iterator ip;
		for(ip=_vp.begin();ip<_vp.end();ip++){
			ip->normalize();
			point3D proj=projection(*ip);
			x=x-proj.x;
			y=y-proj.y;
			z=z-proj.z;
			normalize();
		}
	}

	//	point3D(point3D _source,double _dl){
	//		x=_source.x+_dl*_source.Vx;
	//		y=_source.y+_dl*_source.Vy;
	//		z=_source.z+_dl*_source.Vz;
	//		Vx=_source.Vx;
	//		Vy=_source.Vy;
	//		Vz=_source.Vz;
	//	}
	string point2String(){
		return to_string(x)+" "+ to_string(y) + " "+ to_string(z);
	}
};

class StreamLine3D{
public:
	static point3D Xg,Yg,Zg;
	point3D pI,pH,pL,pU,pE;
	StreamLine3D(){
		pI({0,0,0});
		*pE=NULL;
		Xg({1,0,0});
		Yg({0,1,0});
		Zg({0,0,1});
		pH(Xg);
		pL(Yg);
		pU(Zg);
	}
	StreamLine3D(point3D _pi){
		pI(_pi);
		*pE=NULL;
		Xg({1,0,0});
		Yg({0,1,0});
		Zg({0,0,1});
		pH(Xg);
		pL(Yg);
		pU(Zg);
	}
	StreamLine3D(point3D* _pi){
		*pI=_pi;
		*pE=NULL;
		Xg({1,0,0});
		Yg({0,1,0});
		Zg({0,0,1});
		pH(Xg);
		pL(Yg);
		pU(Zg);
	}
	//	StreamLine3D(point3D _pi,point3D _pH0){
	//		pI(_pi);
	//		_pH0.normalize();
	//		pH(_pH0);
	//		Xg({1,0,0});
	//		Yg({0,1,0});
	//		Zg({0,0,1});
	//		int test=1*(pH.dot(point3D({})))
	//		//		pH=pL.Rz(PI/2);
	//		//		pU=pL.Ry(PI/2);
	//	}
	//	StreamLine3D(point3D _pi,point3D _pt0,double roll){
	//		pI(_pi.x,_pi.y,_pi.z);
	//		double norm2=sqrt((_pt0.x)^2+(_pt0.y)^2+(_pt0.z)^2);
	//		pt({_pt0.x/norm2,_pt0.y/norm2,_pt0.z/norm2});
	//		double phi_t=atan(-_pt0.x/_pt0.z);
	//		pn({cos(phi_t),0,sin(phi_t)});
	//		//			pn({1,0,0});//make proper normal, natural normal is in a ZX tanget plane
	//	}
	StreamLine3D(point3D _pi,point3D _pH0,point3D _pL0,point3D _pU0){
		pI(_pi);
		&pE=NULL;
		Xg({1,0,0});
		Yg({0,1,0});
		Zg({0,0,1});
		pH(_pH0.normalize());
		_pL0.normalize();
		vector<point3D> vp;
		vp.push_back(_pH0);
		_pL0.gramSh(vp);
		pL(_pL0);
		_pU0.normalize();
		vp.push_back(_pL0);
		_pU0.gramSh(vp);
		pU(_pU0);
	}
	StreamLine3D(point3D _pi,point3D _pH0,point3D _pL0,point3D _pU0,point3D _pE){
		pI(_pi);
		pE=_pE;
		Xg({1,0,0});
		Yg({0,1,0});
		Zg({0,0,1});
		pH(_pH0.normalize());
		_pL0.normalize();
		vector<point3D> vp;
		vp.push_back(_pH0);
		_pL0.gramSh(vp);
		pL(_pL0);
		_pU0.normalize();
		vp.push_back(_pL0);
		_pU0.gramSh(vp);
		pU(_pU0);
	}
	StreamLine3D(point3D *_pi,point3D _pH0,point3D _pL0,point3D _pU0){
		&pI=_pi;
		&pE=NULL;
		Xg({1,0,0});
		Yg({0,1,0});
		Zg({0,0,1});
		pH(_pH0.normalize());
		_pL0.normalize();
		vector<point3D> vp;
		vp.push_back(_pH0);
		_pL0.gramSh(vp);
		pL(_pL0);
		_pU0.normalize();
		vp.push_back(_pL0);
		_pU0.gramSh(vp);
		pU(_pU0);
	}
	StreamLine3D(point3D *_pi,point3D _pH0,point3D _pL0,point3D _pU0,point3D* _pE){
		&pI=_pi;
		&pE=_pE;
		Xg({1,0,0});
		Yg({0,1,0});
		Zg({0,0,1});
		pH(_pH0.normalize());
		_pL0.normalize();
		vector<point3D> vp;
		vp.push_back(_pH0);
		_pL0.gramSh(vp);
		pL(_pL0);
		_pU0.normalize();
		vp.push_back(_pL0);
		_pU0.gramSh(vp);
		pU(_pU0);
	}
	StreamLine3D(StreamLine3D* _s){
		this->Xg(_s->Xg);
		this->Yg(_s->Yg);
		this->Zg(_s->Zg);
		pI(_s->pI);
		pE(_s->pE);
		pH(_s->pH);
		pL(_s->pL);
		pU(_s->pU);
	}
	void updateDirRx(double _theta){
		pH=pH.Rx(_theta);
		pL=pL.Rx(_theta);
		pU=pU.Rx(_theta);
	}
	void updateDirRy(double _theta){
		pH=pH.Ry(_theta);
		pL=pL.Ry(_theta);
		pU=pU.Ry(_theta);
	}
	void updateDirRz(double _theta){
		pH=pH.Rz(_theta);
		pL=pL.Rz(_theta);
		pU=pU.Rz(_theta);
	}
	StreamLine3D ChildStream(double dist){
		*pE=&point3D(pI.x+pH.x*dist,pI.y+pH.y*dist,pI.z+pH.z*dist);

		StreamLine3D StLn(pE,pH,pL,pU);
		return StLn;
	}
	StreamLine3D rotateStream(StreamLine3D *_s,double _M[3][3]){//_M is symmetric rotation matrix

		StreamLine3D SL3D(pI.MatrixRotate(_M),_s->pH.MatrixRotate(_M),_s->pL.MatrixRotate(_M),_s->pU.MatrixRotate(_M));
		if(*pE!=0x0){
			SL3D.pE=pE.MatrixRotate(_M);
		}
		pI=pI.MatrixRotate(_M);
		pH=pH.MatrixRotate(_M);
		pL=pL.MatrixRotate(_M);
		pI=pU.MatrixRotate(_M);
	return SL3D;
	}
};
class StreamTree3D{
public:
	node<StreamLine3D> *streams;
	node<point3D> *points;
	StreamTree3D(){
		points=&(new node<point3D>(&point3D()));
		streams=&(new node<StreamLine3D>(&StreamLine3D(*points->value)));
	}
	StreamTree3D(point3D* _p){
		points=&(new node<point3D>(_p));
		streams=&(new node<StreamLine3D>(&StreamLine3D(*points->value)));
	}
	StreamTree3D(node<point3D> _ps,node<StreamLine3D> _sts){
		points=_ps;
		streams=&(new node<StreamLine3D>(&StreamLine3D(*points->value)));
	}
	void rotateStreams(double _M[3][3]){

	}
	static node<StreamLine3D>* getStreamNodeFromPointNodeVal(point3D* _p,node<StreamLine3D>* _s){
		node<StreamLine3D>* nSL3D=_s;
		if (&(nSL3D->value->pI)==_p){
			return nSL3D;
		}else{
			nSL3D=NULL;
			typename vector<node<StreamLine3D>*>::iterator it;
			it=_s->children.begin();
			while((nSL3D==NULL)&&(it!=_s->children.end())){
				nSL3D=getStreamNodeFromPointNodeVal(_p,*it);
			}
		}
		return nSL3D;
	}
	StreamTree3D* cutSubTree(node<point3D>* _n){
		StreamTree3D* subTree;
		if(*points->isMember(_n)){
			node<StreamLine3D> *subStreams,*Temp;
//			StreamTree3D
			node<point3D> *subPoints=&(new node<point3D>(_n->value,NULL));;
			Temp=getStreamNodeFromPointNodeVal(_n->value,this->streams);
			*subStreams->value=new node<StreamLine3D>(Temp->value,NULL);
			subStreams->appendChildren(Temp->children);
			subTree->points=subPoints;
			subTree->streams=subStreams;

		}else{
			invalid_argument("no such point node in the tree");
			terminate();
		}
		return subTree;
	}
	void mountSubTreeAtPoint(StreamTree3D* ST3D,node<point3D>* _n)

};
//void auxString2VerTree(node<point3D> _n,string* _s,size_t* _t){
//	string temp;
//	size_t lb,rb;
//	while(*_s[*_t]!=']'){
//		switch(*_s[*_t]){
//		case 'F':
//			lb=(*_s).substr((*_t)+1).find("(");
//			if(lb==(*_s).npos||(lb>=1)){
//				point3D p1(_n.value,DL);
//				_n.appendChild(p1);
//				auxString2VerTree(_n.children.back(),_s,_t);
//			}else if (lb==0){
//				rb=(*_s).substr((*_t)+1).find(")");
//				if(rb>lb){
//					if (rb==lb+1){
//						point3D p1(_n.value,DL);
//						_n.appendChild(p1);
//						auxString2VerTree(_n.children.back(),_s,_t);
//					}
//					else{
//						temp=(*_s).substr(lb);
//						temp=temp.substr(0, temp.find(")"));
//						point3D p1(_n.value,stod(temp));
//						_n.appendChild(p1);
//						auxString2VerTree(_n.children.back(),_s,_t);
//					}
//				}
//			}
//			break;
//		case 'O':
//			break;
//		case '[':
//
//			break;
//		default:
//			tt++;
//		}
//	}
//}
//
//node<point3D> LSYS2VerTree(LSYS _L){
//	node<point3D> root({});
//	size_t t=0;
//	vector<node<point3D>>::iterator it;
//	string input=_L.current;
//
//	return root;
//}
//
//
//

#endif /* TRETRNS_HPP_ */
