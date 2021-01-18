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
	static streamTree3D* stringTurtling2StreamT(string _s){
		streamTree3D* ST3D=new streamTree3D;
		NodeP *NPt=NodeP::newNode(point3D(),NULL);
		NodeS *NSt=NodeS::newNode(streamLine3D(&(NPt->value)), NULL);
		ST3D->P=NPt;
		ST3D->S=NSt;
		//		typename vector<NodeS*>::iterator itS;
		//		typename vector<NodeP*>::iterator itP;
		size_t it,it2;
		double D,H,L,U;
		string temp;
		char x,xsign;
		//		point3D 	*Pt,Pt1;
		//		streamLine3D	*St,St1;
		it=0;
		while(it<_s.length()){
			x=_s[it];
			xsign=_s[it+1];
			switch(x){
			case 'F':
				if(_s.substr(it).find("F(")==0){
					temp=_s.substr(it+2);
					it2=temp.find(")");
					D=std::stod(temp.substr(0,it2));
					it+=it2+3;
				}
				else{
					D=defD;
					it++;
				}
				NPt->appendChild(NPt, NodeP::newNode(point3D(),NULL));
				NSt->appendChild(NSt, NodeS::newNode(streamLine3D(),NULL));
				//				point3D *Pt=&(NPt->children.back()->value);
				//				streamLine3D *St=&(NSt->children.back()->value);
				streamLine3D::childStream(&(NPt->children.back()->value), &(NSt->value),&(NSt->children.back()->value),D);
				NPt=NPt->children.back();
				NSt=NSt->children.back();

				break;
			case 'H':
				if(it+1<_s.length()){
					switch(xsign){
					case 'p':
						if(_s.substr(it).find("Hp(")==0){
							temp=_s.substr(it+3);
							it2=temp.find(")");
							H=std::stod(temp.substr(0,it2));
							it+=it2;
						}
						else{
							H=defDeg;
							it+=2;
						}
						NSt->value.updateDirRx(H);
						break;
					case 'm':
						if(_s.substr(it).find("Hm(")==0){
							temp=_s.substr(it+3);
							it2=temp.find(")");
							H=std::stod(temp.substr(0,it2));
							it+=it2;
						}
						else{
							H=defDeg;
							it+=2;
						}
						NSt->value.updateDirRx(-H);
						break;
					default:
						H=defDeg;
						NSt->value.updateDirRx(H);
						break;
					}}else{
						H=defDeg;
						it++;
						NSt->value.updateDirRx(H);
					}
				break;
			case 'L':
				if(it+1<_s.length()){
					switch(xsign){
					case 'p':
						if(_s.substr(it).find("Lp(")==0){
							temp=_s.substr(it+3);
							it2=temp.find(")");
							L=std::stod(temp.substr(0,it2));
							it+=it2;
						}
						else{
							L=defDeg;
							it+=2;
						}
						NSt->value.updateDirRy(L);
						break;
					case 'm':
						if(_s.substr(it).find("Lm(")==0){
							temp=_s.substr(it+3);
							it2=temp.find(")");
							L=std::stod(temp.substr(0,it2));
							it+=it2;
						}
						else{
							L=defDeg;
							it+=2;
						}
						NSt->value.updateDirRy(-L);
						break;
					default:
						L=defDeg;
						NSt->value.updateDirRy(L);
						break;}
				}else{
					L=defDeg;
					it++;
					NSt->value.updateDirRy(L);
				}
				break;
			case 'U':
				if(it+1<_s.length()){
					switch(xsign){
					case 'p':
						if(_s.substr(it).find("Up(")==0){
							temp=_s.substr(it+3);
							it2=temp.find(")");
							U=std::stod(temp.substr(0,it2));
							it+=it2;
						}
						else{
							U=defDeg;
							it+=2;
						}
						NSt->value.updateDirRz(U);
						break;
					case 'm':
						if(_s.substr(it).find("Lm(")==0){
							temp=_s.substr(it+3);
							it2=temp.find(")");
							U=std::stod(temp.substr(0,it2));
							it+=it2;
						}
						else{
							U=defDeg;
							it+=2;
						}
						NSt->value.updateDirRz(-U);
						break;
					default:
						U=defDeg;
						NSt->value.updateDirRz(U);
						break;
					}}else{
						H=defDeg;
						it++;
						NSt->value.updateDirRx(H);
					}
				break;
			case '{':
				NodeS::appendChild(NSt->parent,NodeS::newNode(NSt->value,NULL));
				NSt=NSt->parent->children.back();
				it++;
				break;
			case '}':
				if(NSt==NSt->parent->children.front()){
					while(NSt==NSt->parent->children.front()){
						NSt=NSt->parent;
						NPt=NPt->parent;
					}
				}else {
					NSt=NSt->parent->children.front();
					it++;
				}
				break;
			default:
				it++;
				break;
			}

		}
		//		streamTree3D ST3D(NPt, NSt);
		return ST3D;
	}
	static void pointExportAux(NodeP* _child,ofstream* out){
		*out<<endl;
		string s=std::to_string(_child->value.x)+" "+std::to_string(_child->value.y)+" "+std::to_string(_child->value.z)+"\n";
		*out<<s;
		if(!_child->children.empty()){
			typename vector<NodeP*>::iterator it;
			for(it=_child->children.begin();it!=_child->children.end();it++){
				pointExportAux(*it,out);
			}
		}
	}
	static void pointExport(string _fileName,streamTree3D* T){
		ofstream out( _fileName.c_str(), ios::out );
		NodeP* Np=T->P;
		string s=std::to_string(Np->value.x)+" "+std::to_string(Np->value.y)+" "+std::to_string(Np->value.z)+"\n";
		out<<s;
		if(!Np->children.empty()){
			typename vector<NodeP*>::iterator it;
			for(it=Np->children.begin();it!=Np->children.end();it++){
				pointExportAux(*it,&out);
			}
		}
		out.close();
	}
	static void streamExportAux(NodeS* _child,ofstream* out){
		*out<<endl;
		if(_child->value.pE!=0x0){
			string s=std::to_string(_child->value.pI->x)+" "+std::to_string(_child->value.pI->y)+" "+std::to_string(_child->value.pI->z)+" "+std::to_string(_child->value.pE->x)+" "+std::to_string(_child->value.pE->y)+" "+std::to_string(_child->value.pE->z)+"\n";
			*out<<s;
			if(!_child->children.empty()){
				typename vector<NodeS*>::iterator it;
				for(it=_child->children.begin();it!=_child->children.end();it++){
					streamExportAux(*it,out);
				}
			}
		}
	}
	static void streamExport(string _fileName,streamTree3D* T){
		ofstream out( _fileName.c_str(), ios::out );
		NodeS* Ns=T->S;
		string s=std::to_string(Ns->value.pI->x)+" "+std::to_string(Ns->value.pI->y)+" "+std::to_string(Ns->value.pI->z)+" "+std::to_string(Ns->value.pE->x)+" "+std::to_string(Ns->value.pE->y)+" "+std::to_string(Ns->value.pE->z)+"\n";
		out<<s;
		if(!Ns->children.empty()){
			typename vector<NodeS*>::iterator it;
			for(it=Ns->children.begin();it!=Ns->children.end();it++){
				streamExportAux(*it,&out);
			}
		}
		out.close();
	}
};




#endif /* SRC_STREAMTREE_HPP_ */
