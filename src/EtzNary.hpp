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
	T 				value;
	vector<node*> 	children;
	node* 			parent;

	static node* newNode(T _value,node* _parent){
		node* temp=new node;
		temp->value=_value;
		temp->parent=_parent;
		return temp;
	}
	static void appendChild(node* _parent,node* _child){
		if(notMyPapa(_parent, _child)){
			_child->parent=_parent;
			_parent->children.push_back(_child);
		}
		else{
			invalid_argument("there is a loop in the tree");
			terminate();
		}
	}
	static bool notMyPapa(node* _parent,node* _child){
		node* ancestor=_parent;
		bool fatherLikeSon=false;
		while(ancestor!=0x0){
			fatherLikeSon=(fatherLikeSon||(_child==ancestor));
			if(fatherLikeSon)return !fatherLikeSon;
			ancestor=ancestor->parent;
		}
		return !fatherLikeSon;
	}
	static bool isMember(node* _parent,node* _child){
		bool x=(_parent==_child);
		typename vector<node<T>*>::iterator it;
		if(x){
			if(!_parent->children.empty()){
				for(it=_parent->children.begin();(it!=_parent->children.end())&&(!x);it++){
					x=+isMember(*it,_child);
				}
			}
		}
		return x;
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
	static void copySubTreeAux(node* _root,node* _parent){
		node* n=newNode(_root->value, _parent);
		_parent->appendChild(_parent, n);
		typename vector<node<T>*>::iterator it;
		for(it=_root->children.begin();it!=_root->children.end();it++){
			copySubTreeAux(*it,n);
		}
	}
	node* copySubTree(node* _root){
		node *n=newNode(_root->value,NULL);
		typename vector<node<T>*>::iterator it;
		for(it=_root->children.begin();it!=_root->children.end();it++){
			copySubTreeAux((*it),n);
		}
		return n;
	}

	static void cutBranch(node* _branch){
		node* parent=_branch->parent;
		bool f=false;
		_branch->parent=NULL;
		typename vector<node<T>*>::iterator it;
		for(it=parent->children.begin();(it!=parent->children.end())&&(!f);it++){
			if(&(*it)==_branch){
				parent->children.erase(it);
				f=true;
			}
		}
	}
};



#endif /* ETZNARY_H_ */
