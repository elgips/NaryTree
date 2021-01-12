/*
 * main.cpp
 *
 *  Created on: Dec 31, 2020
 *      Author: gips
 */
#include "EtzNary.hpp"
#include "streamTree.hpp"


int main(){
	//	double X=1.2,X1=3,X2=4;
	//	node <double> nX(1.5),nX1(0.2),Nx2(0.8);
	//	nX.appendChild(new node<double>(0.1), &nX);
	//	nX.appendChild(new node<double>(0.5), &nX);
	//	nX.appendChild(new node<double>(0.8), &nX);
	//	node <double> *n;//=*(nX.children.begin());
	////	n=&(*(nX.children.begin()));
	////	n->appendChild(new node<double>(0.25), n);
	////	n->appendChild(new node<double>(0.8),n);
//	Node* n=Node::newNode(0.3,NULL);
//	n->children.push_back(Node::newNode(0.2,n));
//	n->children.push_back(Node::newNode(0.4,n));
//	n->children.push_back(Node::newNode(0.3,n));
//	n->children.push_back(Node::newNode(0.9,n));
//	n->children.push_back(Node::newNode(0.8,n));
//	Node* n1=Node::newNode(0.3,NULL);
//	n1->children.push_back(Node::newNode(0.2,n1));
//	n1->children.push_back(Node::newNode(0.4,n1));
//	n1->children.push_back(Node::newNode(0.3,n1));
//	n1->children.push_back(Node::newNode(0.9,n1));
//	n1->children.push_back(Node::newNode(0.8,n1));
//	Node::appendChild(n,n1);
	NodeP *P=NodeP::newNode(point3D(1,2,3),NULL);
	NodeS *S=NodeS::newNode(streamLine3D(&(P->value)),NULL);
//	point3D p=point3D(1,2,3);
	streamTree3D T(P,S);





	return 0;
}



