/* Filename: robot.c
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
#include "robot.h"
#include "mymath.h"


//functions

Robot newRobot(float x0, float y0, float speed, float turnRate, int historyCapacity) //Create a new robot
{
	Robot myRobot; //declare a new robot

	myRobot.currentState.x = x0; //Set the initial x coordinate of the robot = the one passed to the function
	myRobot.currentState.y = y0; //Set the initial y coordinate of the robot = the one passed to the function
	myRobot.currentState.heading = 0; //Set the initial direction of the robot = the one passed to the function
	myRobot.currentState.t = 0; //set the elapsed time = o

	myRobot.speed = speed; //Set the speed of the robot = the one passed to the function
	myRobot.turnRate = turnRate; //Set the turn rate of the robot = the one passed to the function

	myRobot.historyAmount = 0; //Set the initial number of history entries = 0
	myRobot.historyCapacity = historyCapacity; //Set the maximum number of history entries = the amount passed to the function

	myRobot.stateHistory = malloc(historyCapacity*sizeof(RobotState)); /* Allocate a block
	of memory large enough to hold this number of RobotState structures, and store the starting address of
	this block in the stateHistory pointer of the Robot. */

	addCurrentStateToHistory(&myRobot); //Set the initial state of the robot to the first entry of the state history

	return myRobot;
} //end newRobot

void newRobotTest(float x0, float y0, float speed, float turnRate, int historyCapacity) //Test the creation of a new robot
{
	Robot testRobot = newRobot(x0, y0, speed, turnRate, historyCapacity); //declare a new robot and set its properties to the values passed to the function

	//Print test results:
	printf("\nCurrent state:");
	printf("\n	x = %.2f", testRobot.currentState.x);
	printf("\n	y = %.2f", testRobot.currentState.y);
	printf("\n	Heading = %.2f", testRobot.currentState.heading);
	printf("\n 	t = %.2f", testRobot.currentState.t);
	printf("\nSpeed: %.2f", testRobot.speed);
	printf("\nTurn rate: %.2f degrees/s", testRobot.turnRate);
	printf("\nStarting address of state history: %p", testRobot.stateHistory);
	printf("\nHistory capacity: %d", testRobot.historyCapacity);
	printf("\nHistory used: %d\n", testRobot.historyAmount);

	free(testRobot.stateHistory); //free state history
} //end newRobotTest

Command initializeNewCommand(int action, float duration) //Initialize a new command
{
	Command myCommand; //Command variable to be returned

	myCommand.robotAction = action; //Set the command variable's action = to the action passed to the function
	myCommand.robotActionDuration = duration; //Set the command variable's duration = to the duration passed to the function

	return myCommand; //return the command variable
} //initializeNewCommand

void initialiseNewCommandTest(int action, float duration) //Test the Initialization of a new command
{
	Command testCommand = initializeNewCommand(action, duration);

	//Print test results:
	printf("\nTest Command:");
	printf("\nAction: %d", testCommand.robotAction);
	printf("\nDuration: %f seconds\n", testCommand.robotActionDuration);
} //initialiseNewCommandTest

int addCurrentStateToHistory(Robot *robotPtr) //adds the current state to a new entry in the history
{
	int success;

	if ( ((*robotPtr).historyAmount) < ((*robotPtr).historyCapacity) ) //if number of history entries < historyCapacity
	{
		(*robotPtr).stateHistory[(*robotPtr).historyAmount] = (*robotPtr).currentState; //set stateHistory[statesInHistory] = currentState
		(*robotPtr).historyAmount++; //increment the number of history entries
		success = 1; //set success = 1
	}
	else
	{
		success = 0; //set success = 0
	}
	return success;  //return success
} //end

