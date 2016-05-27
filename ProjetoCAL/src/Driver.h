#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>


using namespace std;


class Driver {

private:
	static int NrDrivers;
	string name;
	int ID;

public:
	Driver();
	Driver(string name);
	int getID();
	string getName();
};



#endif /* DRIVER_H_ */
