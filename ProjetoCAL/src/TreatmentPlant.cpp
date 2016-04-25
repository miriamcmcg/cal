#include "TreatmentPlant.h"

TreatmentPlant::TreatmentPlant(unsigned int ID, string name,
		double x, double y, double z) : GarbageDeposit(ID, x, y, z, 0, 0) {
	this->name = name;
}

const string& TreatmentPlant::getName() const {
	return name;
}


string TreatmentPlant::print() const {
	return name;
}
