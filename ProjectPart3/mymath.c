/* Filename: mymath.c
* Date: 3 October 2012
* Name: D.S. van der Westhuizen
* Student number: 17158680
* ------------------------------------------------------
* By submitting this file electronically, I declare that
* it is my own original work, and that I have not copied
* any part of it from another source, unless instructed
* to do so in the assignment.
* ------------------------------------------------------
* Description:
* ------------------------------------------------------
*/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "mymath.h"


//functions


void trimRadians(float *rad) // begin trimRadians(rad by reference)
{
		while ( *rad <= -M_PI) { //while the angle less than -180 degrees
			*rad += (2 * M_PI); //increase the ngle by 360 degrees
		}
		while ( *rad > M_PI) { //while the angle greater than -180 degrees
			*rad -= (2 * M_PI); //decrease the ngle by 360 degrees
		}
}  // end function trimRadians


void testTrimRad() //Test function for angle trimming
{

	float testAngle1 = (5.5*M_PI); //declare first test angle
	float testAngle2 = -(2.75*M_PI); //declare second test angle
	float *testAngle1Ptr;
	testAngle1Ptr = &testAngle1;
	float *testAngle2Ptr;
	testAngle2Ptr = &testAngle2;
	printf("\nThe 2 test angles are %.2f and %.2f\n",( testAngle1*(360/(2*M_PI))), (testAngle2*(360/(2*M_PI))) ); //print the test angles
	trimRadians(testAngle1Ptr);
	trimRadians(testAngle2Ptr);
	printf("The 2 trimmed angles are %.2f and %.2f\n",( testAngle1*(360/(2*M_PI))), (testAngle2*(360/(2*M_PI))) ); //print the trimmed angles
} //end testTrimrad