int executeCommand(Robot *robotPtr, Command theCommand) //Execute a command
{
	float *headingPtr;
	headingPtr = &(*robotPtr).currentState.heading; //Create a pointer to the robot's direction

	if ( (theCommand.robotAction==0 || theCommand.robotAction==1 || theCommand.robotAction==2 || theCommand.robotAction==3) && theCommand.robotActionDuration>0)
	{
		if(theCommand.robotActionDuration>0)
		{
			(*robotPtr).currentState.t += theCommand.robotActionDuration; //Add the action duration to the robot's elapsed time regardless of which action was chosen
			switch (theCommand.robotAction) //update robot state according to the chosen action
			{
			case 1: //if command is move
				(*robotPtr).currentState.y += (*robotPtr).speed * theCommand.robotActionDuration * sin((*robotPtr).currentState.heading); //Calculate and the movement's y component and add it to the robot's current y coordinate
				(*robotPtr).currentState.x += (*robotPtr).speed * theCommand.robotActionDuration * cos((*robotPtr).currentState.heading); //Calculate and the movement's x component and add it to the robot's current x coordinate
				break;
			case 2: //if command is turn left
				(*robotPtr).currentState.heading += (*robotPtr).turnRate * theCommand.robotActionDuration; //add the change in dirction to the robot's current direction
				trimRadians(headingPtr); //Trim radians if necessary
				break;
			case 3: //if command is turn right
				(*robotPtr).currentState.heading -= (*robotPtr).turnRate * theCommand.robotActionDuration; //subtract the change in dirction from the robot's current direction
				trimRadians(headingPtr); //Trim radians if necessary
				break;
			}
			addCurrentStateToHistory(robotPtr); //add the new state to the history
		}
	}
	return 1;

} //executeCommand


void printStateHistory(Robot *robotPtr) //Print the state history on the screen
{
	int counter; //counter
	float *trimRadPtr; //create a pointer for use by trimRadians

	printf("X\tY\tHeading\tTime\n"); //Print the heading

	for ( counter=0 ; counter<((*robotPtr).historyAmount) ; counter++) //loop through each history entry
	{
		trimRadPtr = &(*robotPtr).stateHistory[counter].heading; //point the trimRadPtr to the Robot's direction
		trimRadians(trimRadPtr); //Trim Radians if necessary
		printf("%.2f\t%.2f\t%.2f\t%.2f\n", (*robotPtr).stateHistory[counter].x,(*robotPtr).stateHistory[counter].y,
				((*robotPtr).stateHistory[counter].heading)*(180/M_PI), (*robotPtr).stateHistory[counter].t); //print the history entry on the screen
	}
} //end printStateHistory


void turnByCertainAngle(Robot *robotPtr, float angle) //commands a robot to turn by a certain angle
{
	Command theCommand; //Create a new command variable
	float actionDuration; //Create a duration variable

	actionDuration = angle / (*robotPtr).turnRate; //Calculate the action's duration

	if (angle > 0) //if the angle
	{
		theCommand = initializeNewCommand(ACTION_TURN_LEFT, actionDuration); //Initialize a command to turn left
	}
	else //else
	{
		theCommand = initializeNewCommand(ACTION_TURN_RIGHT, actionDuration); //Initialize a command to turn right
	}

	executeCommand(robotPtr, theCommand); //Execute the command
} //end turnByCertainAngle

void moveCertainDistance(Robot *robotPtr, float distance) //function which commands a robot to move a certain distance
{
	Command theCommand; //Create a new command variable
	float actionDuration; //Create a duration variable

	actionDuration = distance / (*robotPtr).speed; //Calculate the action's duration

	theCommand = initializeNewCommand( ACTION_FORWARD, actionDuration); //Initialize a forward command

	executeCommand(robotPtr, theCommand); //Execute the command
} //end moveCertainDistance

void moveRobotTo(Robot *robotPtr, float x, float y) //move a robot to a given goal location
{
	float dx, dy;
	float angleChange;
	float newHeading;
	float distance;

	dx = x - (*robotPtr).currentState.x; //Calculate required x Change
	dy = y - (*robotPtr).currentState.y; //Calculate required y Change

	newHeading = atan2(dy,dx); //Calculate required direction
	angleChange = newHeading - (*robotPtr).currentState.heading; //Calculate Required Angle Change
	turnByCertainAngle(robotPtr, angleChange); //Perform Angle Change

	distance = pow( ((dx*dx) + (dy*dy)) , 0.5 ); //Calculate move distance
	moveCertainDistance(robotPtr, distance); //Perform move command
} //end moveRobotTo

void followWaypointSequence(Robot *robotPtr, float xArr[], float yArr[], int waypointNumber) //function which allows the robot to follow a sequence of waypoints
{
	int counter; //declare counter

	for( counter=0 ; counter<waypointNumber ; counter++) //loop through each waypoint
	{
		moveRobotTo(robotPtr, xArr[counter], yArr[counter]); //Move robot to given location
	}
} //end followWaypointSequence

