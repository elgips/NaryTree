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
		point3D 				P;
		node	<point3D>		nP(P);
		streamLine3D 			sP(P);
		node	<streamLine3D> 	nS(sP);
	}

};




#endif /* SRC_STREAMTREE_HPP_ */
