/*
 * EtzNary.h
 *
 *  Created on: Dec 9, 2020
 *      Author: gips
 */

#ifndef ETZNARY_H_
#define ETZNARY_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cstdio>
#include <random>
#include<fstream>
#include<sstream>

using namespace std;
template <typename T>
class node{
public:
	T 				 value;
	vector<node*> children;
	node* 			parent;
	bool notMyPapa(node* _leaf,node* _branch){
		node* ancestor=_branch;
		bool fatherLikeSon=false;
		while(ancestor!=NULL){
			fatherLikeSon=(fatherLikeSon||(_leaf==ancestor));
		}
		return fatherLikeSon;
	}
	node(){
		children.clear();
		parent=NULL;
	}
	node(node* _parent){
		if(notMyPapa(this, _parent)){
			children.clear();
			parent=_parent;}
		else{
			invalid_argument("there is a loop in the tree");
			terminate();
		}}
	node(T _value){
		value=_value;
		children.clear();
		parent=NULL;
	}
	node(T _value,node* _parent){
		if(notMyPapa(this, _parent)){
			value=_value;
			children.clear();
			parent=_parent;}
		else{
			invalid_argument("there is a loop in the tree");
			terminate();
		}
	}
	//	node<T> node::newNode(T _value);
	void appendChild(T _value){
		node temp(_value,this);
		this->children.push_back(&temp);
	}
	void appendChild(node* _child){
		if(notMyPapa(_child, this)){
		_child->parent=this;
		this->children.push_back(_child);}
		else{
			invalid_argument("there is a loop in the tree");
			terminate();
			}
		}
	void TreePrintAux(node* _child,ofstream* out){
		if(!children.empty()){
			typename vector<node<T>*>::iterator it;
			*out<<_child->value;
			for(it=children.begin();it!=children.end();it++){
				TreePrintAux(it);
			}
		}
	}
	void topToBottom2Text(string _fileName){
		ofstream out(_fileName);
		out<<this->value;
		if(!children.empty()){
			typename vector<node<T>*>::iterator it;
			for(it=children.begin();it!=children.end();it++){
				TreePrintAux(it,&out);
			}
		}
		out.close();
	}
};



#endif /* ETZNARY_H_ */
