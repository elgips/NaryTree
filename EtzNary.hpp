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
	T* 				 value;
	vector<node*> children;
	node* 			parent;
	bool notMyPapa(node* _leaf,node* _branch){
		node* ancestor=_branch;
		bool fatherLikeSon=false;
		while(ancestor!=0x0){
			fatherLikeSon=(fatherLikeSon||(_leaf==ancestor));
			if(fatherLikeSon)return !fatherLikeSon;
			ancestor=ancestor->parent;
		}
		return !fatherLikeSon;
	}
	node(){
		value=NULL;
		children.clear();
		parent=NULL;
	}

	node(node* _parent){
		value=NULL;
		if(notMyPapa(this, _parent)){
			children.clear();
			parent=_parent;}
		else{
			invalid_argument("there is a loop in the tree");
			terminate();
		}}
	node(T* _value){
		value=_value;
		children.clear();
		parent=NULL;
	}
	node(T _value){
		value=new T;
		*value=_value;
		children.clear();
		parent=NULL;
	}


	node(T* _value,node* _parent){
		if(notMyPapa(this, _parent)){
			value=_value;
			children.clear();
			parent=_parent;}
		else{
			invalid_argument("there is a loop in the tree");
			terminate();
		}
	}
	node(T _value,node* _parent){
		if(notMyPapa(this, _parent)){
			value=new T;
			*value=_value;
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
	void appendChild(T* _value){
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
	void appendChildren(vector<node*> _c){
		typename vector<node<T>*>::iterator it;
		for(it=_c.begin();it!=_c.end();it++){
			if(notMyPapa(*it, this)){
				*it->parent=this;
				this->children.push_back(*it);}
			else{
				invalid_argument("there is a loop in the tree");
				terminate();
			}
		}
	}
	void appendChild(node* _child,node* _parent){
		if(notMyPapa(_child, _parent)){
			_child->parent=_parent;
			_parent->children.push_back(_child);}
		else{
			invalid_argument("there is a loop in the tree");
			terminate();
		}
	}
	void TreePrintAux(node* _child,ofstream* out){
		*out<<endl;
		*out<<*(_child->value);
		if(!_child->children.empty()){
			typename vector<node<T>*>::iterator it;
			for(it=_child->children.begin();it!=_child->children.end();it++){
				TreePrintAux(*it,out);
			}
		}
	}
	void topToBottom2Text(string _fileName){
		ofstream out( _fileName.c_str(), ios::out );
		out<<*(this->value);
		if(!children.empty()){
			typename vector<node<T>*>::iterator it;
			for(it=children.begin();it!=children.end();it++){
				TreePrintAux(*it,&out);

			}
		}
		out.close();
	}
	bool isMember(node* _n){
		bool x=false;
		x=x||*this=_n;
		if(!this->children.empty()){
			typename vector<node<T>*>::iterator it;
			for(it=children.begin();it!=children.end();it++){
				x=x||isMember(it);
			}
		}
		return x;
	}
};



#endif /* ETZNARY_H_ */
