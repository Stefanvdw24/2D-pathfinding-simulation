/* Filename: pathplanning.h
* Date: 16 October 2012
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


#ifndef PATHPLANNING_H_
#define PATHPLANNING_H_
#define MAX_ENV_WIDTH 20
#define MAX_ENV_HEIGHT 20


//Structures

typedef struct Action_t{
int dx, dy;
float length;
char name[2];
} Action;

typedef struct Environment_t{
int width, height;
int xStart,yStart,xGoal,yGoal;
int occupancyMap[MAX_ENV_WIDTH][MAX_ENV_HEIGHT];
Action actionMap[MAX_ENV_WIDTH][MAX_ENV_HEIGHT];
} Environment;


//Function prototypes

void printOccMap(Environment *envPtr);
void printActionMap(Environment *envPtr);
Action* defaultActionArray();
int dijkstra(Environment *envPtr,Action *actionArray,int numActions);

Environment newEnvironment(char mapFileName[], int x0, int y0, int xG, int yG); //Read the environment from a file and create the necessary maps
void searchActionMap(Environment *envPtr,float** xArrPtr, float** yArrPtr, int* numWaypoints); //Search the action map


#endif /* PATHPLANNING_H_ */
