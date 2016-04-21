/*
 * RoadPointer.h
 *
 *  Created on: 20/04/2016
 *      Author: User
 */

#ifndef SRC_ROADPOINTER_H_
#define SRC_ROADPOINTER_H_


#include "Road.h"


class RoadPointer{
private:
	Road *road_ptr;

public:
	RoadPointer();
	RoadPointer(Road *r);
	Road *getPointer();
	bool operator==(const RoadPointer &r) const;
	double getWeight();


};


#endif /* SRC_ROADPOINTER_H_ */
