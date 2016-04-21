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
	TreatmentPlant(unsigned int ID, string name);
	const string& getName() const;
};


#endif /* SRC_TREATMENTPLANT_H_ */
