/*
 * RoadPointer.h
 *
 *  Created on: 20/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
 */

#ifndef SRC_ROADPOINTER_H_
#define SRC_ROADPOINTER_H_


#include "Road.h"

/**
 *Class RoadPointer
 */
class RoadPointer{
private:
	/**
	 * pointer to road */
	Road *road_ptr;

public:
	/**
	 * Default constructor of RoadPointer*/
	RoadPointer();
	/*
	 * RoadPointer constructor
	 * @param road pointer
	 */
	RoadPointer(Road *r);
	/*
	 * getPointer function
	 * @return pointer to road
	 */
	Road *getPointer();
	/**
	 * equal operator
	 * @param r road pointer
	 *
	 * verify if two road pointers are equal
	 */
	bool operator==(const RoadPointer &r) const;
	/**
	 * getWeight function
	 * @return weight of road pointer
	 */
	double getWeight();


};


#endif /* SRC_ROADPOINTER_H_ */
