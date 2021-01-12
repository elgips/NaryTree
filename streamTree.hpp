/*
 * StreamTree.hpp
 *
 *  Created on: Dec 31, 2020
 *      Author: gips
 */

#ifndef STREAMTREE_HPP_
#define STREAMTREE_HPP_
#include "streamLine3D.h"
#include "EtzNary.hpp"
#define defD 0.1
#define PI	3.14
#define defDeg PI/4

typedef node<point3D> NodeP;
typedef node<streamLine3D> NodeS;
class streamTree3D{
public:
	NodeP*	P;
	NodeS* 	S;
	streamTree3D(){
		P=NodeP::newNode(point3D(),NULL);
		S=NodeS::newNode(streamLine3D(&(P->value)), NULL);
	}
	streamTree3D(point3D* _p){
		P=NodeP::newNode(*_p,NULL);
		S=NodeS::newNode(streamLine3D(&(P->value)), NULL);
	}
	streamTree3D(NodeP* _P,NodeS* _S){
		P=_P;
		S=_S;
	}
	static void rotateStreams(NodeS* _S,double* _M[3][3]){
		_S->value.pH=_S->value.pH.MatrixRotate(_M);
		_S->value.pL=_S->value.pL.MatrixRotate(_M);
		_S->value.pU=_S->value.pU.MatrixRotate(_M);
		if(!_S->children.empty()){
			typename vector<NodeS*>::iterator it;
			for(it=_S->children.begin();it!=_S->children.end();it++){
				rotateStreams(*it,_M);
			}
		}
	}
	static void rotatePoints(NodeP* _P,double* _M[3][3]){
		_P->value=_P->value.MatrixRotate(_M);
		if(!_P->children.empty()){
			typename vector<NodeP*>::iterator it;
			for(it=_P->children.begin();it!=_P->children.end();it++){
				rotatePoints(*it,_M);
			}
		}
	}
	void rotateTree(double* _M[3][3]){
		rotatePoints(this->P,_M);
		rotateStreams(this->S,_M);
	}
	static NodeS* getStreamNodeFromPointNodeVal(point3D* _P,node<streamLine3D>* _S){
		node<streamLine3D>* nSL3D=_S;
		if (_S->value.pI==_P){
			return nSL3D;
		}else{
			nSL3D=NULL;
			typename vector<NodeS*>::iterator it;
			it=_S->children.begin();
			while((nSL3D==NULL)&&(it!=_S->children.end())){
				nSL3D=getStreamNodeFromPointNodeVal(_P,*it);
				it++;
			}
		}
		return nSL3D;
	}
	streamTree3D* copySubTree(NodeP* _n){
		if(P->isMember(P, _n)){
			NodeP* subP;
			subP=P->copySubTree(_n);
			NodeS *subS,*Temp;
			Temp=getStreamNodeFromPointNodeVal(&(_n->value),S);
			subS=S->copySubTree(Temp);
			streamTree3D* subTree;
			subTree->P=subP;
			subTree->S=subS;
			return subTree;
		}else{
			invalid_argument("no such point node in the tree");
			terminate();
		}

	}
	static void stringTurtling2StreamT(string _s,NodeP *_P,NodeS *_S){
		//		streamTree3D* ST;
		NodeP *NPt=_P;
		NodeS *NSt=_S;
//		typename vector<NodeS*>::iterator itS;
//		typename vector<NodeP*>::iterator itP;
		size_t it,it2;
		double D,H,L,U;
		string temp;
		char x,xsign;
		point3D 	*Pt=new point3D;
		streamLine3D	*St=new streamLine3D;
		it=0;
		while(it!=_s.length()){
			x=_s[it];
			xsign=_s[it+1];
			switch(x){
			case 'F':
				if(_s.substr(it).find("F(")==0){
					temp=_s.substr(it+2);
					it2=_s.substr(it).find(")");
					D=std::stod(_s.substr(0,it-1));
				}
				else{
					D=defD;
				}
				NPt->appendChild(NPt, NodeP::newNode(point3D(),NPt));
				Pt=NPt->children.back()->value;
				St=NSt->value.childStream(Pt, D);
				NSt->appendChild(NSt,NodeS::newNode(*St,NSt));
				NPt=NPt->children.back();
				NSt=NSt->children.back();
				break;
			case 'H':
				switch(xsign){
				case 'p':
					if(_s.substr(it).find("Hp(")==0){
						temp=_s.substr(it+3);
						it2=_s.substr(it).find(")");
						H=std::stod(_s.substr(0,it2-1));
						it+=it2;
					}
					else{
						H=defDeg;
						it++++;
					}
					NSt->value.updateDirRx(H);
					break;
				case 'm':
					if(_s.substr(it).find("Hm(")==0){
						temp=_s.substr(it+3);
						it2=_s.substr(it).find(")");
						H=std::stod(_s.substr(0,it2-1));
						it+=it2;
					}
					else{
						H=defDeg;
						it++++;
					}
					NSt->value.updateDirRx(-H);
					break;
				default:
					H=defDeg;
					NSt->value.updateDirRx(H);
					break;
				}
				break;
				case 'L':
					switch(xsign){
					case 'p':
						if(_s.substr(it).find("Lp(")==0){
							temp=_s.substr(it+3);
							it2=_s.substr(it).find(")");
							L=std::stod(_s.substr(0,it2-1));
							it+=it2;
						}
						else{
							L=defDeg;
							it++++;
						}
						NSt->value.updateDirRy(L);
						break;
					case 'm':
						if(_s.substr(it).find("Lm(")==0){
							temp=_s.substr(it+3);
							it2=_s.substr(it).find(")");
							L=std::stod(_s.substr(0,it2-1));
							it+=it2;
						}
						else{
							L=defDeg;
							it++++;
						}
						NSt->value.updateDirRy(-L);
						break;
					default:
						L=defDeg;
						NSt->value.updateDirRy(L);
						break;
					}
					break;
					case 'U':
						switch(xsign){
						case 'p':
							if(_s.substr(it).find("Up(")==0){
								temp=_s.substr(it+3);
								it2=_s.substr(it).find(")");
								U=std::stod(_s.substr(0,it2-1));
								it+=it2;
							}
							else{
								U=defDeg;
								it++++;
							}
							NSt->value.updateDirRz(U);
							break;
						case 'm':
							if(_s.substr(it).find("Lm(")==0){
								temp=_s.substr(it+3);
								it2=_s.substr(it).find(")");
								U=std::stod(_s.substr(0,it2-1));
								it+=it2;
							}
							else{
								U=defDeg;
								it++++;
							}
							NSt->value.updateDirRz(-U);
							break;
						default:
							U=defDeg;
							NSt->value.updateDirRz(U);
							break;
						}
						break;
						case '{':
							NodeS::appendChild(NSt->parent,NodeS::newNode(NSt->value,NSt->parent));
							NSt=NSt->parent->children.back();
							it++;
							break;
						case '}':
							if(NSt==NSt->children.front()){
								NSt=NSt->parent;
								NPt=NPt->parent;
							}else NSt=NSt->parent->children.front();
							break;
						default:
							it++;
							break;
			}

		}
	}
	};




#endif /* SRC_STREAMTREE_HPP_ */
