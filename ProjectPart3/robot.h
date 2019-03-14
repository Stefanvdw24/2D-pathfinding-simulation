/* Filename: robot.h
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
#ifndef ROBOT_H_
#define ROBOT_H_
#define ACTION_WAIT 0
#define ACTION_FORWARD 1
#define ACTION_TURN_LEFT 2
#define ACTION_TURN_RIGHT 3


//structures

typedef struct RobotState_t {
	float t; // The time in seconds
	float x; // The horizontal position of the robot
	float y; // The vertical position of the robot
	float heading; // Angle robot is pointing, measured
	// counter-clockwise from X-axis
} RobotState;

typedef struct Robot_t {
	RobotState currentState; // The current state of the robot
	RobotState *stateHistory; // Pointer representing an array
	// containing all the past states
	// Add more structure members here
	float speed;
	float turnRate;
	int historyCapacity; //how many states the state history can contain
	int historyAmount; //amount of states are currently stored in the state history.
} Robot;

typedef struct Command_t {
	int robotAction; /* which action the robot should perform. The value of
	this member will always be one of the ACTION constants defined in the header file. */
	float robotActionDuration; /* how long the robot should perform this
	action, i.e. the duration of the command. */
} Command;


//function prototypes

Robot newRobot(float x0, float y0, float speed, float turnRate, int historyCapacity); //Create a new robot
void newRobotTest(float x0, float y0, float speed, float turnRate, int historyCapacity); //Test the creation of a new robot
Command initializeNewCommand(int action, float duration); //Initialize a new command
void initialiseNewCommandTest(int action, float duration); //Test the Initialization of a new command
int addCurrentStateToHistory(Robot *robotPtr); //adds the current state to a new entry in the history
int executeCommand(Robot *RobotPtr, Command theCommand); //Execute a command
void printStateHistory(Robot *robotPtr); //Print the state history on the screen
void turnByCertainAngle(Robot *robotPtr, float angle); //commands a robot to turn by a certain angle
void moveCertainDistance(Robot *robotPtr, float distance); //function which commands a robot to move a certain distance
void moveRobotTo(Robot *robotPtr, float x, float y); //move a robot to a given goal location
void followWaypointSequence(Robot *robotPtr, float xArr[], float yArr[], int waypointNumber); //function which allows the robot to follow a sequence of waypoints

#endif /* ROBOT_H_ */

