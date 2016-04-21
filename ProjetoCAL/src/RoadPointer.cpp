#include "RoadPointer.h"


RoadPointer::RoadPointer() { road_ptr = nullptr; };
RoadPointer::RoadPointer(Road *r){ road_ptr = r;}

Road *RoadPointer::getPointer(){return road_ptr;}

bool RoadPointer::operator==(const RoadPointer &r) const {
	return *road_ptr == *r.road_ptr;
}

double RoadPointer::getWeight(){
	return road_ptr->getWeight();
}
