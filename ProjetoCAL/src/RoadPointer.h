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
	RoadPointer() { road_ptr = nullptr; };
	RoadPointer(Road *r){ road_ptr = r;}

	Road *getPointer(){return road_ptr;}

	bool operator==(const RoadPointer &r) const {
		return *road_ptr == *r.road_ptr;
	}

	double getWeight(){
		return road_ptr->getWeight();
	}
};


#endif /* SRC_ROADPOINTER_H_ */
