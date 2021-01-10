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
};




#endif /* SRC_STREAMTREE_HPP_ */
