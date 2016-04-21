#include "GarbageDeposit.h"
#include <random>


GarbageDeposit::GarbageDeposit(unsigned long ID, unsigned int maxCapacity = 4500, unsigned capacityOccupied = 0) {
	this->ID = ID;
	this->maxCapacity = maxCapacity;

	if (capacityOccupied != 0)
		this->capacityOccupied = capacityOccupied;
	else
		this->capacityOccupied = (rand() % 3000) + 100;
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
	// TODO THROW
	if (capacityOccupied + quantity > maxCapacity)
		;

	capacityOccupied += quantity;
}
