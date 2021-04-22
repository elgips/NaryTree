/*
 * main.cpp
 *
 *  Created on: Dec 31, 2020
 *      Author: gips
 */
#include "EtzNary.hpp"
#include "streamTree.hpp"
#include <cstdio>
//typedef node<double> ND;

//ND string2nodes(string _s){
//	ND *temp=new ND;
//	typename vector<ND*>::iterator iND;
//	size_t it,it2;
//	string stTem;
//	char x,xsign;
//
//}
const int size(){
	return 3;
}

//double* values(const int _size){
//	double *temp =new double[_size];
////	const int sz=_size;
////	static double temp[3];
//	for(int i=0;i<_size;i++){
//		temp[i]=0.23*(double)i;
//	}
//	return temp;
//}
//
//const static double* Q=values(3);

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
//	NodeP *P=NodeP::newNode(point3D(),NULL);
//	NodeP *P1=NodeP::newNode(point3D(),P);
//	point3D *temp;
//	temp=&(P1->value);
//	NodeS *S=NodeS::newNode(streamLine3D(&(P->value)),NULL);
//	NodeS *S1=NodeS::newNode(streamLine3D(), S);
//	streamLine3D::childStream(&(P1->value),&(S->value),&(S1->value), 0.2);
//	point3D p=point3D(1,2,3);
//	streamTree3D T(P,S);
	  std::ifstream ifs("../streamTree3D_withWidth_2_blender/LSYOUT.txt");
	  std::string s( (std::istreambuf_iterator<char>(ifs) ),
	                       (std::istreambuf_iterator<char>()    ) );

//	string s="F(0.008100)+F(0.012373)--F(0.012373)+F(0.018900)+F(0.012373)+F(0.018900)--F(0.018900)+F(0.028870)--F(0.012373)+F(0.018900)--F(0.018900)+F(0.028870)+F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.012373)+F(0.018900)--F(0.018900)+F(0.028870)+F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)--F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)--F(0.012373)+F(0.018900)--F(0.018900)+F(0.028870)+F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)--F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)--F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)+F(0.012373)+F(0.018900)--F(0.018900)+F(0.028870)+F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)--F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)--F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)--F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)--F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)--F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)+F(0.067364)+F(0.102900)--F(0.102900)+F(0.157183)--F(0.012373)+F(0.018900)--F(0.018900)+F(0.028870)+F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)--F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)--F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)--F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)--F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)--F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)+F(0.067364)+F(0.102900)--F(0.102900)+F(0.157183)+F(0.018900)+F(0.028870)--F(0.028870)+F(0.044100)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)--F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)+F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)--F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)+F(0.067364)+F(0.102900)--F(0.102900)+F(0.157182)--F(0.028870)+F(0.044100)--F(0.044100)+F(0.067364)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)--F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)+F(0.067364)+F(0.102900)--F(0.102900)+F(0.157182)+F(0.044100)+F(0.067364)--F(0.067364)+F(0.102900)+F(0.067364)+F(0.102900)--F(0.102900)+F(0.157182)--F(0.067364)+F(0.102900)--F(0.102900)+F(0.157182)+F(0.102900)+F(0.157182)--F(0.157182)+F(0.240100)";
	string s1="../streamTree3D_withWidth_2_blender/Streams.txt";
	string s2="../streamTree3D_withWidth_2_blender/Points.txt";
	streamTree3D *T1=streamTree3D::stringTurtling2StreamT(s);
	streamTree3D::streamExport(s1, T1);
	streamTree3D::pointExport(s2, T1);
//	cout <<Q[1];//	float s=10.3;
//	const char* format="%f\n";
//	printf(format,s);





	return 0;
}



