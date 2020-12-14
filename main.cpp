/*
 * main.cpp
 *
 *  Created on: Dec 9, 2020
 *      Author: gips
 */

#include "EtzNary.hpp"
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
//template <typename T>
//class node{
//public:
//	T 				 value;
//	vector<node*> children;
//	node();
//	node(T _value);
////	node<T>* node::newNode(T _value);
//
//	void appendChild(T _value);
//	void appendChild(node _child);
//};
//template <typename T>
//node<T>::node(){}
//template <typename T>
//node<T>::node(T _value){
//	value=_value;
//}
//template <typename T>
//void node<T>::appendChild(T _value){
//	node temp(_value);
//	this->children.push_back(&temp);
//}
//template <typename T>
//void node<T>::appendChild(node _child){
//	this->children.push_back(&_child);
//}

int main(){
	node<int> x1(1),x2(2);
	x1.appendChild(3);
	node<string> y("1");
	y.appendChild(&y);
//	vector<node<int>> z;

	cout<< "too slow";
	return 0;
}

