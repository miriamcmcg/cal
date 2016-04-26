/*
 * TreatmentPlant.h
 *
 *  Created on: 21/04/2016
 *      Author: Bruno Barros, João Barbosa, Miriam Gonçalves
 */

#ifndef SRC_TREATMENTPLANT_H_
#define SRC_TREATMENTPLANT_H_

#include <string>
#include "GarbageDeposit.h"

using namespace std;
/**
 * Class TreatmentPlant
 */
class TreatmentPlant : public GarbageDeposit {
private:
	/** name of treatmentPlant*/
	string name;

public:
	/**
	 * TreatmentPlant constructor
	 * @param identifier of TreatmentPlant
	 * @param name of TreatmentPlant
	 * @param x coordinate of TreatmentPlant
	 * @param y coordinate of TreatmentPlant
	 * @param z coordinate of TreatmentPlant
	 */
	TreatmentPlant(unsigned int ID, string name, double x, double y, double z);
	/**
	 * getName function
	 * @return name of TreatmentPlant
	 */
	const string& getName() const;
	/**
	 * print function
	 * @return the string of the name of the TreatmentPlant to print
	 */
	virtual string print() const override;
};


#endif /* SRC_TREATMENTPLANT_H_ */
