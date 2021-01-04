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
class streamTree3D{
public:
	node	<point3D> 		P;
	node	<streamLine3D> 	S;
	streamTree3D(){
		point3D 				p;
		node	<point3D>		nP(&p);
		P=nP;
		streamLine3D 			sP(&p);
		node	<streamLine3D> 	nS(sP);
		S=nS;
	}
	streamTree3D(point3D* _p){
		node	<point3D>		nP(_p);
		streamLine3D 			sP(_p);
		P=nP;
		node	<streamLine3D> 	nS(sP);
		S=nS;
	}
	streamTree3D(node<point3D> _ps,node<streamLine3D> _sts){
		P=_ps;
		S=_sts;
	}
	void rotateStreams(node<point3D>* _pP,node<streamLine3D>* _pS,node<streamLine3D>* _nS,double _M[3][3]){
		node<point3D>* nPR;
		node<streamLine3D>* nSR;
		nPR->parent=_pP;
		nSR->parent=_pS;
		_nS->value->rotateStream(_M);
		nSR->value=_nS->value;
		nSR->value->pI->MatrixRotate(_M);
		nPR->value=nSR->value->pI;
		if(!_nS->children.empty()){
			typename vector<node<streamLine3D>*>::iterator it;
			for(it=_nS->children.begin();it!=_nS->children.end();it++){
				rotateStreams(nPR,nSR,*it,_M);
			}
		}
	}
	node<point3D>* rotatePoints(node<point3D>* _p,node<point3D>* _n,double _M[3][3]){ //not fit to Streams rotations - points to streams refs lost
		node<point3D>* nR;
		nR->parent=_p;
		_n->value->MatrixRotate(_M);
		nR->value=_n->value;
		if(!_n->children.empty()){
			typename vector<node<point3D>*>::iterator it;
			for(it=_n->children.begin();it!=_n->children.end();it++){
				nR->children.push_back(rotatePoints(nR,*it,_M));
			}
		}
		return nR;
	}
	static node<streamLine3D>* getStreamNodeFromPointNodeVal(point3D* _p,node<streamLine3D>* _s){
		node<streamLine3D>* nSL3D=_s;
		if (&(*(nSL3D->value)->pI)==_p){
			return nSL3D;
		}else{
			nSL3D=NULL;
			typename vector<node<streamLine3D>*>::iterator it;
			it=_s->children.begin();
			while((nSL3D==NULL)&&(it!=_s->children.end())){
				nSL3D=getStreamNodeFromPointNodeVal(_p,*it);
				it++;
			}
		}
		return nSL3D;
	}
	streamTree3D* cutSubTree(node<point3D>* _n){//bad code, fix it
			streamTree3D* subTree;
			if(P.isMember(&P,_n)){
				node<point3D> subP;
				subP=P.copySubTree(_n);
				node<streamLine3D> subS,*Temp;
				Temp=getStreamNodeFromPointNodeVal(_n->value, &S);
				subS=S.copySubTree(Temp);
				subTree->P=subP;
				subTree->S=subS;
			}else{
				invalid_argument("no such point node in the tree");
				terminate();
			}
			return subTree;
		}
	//	streamTree3D(){
	//		point3D 				P;
	//		node	<point3D>		nP(P);
	//		streamLine3D 			sP(P);
	//		node	<streamLine3D> 	nS(sP);
	//	}


};




#endif /* SRC_STREAMTREE_HPP_ */
