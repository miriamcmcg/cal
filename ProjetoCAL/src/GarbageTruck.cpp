#include "GarbageTruck.h"


unsigned int GarbageTruck::TruckCounter = 0;


GarbageTruck::GarbageTruck(unsigned int capacity) {
	this->ID = ++TruckCounter;
	this->capacity = capacity;
	this->carrying = 0;
	this->driverID = 0;
}


unsigned int GarbageTruck::getCapacity() const {
	return capacity;
}

unsigned int GarbageTruck::getCarrying() const {
	return carrying;
}

unsigned int GarbageTruck::getID() const {
	return ID;
}

bool GarbageTruck::addCarrying(unsigned int quantity) {

	if (carrying + quantity > capacity)
		return false;

	carrying += quantity;
	return true;
}


void GarbageTruck::empty(){
	carrying = 0;
}
