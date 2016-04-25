#include "GarbageDeposit.h"
#include <random>


GarbageDeposit::GarbageDeposit(unsigned long ID, double x, double y, double z, unsigned int maxCapacity, unsigned capacityOccupied) {

	if (capacityOccupied > maxCapacity)
		throw InvalidEntry();

	this->ID = ID;
	this->x = x;
	this->y = y;
	this->z = z;

	this->maxCapacity = maxCapacity;

	if (capacityOccupied != 0)
		this->capacityOccupied = capacityOccupied;
	else if (maxCapacity != 0)
		this->capacityOccupied = (rand() % maxCapacity);
	else
		this->capacityOccupied = 0;
};

bool GarbageDeposit::operator==(const GarbageDeposit &gd) const {
	return ID == gd.ID;
}

bool GarbageDeposit::operator!=(const GarbageDeposit &gd) const {
	return !(ID == gd.ID);
}

unsigned int GarbageDeposit::getCapacityOccupied() const {
	return capacityOccupied;
}

void GarbageDeposit::setCapacityOccupied(unsigned int capacityOccupied) {
	this->capacityOccupied = capacityOccupied;
}

double GarbageDeposit::getX() const{
	return this->x;
}

double GarbageDeposit::getY() const{
	return this->y;
}

double GarbageDeposit::getZ() const{
	return this->z;
}
unsigned long  GarbageDeposit::getID() const {
	return ID;
}

unsigned int  GarbageDeposit::getMaxCapacity() const {
	return maxCapacity;
}

void GarbageDeposit::setMaxCapacity(unsigned int maxCapacity) {
	this->maxCapacity = maxCapacity;
}


void GarbageDeposit::empty() {
	capacityOccupied = 0;
}


void GarbageDeposit::addCapacityOccupied (unsigned int quantity) {

	if (capacityOccupied + quantity >= maxCapacity)
		capacityOccupied = maxCapacity;
	else
		capacityOccupied += quantity;
}


string GarbageDeposit::coordsString() {
	stringstream ss;
	ss << "(" << x << "," << y << "," << z << ")";
	return ss.str();
}


string GarbageDeposit::print() const {
	stringstream ss;
	ss << ID;
	return ss.str();
}
