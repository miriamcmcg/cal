#include "Driver.h"

int Driver::NrDrivers = 0;


Driver::Driver() {
	this->ID = -1;
	this->name = "unnamed";
}

Driver::Driver(string name)
{
	NrDrivers++;
	this->name = name;
	this->ID = NrDrivers;
}


int Driver::getID() {
	return this->ID;
}

string Driver::getName()
{
	return this->name;
}
