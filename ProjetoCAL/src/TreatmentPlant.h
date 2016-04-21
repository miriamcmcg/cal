/*
 * TreatmentPlant.h
 *
 *  Created on: 21/04/2016
 *      Author: User
 */

#ifndef SRC_TREATMENTPLANT_H_
#define SRC_TREATMENTPLANT_H_

#include <string>

using namespace std;

class TreatmentPlant : public GarbageDeposit {
private:
	string name;

public:
	TreatmentPlant(unsigned int ID, string name) : GarbageDeposit(ID, 0, 0) {
		this->name = name;
	}

	const string& getName() const {
		return name;
	}
};


#endif /* SRC_TREATMENTPLANT_H_ */
