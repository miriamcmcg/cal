//============================================================================
// Name        : EcoPoints.cpp
// Author      : Bruno Barros, Jo�o Barbosa, Miriam Gon�alves
//============================================================================

#include <iostream>
#include "Reader.h"
#include "GarbageCentral.h"
#include "Interface.h"

using namespace std;

int main() {
	srand(time(NULL));

//	Reader r;
//	r.readFiles();
// 	GarbageCentral GC(r);
//	mainMenu(GC);

	GarbageCentral GC = GarbageCentral();
	GC.test();

	return 0;
}
