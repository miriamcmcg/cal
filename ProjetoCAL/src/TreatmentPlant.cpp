#include "TreatmentPlant.h"

TreatmentPlant::TreatmentPlant(unsigned int ID, string name) : GarbageDeposit(ID, 0, 0) {
	this->name = name;
}

const string& TreatmentPlant::getName() const {
	return name;
}
