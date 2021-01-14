/*
 * main.cpp
 *
 *  Created on: Dec 31, 2020
 *      Author: gips
 */
#include "EtzNary.hpp"
#include "streamTree.hpp"
//typedef node<double> ND;

//ND string2nodes(string _s){
//	ND *temp=new ND;
//	typename vector<ND*>::iterator iND;
//	size_t it,it2;
//	string stTem;
//	char x,xsign;
//
//}

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
	NodeP *P=NodeP::newNode(point3D(),NULL);
//	NodeP *P1=NodeP::newNode(point3D(),P);
//	point3D *temp;
//	temp=&(P1->value);
	NodeS *S=NodeS::newNode(streamLine3D(&(P->value)),NULL);
//	NodeS *S1=NodeS::newNode(streamLine3D(), S);
//	streamLine3D::childStream(&(P1->value),&(S->value),&(S1->value), 0.2);
//	point3D p=point3D(1,2,3);
	streamTree3D T(P,S);
	string s="FF(0.2){Um(0.7)Hm(0.8)FUm(0.7)Hm(0.8)F(0.7)FFF(0.2)}";
	streamTree3D *T1=streamTree3D::stringTurtling2StreamT(s);





	return 0;
}



