/*
 * Interface.h
 *
 *  Created on: 21/04/2016
 *      Author: Bruno
 */

#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <windows.h>

#include "GarbageCentral.h"


using namespace std;

void ClearScreen();
void getCursorXY(int &x, int&y);
void gotoXY(int x, int y);
void clearline();
void clearline(int x, int y);
void waitReturn();

vector<unsigned int> manualPicking(GarbageCentral& gc, unsigned int truck_id);
void getEntry(unsigned int &entrada);
void getEntry(int &entrada);
void getEntry(int &entrada, int start, int end);
void mainMenu(GarbageCentral& gc);
void createPickRoute(GarbageCentral& gc);
void updateCapacityOccupied(GarbageCentral& gc);
void updateAvgSpeedRoad(GarbageCentral& gc);
void updateAvailableRoad(GarbageCentral& gc);


#endif /* SRC_INTERFACE_H_ */
