/* Filename: filehandling.c
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
#include "filehandling.h"
#define pi (22/7)

void writeStateHistoryText(char filename[], Robot *robotPtr) //prints State History to text file
{
	FILE *filePtr; //initialize a file pointer
	filePtr = fopen( filename, "w"); //open the file for writing as a text file, and store the return value of fopen in a file pointer.

	int counter; //initialize a counter

	fprintf(filePtr, "X\tY\tHeading\tTime\n");

	for ( counter=0 ; counter<((*robotPtr).historyAmount) ; counter++) //loop through each state history entry
	{
		fprintf(filePtr, "%.2f\t%.2f\t%.2f\t%.2f\n", (*robotPtr).stateHistory[counter].x,(*robotPtr).stateHistory[counter].y,
				((*robotPtr).stateHistory[counter].heading) * (180/(pi)), (*robotPtr).stateHistory[counter].t ); //print the state history of the entry
	}

	fclose(filePtr); //Close the file at the end of the function.
}

void writeStateHistoryBinary(char filename[], Robot *robotPtr) //prints state history to binary file
{
	FILE *filePtr; //initialize a file pointer
	filePtr = fopen( filename, "wb"); //open the file for writing as a binary file, and store the return value of fopen in a file pointer.
	/* At the start of the function, open the file for writing as a text file, and store the
	return value of fopen in a file pointer. */

	int counter; //counter

	fprintf(filePtr, "X\tY\tHeading\tTime\n"); //print heading

	for ( counter=0 ; counter<((*robotPtr).historyAmount) ; counter++) //loop through each history state
	{
		fwrite( &(*robotPtr).stateHistory[counter].x, sizeof(float), 1, filePtr); //print the x coordinate
		fwrite( &(*robotPtr).stateHistory[counter].y, sizeof(float), 1, filePtr); //print the y coordinate
		fwrite( &(*robotPtr).stateHistory[counter].heading, sizeof(float), 1, filePtr); //print the direction
		fwrite( &(*robotPtr).stateHistory[counter].t, sizeof(float), 1, filePtr); //print the elapsed time
	}

	fclose(filePtr); //Close the file at the end of the function.
}

void readWayPoints(char filename[], float **xArrPtr, float **yArrPtr, int *numWaypoints) //read waypoints from a file
{
	FILE *cfPtr; //initialize a file pointer
	int counter; //counter
	char commaChar; //variable for comma skipping

	cfPtr = fopen( filename, "r"); //open the file for reading, and store the return value of fopen in a file pointer.

	fscanf(cfPtr, "%d", &(*numWaypoints)); //scan the number of waypoints from the file

	//Declare two normal float pointers as local variables in the function:
	float *xPtr;
	float *yPtr;

	//Use malloc to allocate two arrays dynamically, and store the starting addresses in these pointers:
	xPtr = malloc(*numWaypoints * sizeof(float));
	yPtr = malloc(*numWaypoints * sizeof(float));

	//change the address stored at the address stored in each double pointer to the starting address of the array:
	*xArrPtr = xPtr;
	*yArrPtr = yPtr;

	for ( counter=0 ; counter<(*numWaypoints); counter++ ) //loop through each waypoint entry
	{
		fscanf(cfPtr, "%f%c%f", &xPtr[counter], &commaChar, &yPtr[counter]); //scan the coordinates form each line
	}

	free(xPtr); //free the pointers
	free(yPtr);

	fclose(cfPtr); //Close the file at the end of the function.
}
