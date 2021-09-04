/*
 * StreamTree.hpp
 *
 *  Created on: Dec 31, 2020
 *      Author: gips
 */

#ifndef STREAMTREE_HPP_
#define STREAMTREE_HPP_
#include "EtzNary.hpp"
#include "streamLine3DW.h"
#include <iomanip>
#define defD 0.5
#define PI	3.1416
#define defDeg PI/2

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
	static streamTree3D* stringTurtling2StreamT(string _s){/*fits for non negative input values in functions*/
		streamTree3D* ST3D=new streamTree3D;
		long unsigned int nPoint=0;
		long unsigned int nStream=0;
		NodeP *NPt=NodeP::newNode(point3D(),NULL);
		NPt->value.setIndex(nPoint);
		//		nPoint++;
		NodeS *NSt=NodeS::newNode(streamLine3D(&(NPt->value)), NULL);
		//		NSt->value.setIndex(nStream);
		//		nStream++;

		NPt->appendChild(NPt, NodeP::newNode(point3D(),NULL));
		NSt->appendChild(NSt, NodeS::newNode(streamLine3D(),NULL));
		NPt=NPt->children.back();
		NSt=NSt->children.back();
		ST3D->P=NPt;
		ST3D->S=NSt;
		//		typename vector<NodeS*>::iterator itS;
		//		typename vector<NodeP*>::iterator itP;
		size_t it,it2;
		double D,H,width;//L,U,width;
		string temp;
		char x;//xsign;
		//		point3D 	*Pt,Pt1;
		//		streamLine3D	*St,St1;
		it=0;
		while(it<_s.length()){
			x=_s[it];
			//xsign=_s[it+1];
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
				streamLine3D::childStream(&(NPt->children.back()->value), &(NSt->value),&(NSt->children.back()->value),D,width);
				NSt->value.setIndex(nStream++);
				NPt=NPt->children.back();
				NPt->value.setIndex(++nPoint);
				NSt=NSt->children.back();
				//				NSt->value.setIndex(++nStream);
				break;
			case '+':
				if(_s.substr(it).find("+(")==0){
					temp=_s.substr(it+2);
					it2=temp.find(")");
					H=std::stod(temp.substr(0,it2));
					it+=it2;
				}
				else{
					H=defDeg;
					it+=1;
				}
				NSt->value.RotU(H);
				break;
			case '-':
				if(_s.substr(it).find("-(")==0){
					temp=_s.substr(it+2);
					it2=temp.find(")");
					H=std::stod(temp.substr(0,it2));
					it+=it2;
				}
				else{
					H=defDeg;
					it+=1;
				}
				NSt->value.RotU(-H);
				break;
			case '&':
				if(_s.substr(it).find("&(")==0){
					temp=_s.substr(it+3);
					it2=temp.find(")");
					H=std::stod(temp.substr(0,it2));
					it+=it2;
				}
				else{
					H=defDeg;
					it+=1;
				}
				NSt->value.RotL(H);
				break;
			case '^':
				if(_s.substr(it).find("^(")==0){
					temp=_s.substr(it+2);
					it2=temp.find(")");
					H=-std::stod(temp.substr(0,it2));
					it+=it2;
				}
				else{
					H=-defDeg;
					it+=1;
				}
				NSt->value.RotL(-H);
				break;
			case 92:
				if(_s.substr(it+1).find("\(")==0){
					temp=_s.substr(it+2);
					it2=temp.find(")");
					H=std::stod(temp.substr(0,it2));
					it+=it2;
				}
				else{
					H=defDeg;
					it+=1;
				}
				NSt->value.RotH(H);
				break;
			case '!':
				if(_s.substr(it).find("!(")==0){
					temp=_s.substr(it+2);
					it2=temp.find(")");
					width=std::stod(temp.substr(0,it2));
					it+=it2;
				}
				else{
					width=1;
					it+=1;
				}
				NSt->value.w=width;
				NPt->value.w=width;
				break;
			case '/':
				if(_s.substr(it).find("/(")==0){
					temp=_s.substr(it+2);
					it2=temp.find(")");
					H=-std::stod(temp.substr(0,it2));
					it+=it2;
				}
				else{
					H=-defDeg;
					it+=1;
				}
				NSt->value.RotH(-H);
				break;
			case '[':
				NodeS::appendChild(NSt->parent,NodeS::newNode(NSt->value,NULL));
				NSt=NSt->parent->children.back();
				//				NSt->value.setIndex(++nStream);
				it++;
				break;
			case ']':
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
		//		*out<<endl;
		//*out<<setw(12)<<_child->value.index<<std::setw(12)<<_child->value.x<<std::setw(12)<<_child->value.y<<std::setw(12)<<_child->value.z<<std::setw(12)<<_child->value.w<<endl;
		*out<<"*solidspherefull "<<_child->value.x<<" "<<_child->value.y<<" "<<_child->value.z<<" "<<_child->parent->value.w<<"e-2"<<endl;
		//		*out<<s;
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
		//		string s="*NODE\n";
		//		out<<s;
		//		out<<setw(12)<<Np->value.index<<std::setw(12)<<Np->value.x<<std::setw(12)<<Np->value.y<<std::setw(12)<<Np->value.z<<std::setw(12)<<Np->value.w<<std::setw(12)<<endl;
		out<<"*solidspherefull "<<Np->value.x<<" "<<Np->value.y<<" "<<Np->value.z<<" "<<Np->value.w<<"e-2"<<endl;
		//		out<<s;
		if(!Np->children.empty()){
			typename vector<NodeP*>::iterator it;
			for(it=Np->children.begin();it!=Np->children.end();it++){
				pointExportAux(*it,&out);
			}
		}
		//		s="*END";
		//		out<<s;
		out.close();
	}
	static void streamExportAux(NodeS* _child,ofstream* out){
		//		*out<<endl;
		if(_child->value.pE!=0x0){
			//			string s=std::to_string(_child->value.index)+" "+std::to_string(_child->value.pI->index)+" "+"0 "+std::to_string(_child->value.w)+"\n";
			//			*out<<s;
			//			string s=std::to_string(_child->value.index)+" "+std::to_string(_child->value.pI->index)+" "+std::to_string(_child->value.pE->index)+" "+std::to_string(_child->value.w)+"\n";

			//			*out<<setw(12)<<_child->value.index<<setw(12)<<_child->value.pI->index<<setw(12)<<_child->value.pE->index<<setw(12)<<_child->value.w<<std::setw(12)<<endl;
			*out<<"*solidcone "<<_child->value.pI->x<<" "<<_child->value.pI->y<<" "<<_child->value.pI->z<<" "<<_child->value.pL.x<<" "<<_child->value.pL.y<<" "<<_child->value.pL.z<<" "<<_child->value.pH.x<<" "<<_child->value.pH.y<<" "<<_child->value.pH.z<<" "<<_child->value.w<<"e-2 "<<_child->value.w<<"e-2 1 0.0 360.0 "<<_child->value.pE->Distance(*_child->value.pI)<<endl;
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
		NodeS* Ns=T->S->parent;
		//string s="*ELEMENT_BEAM";
		//out<<s<<endl;
		//		s=std::to_string(Ns->value.index)+" "+std::to_string(Ns->value.pI->index)+" "+std::to_string(Ns->value.pE->index)+" "+std::to_string(Ns->value.w)+"\n";
		//		out<<s;
		//out<<setw(12)<<Ns->value.index<<setw(12)<<Ns->value.pI->index<<setw(12)<<Ns->value.pE->index<<setw(12)<<Ns->value.w<<std::setw(12)<<endl;
//		out<<"*solidcone "<<Ns->value.pI->x<<" "<<Ns->value.pI->y<<" "<<Ns->value.pI->z<<" "<<Ns->value.pL.x<<" "<<Ns->value.pL.y<<" "<<Ns->value.pL.z<<" "<<Ns->value.pH.x<<" "<<Ns->value.pH.y<<" "<<Ns->value.pH.z<<" "<<Ns->value.w<<"e-2 "<<Ns->value.w<<"e-2 1 0.0 360.0 "<<Ns->value.pE->Distance(*Ns->value.pI)<<endl;
		//		s=std::to_string(Ns->value.pE->x)+" "+std::to_string(Ns->value.pE->y)+" "+std::to_string(Ns->value.pE->z)+" 1.000000 0.000000 0.000000\n";
		//		out<<s;
		if(!Ns->children.empty()){
			typename vector<NodeS*>::iterator it;
			for(it=Ns->children.begin();it!=Ns->children.end();it++){
				streamExportAux(*it,&out);
			}
		}
		//		s="*END";
		//		out<<s;
		out.close();
	}
//	static void TreeExport(string _fileName,streamTree3D*T){
//		ofstream out( _fileName.c_str(), ios::out );
//		NodeS* Ns=T->S;
//		NodeP* Np=T->P;
//		out<<"*solidspherefull "<<Np->value.x<<" "<<Np->value.y<<" "<<Np->value.z<<" "<<Np->value.w<<"e-2"<<endl;
//		if(!Np->children.empty()){
//
//		}
//	}
};




#endif /* SRC_STREAMTREE_HPP_ */
