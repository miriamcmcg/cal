#include "Road.h"


Road::Road()
{
	ID = 0;
	name = "";
	distance = 0;
	avg_speed = 0;
	available = true;
};

Road::Road(unsigned long ID, string name, double distance, double speed)
{
	this->ID = ID;
	this->name = name;
	this->distance = distance;
	avg_speed = speed;
	available = true;
};

bool Road::operator==(const Road &r) const {
	return ID == r.ID;
}

unsigned long Road::getID() const {
	return ID;
}

const string& Road::getName() const {
	return name;
}

double Road::getWeight() {

	if (!available || avg_speed == 0)
		return DOUBLE_MAX;

	return distance / avg_speed;
}

void Road::setAvgSpeed(double speed) {
	avg_speed = speed;
}

void Road::setAvailable(bool av) {
	available = av;
}


string Road::print() const {
	return name;
}
