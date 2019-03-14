#ifndef MENU_H_
#define MENU_H_

#include<stdio.h>
#include<stdlib.h>
#include "mymath.h"
#include "robot.h"
#include "filehandling.h"
#include "pathplanning.h"
#include "datastructs.h"

void mainMenu();

void demoPart1();
void demoPart2();
void demoPart3();
void demoExtras();

void demoTrimRad();
void demoNewCommand();
void demoExecCommand();

void demoWriteHist();
void readBinary(char *filename);
void readText(char *filename);
void demoReadWaypoints();
void demoMoves();
void demoFollowWaypoints();

void demoQueue();
void demoEnvironment();

#endif /* MENU_H_ */
