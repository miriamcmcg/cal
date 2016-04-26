/*
 * Interface.h
 *
 *  Created on: 21/04/2016
 *      Author: Bruno Barros, Jo�o Barbosa, Miriam Gon�alves
 */

#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <windows.h>
#include "graphviewer.h"
#include "GarbageCentral.h"


#define IMG_WIDTH	2713
#define	IMG_HEIGHT	1452

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
void displayGraphViewer(vector<Section> route, const GarbageCentral& gc);

#endif /* SRC_INTERFACE_H_ */
