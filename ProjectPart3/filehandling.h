/* Filename: filehandling.h
 * Date: 9 October 2012
 * Name: D.S. van der Westhuizen
 * Student number: 17158680
 * ------------------------------------------------------
 * By submitting this file electronically, I declare that
 * it is my own original work, and that I have not copied
 * any part of it from another source, unless instructed
 * to do so in the assignment.
 * ------------------------------------------------------
 * Description:
 * <<Enter program description here>>
 * ------------------------------------------------------
 */


#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "robot.h"
#ifndef FILEHANDLING_H_
#define FILEHANDLING_H_

void writeStateHistoryText(char filename[], Robot *robotPtr); //prints State History to text file
void writeStateHistoryBinary(char filename[], Robot *robotPtr); //prints state history to binary file
void readWayPoints(char filename[], float **xArrPtr, float **yArrPtr, int *numWaypoints); //read waypoints from a file

#endif /* FILEHANDLING_H_ */
