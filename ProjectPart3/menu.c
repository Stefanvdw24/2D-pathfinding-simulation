#include "menu.h"

/*
 * You were not given names for some of the functions and structure members you
 * had to create In this file, the names of these files have been replaced by
 * symbols that start and end with underscores.
 *
 * Make the following replacements using Ctrl-F (including the underscores):
 *  _nc_ => your function which creates a command
 *  _xc_ => your function which executes a command
 *  _ph_ => your function which prints the state history
 *  _wb_ => your function which writes the state history to a binary file
 *  _ta_ => your function which turns by a certain angle
 *  _md_ => your function which moves by a certain distance
 *  _fw_ => your function which follows a list of waypoints
 *  _fq_ => your function which frees the nodes of a queue
 *
 *  _max_ => The maximum capacity of the state history
 *  _act_ => The action member of the Command structure
 *  _dur_ => The duration member of the Command structure
 *
 * If you have given any functions different names than those used in the project 
 * spec, that's fine - just replace the names in this file with the correct ones.
 *
 * Also, you can add code to test any extra features in the demoExtras function.
 */

void mainMenu()
{
	int choice;
	// Display the main menu choices
	printf("\nMain menu\n");
	printf("1. Test Part 1\n");
	printf("2. Test Part 2\n");
	printf("3. Test Part 3\n");
	printf("4. Test Extras\n");
	printf("Enter choice:\n");
	scanf("%d", &choice);

	// Call the appropriate sub-menu function
	switch(choice){
	case 1:
		demoPart1();
		break;
	case 2:
		demoPart2();
		break;
	case 3:
		demoPart3();
		break;
	case 4:
		demoExtras();
		break;
	}
}

void demoPart1()
{
	int choice;
	// Display the Part 1 menu options
	printf("\nPart 1 menu\n");
	printf("1. Test trimRadians\n");
	printf("2. Test new command\n");
	printf("3. Test execute command\n");
	printf("Enter choice:\n");
	scanf("%d", &choice);

	// Call the appropriate sub-menu function
	switch(choice){
	case 1:
		demoTrimRad();
		break;
	case 2:
		demoNewCommand();
		break;
	case 3:
		demoExecCommand();
		break;
	}
}

void demoPart2()
{
	int choice;
	// Display the Part 2 menu options
	printf("\nPart 2 menu\n");
	printf("1. Test write history\n");
	printf("2. Test read waypoints\n");
	printf("3. Test turn/move/moveTo\n");
	printf("4. Test follow waypoints\n");

	printf("Enter choice:\n");
	scanf("%d", &choice);

	// Call the appropriate sub-menu function
	switch(choice){
	case 1:
		demoWriteHist();
		break;
	case 2:
		demoReadWaypoints();
		break;
	case 3:
		demoMoves();
		break;
	case 4:
		demoFollowWaypoints();
		break;
	}
}

void demoPart3()
{
	int choice;
	// Display the Part 3 menu options
	printf("\nPart 3 menu\n");
	printf("1. Test queue\n");
	printf("2. Test environment\n");

	printf("Enter choice:\n");
	scanf("%d", &choice);

	// Call the appropriate sub-menu function
	switch(choice){
	case 1:
		demoQueue();
		break;
	case 2:
		demoEnvironment();
		break;
	}
}

void demoExtras()
{

}

void demoTrimRad()
{
	int cont;
	printf("\nTrim radians menu\n");
	// Keep asking for angles to trim until user chooses to exit
	do{
		float angle;

		// Read angle in degrees
		printf("\nEnter angle in degrees:\n");
		scanf("%f", &angle);

		// Print first half of message with original angle (no newline)
		printf("%.2f degrees trimmed = ", angle);

		// Convert to radians, trim, and convert back to degrees
		angle *= M_PI/180;
		trimRadians(&angle);
		angle *= 180/M_PI;

		// Print second half of message with trimmed angle
		printf("%.2f degrees\n", angle);

		// Ask if user wants to trim another angle
		printf("Trim another? (1/0)\n");
		scanf("%d", &cont);
	} while(cont);
}

void demoNewCommand()
{
	int cont;
	printf("\nNew command menu\n");
	// Create and print new commands until user chooses to exit
	do{
		int action;
		float duration;
		Command comm;

		// Read action and duration from user
		printf("\nEnter action (0=wait, 1=forward, 2=left, 3=right):\n");
		scanf("%d", &action);
		printf("Enter duration:\n");
		scanf("%f", &duration);

		// Create a new Command structure with these values
		comm = initializeNewCommand(action,duration);
		// Print the members of the structure
		printf("Command with action %d and duration %.2f\n", comm.robotAction, comm.robotActionDuration);

		// Ask if user wants to enter another command
		printf("Do another? (1/0)\n");
		scanf("%d", &cont);
	} while(cont);
}

void demoExecCommand()
{
	int more;
	// Create a new robot with only 5 history spaces
	Robot robot = newRobot(0,0,1,M_PI,5);

	printf("\nCommand execution menu\n");
	// Create and execute commands until user chooses to exit
	do{
		Command comm;

		// Read action and duration from user
		printf("\nEnter action (0=wait, 1=forward, 2=left, 3=right):\n");
		scanf("%d", &comm.robotAction);
		printf("Enter duration:\n");
		scanf("%f", &comm.robotActionDuration);

		// Execute the entered command
		executeCommand(&robot,comm);

		// Print the state of the robot after executing the command
		printf("Current state of robot:\n");
		printf("x = %.2f, y = %.2f, heading = %.2f deg, t = %.2f\n", robot.currentState.x,
				robot.currentState.y, robot.currentState.heading*180/M_PI, robot.currentState.t);

		// Ask if user wants to execute another command
		printf("Do another? (1/0)\n");
		scanf("%d", &more);
	} while(more);

	// Print the state history after executing the commands
	printf("\nState history:\n");
	printStateHistory(&robot);

	// Print state history capacity,
	printf("\nState history capacity: %d\n", robot.historyCapacity);

	// Free the robot's state history
	free(robot.stateHistory);
}

void demoWriteHist()
{
	char binFileName[20], textFileName[20];

	// Create a new robot with 10 history spaces
	Robot robot = newRobot(0,0,1,M_PI,10);

	// Execute some commands
	executeCommand(&robot,initializeNewCommand(ACTION_FORWARD,1));
	executeCommand(&robot,initializeNewCommand(ACTION_TURN_LEFT,0.5));
	executeCommand(&robot,initializeNewCommand(ACTION_FORWARD,0.5));
	executeCommand(&robot,initializeNewCommand(ACTION_TURN_RIGHT,1));
	executeCommand(&robot,initializeNewCommand(ACTION_FORWARD,2));

	// Read the name of the binary file and write to it
	printf("\nEnter binary filename:\n");
	scanf("%s", binFileName);
	writeStateHistoryBinary(binFileName,&robot);

	// Read the name of the text file and write to it
	printf("Enter text filename:\n");
	scanf("%s", textFileName);
	writeStateHistoryText(textFileName,&robot);

	// Call functions with print the contents of each file
	printf("\n");
	readBinary(binFileName);
	printf("\n");
	readText(textFileName);
}

void readBinary(char *filename)
{

	FILE *fPtr;
	int i, numBytes, numRecords;
	RobotState *stateArr;

	// Try to open the file
	fPtr = fopen(filename,"rb");

	// If file was opened successfully
	if (fPtr){
		printf("Contents of binary file \"%s\":\n", filename);

		/* Determine the size of the file in bytes by seeking to the end,
		 * getting the position, then rewinding to the start again */
		fseek(fPtr, 0, SEEK_END);
		numBytes = ftell(fPtr);
		fseek(fPtr, 0, SEEK_SET);

		// Get the number of records in the file
		numRecords = numBytes/sizeof(RobotState);

		// Print the size in bytes and records
		printf("size = %d bytes = %d records\n", numBytes, numRecords);

		// Allocate enough memory to store the contents of the file
		stateArr = malloc(numBytes);

		// Read the records from the file into the memory block
		fread(stateArr,sizeof(RobotState),numRecords,fPtr);

		// Print the column headings
		printf("%6s  %6s  %7s  %6s\n", "X","Y","Heading","Time");

		// For each state in the memory block
		for (i = 0 ; i < numRecords ; i++){
			RobotState s = stateArr[i]; // Temporary variable
			printf("%6.2f, %6.2f, %7.2f, %6.2f\n", s.x, s.y, s.heading*180/M_PI, s.t);
		}

		free(stateArr); // Free the memory block
		fclose(fPtr);   // Close the file
	}
	else{ // If file could not be opened
		printf("File \"%s\" could not be opened\n", filename);
	}
}

void readText(char *filename)
{
	FILE *fPtr;
	// Character strings to store the four fields in each line
	char s1[10],s2[10],s3[10],s4[10];

	fPtr = fopen(filename,"r");

	// If file opened successfully
	if (fPtr != NULL){
		printf("Contents of text file \"%s\":\n", filename);

		// While the end of the file has not been reached
		while (!feof(fPtr)){
			// Read a line and print it
			fscanf(fPtr,"%s\t%s\t%s\t%s\n",s1,s2,s3,s4);
			printf("%s\t%s\t%s\t%s\n",s1,s2,s3,s4);
		}
	}
	else{ // If file could not be opened
		printf("File \"%s\" could not be opened\n", filename);
	}

	// Close the file
	fclose(fPtr);
}

void demoReadWaypoints()
{
	char filename[20];
	float *xArr, *yArr;
	int i,numWP;

	// Get the name of a file
	printf("\nEnter name of waypoint file:\n");
	scanf("%s", filename);

	// Read waypoints from it into xArr and yArr
	readWayPoints(filename,&xArr,&yArr,&numWP);

	// Print the waypoints that were read from the file
	printf("Waypoints from \"%s\":\n", filename);
	for(i = 0 ; i < numWP ; i++){
		printf("X = %5.2f, Y = %5.2f\n", xArr[i], yArr[i]);
	}

	// Free the arrays
	free(xArr);
	free(yArr);
}

void demoMoves()
{
	float dist, angle, x, y;
	Robot robot = newRobot(0,0,1,M_PI/2,20);

	// Read an angle in degrees from the user
	printf("\nEnter angle to turn left: (degrees)\n");
	scanf("%f", &angle);
	angle *= M_PI/180; // Convert the angle to radians
	turnByCertainAngle(&robot,angle); // Turn left (positive) by that angle

	// Read a distance, and move that distance forward
	printf("Enter distance to move forward:\n");
	scanf("%f", &dist);
	moveCertainDistance(&robot,dist);

	// Read and angle in degrees from the used
	printf("Enter angle to turn right: (degrees)\n");
	scanf("%f", &angle);
	angle *= M_PI/180; // Convert the angle to radians
	turnByCertainAngle(&robot,-angle); // Turn right (negative) by that angle

	// Read a waypoint from the user and move there
	printf("Enter X coordinate of waypoint:\n");
	scanf("%f", &x);
	printf("Enter Y coordinate of waypoint:\n");
	scanf("%f", &y);
	moveRobotTo(&robot,x,y);

	// Print and free the state history
	printStateHistory(&robot);
	free(robot.stateHistory);
}

void demoFollowWaypoints()
{
	// Hard-coded waypoints
	float xArr[5] = {0, 1, 2, 3, 4};
	float yArr[5] = {0, 1, 2, 1, 0};

	// Create a robot
	Robot robot = newRobot(0,0,1,M_PI*2,20);

	// Follow the waypoints
	followWaypointSequence(&robot,xArr,yArr,5);

	// Print and free the state history
	printf("\nState history after following waypoints:\n");
	printStateHistory(&robot);
	free(robot.stateHistory);
}

void demoQueue()
{
	int choice, x, y;

	// Create an empty queue
	Queue queue = {NULL,NULL};

	// Keep performing queue operations until user exits
	do{
		// Display menu
		printf("\nQueue menu\n");
		printf("1. Add to queue\n");
		printf("2. Remove from queue\n");
		printf("3. Print queue\n");
		printf("0. Exit\n");
		printf("Enter choice:\n");
		scanf("%d", &choice);

		switch(choice)
		{
		case 1: // Add values to queue
			printf("Enter X to add to queue:\n");
			scanf("%d", &x);
			printf("Enter Y to add to queue:\n");
			scanf("%d", &y);
			addToQueue(&queue,x,y);
			printf("(%d,%d) added to queue\n", x, y);
			break;

		case 2: // Remove from queue
			removeFromQueue(&queue,&x,&y);
			printf("Values removed from queue: (%d,%d)\n", x, y);
			break;

		case 3: // Print the queue
			printQueue(&queue);
			break;
		}
	}
	while(choice != 0);

	// Free any remaining nodes in the queue
	freeQueue(&queue);
}

void demoEnvironment()
{
	char filename[20];
	Environment env;
	int x0,y0,xG,yG;
	Action *actions = defaultActionArray(); // Create action array
	float *xArr, *yArr;
	int i,numWP;
	Robot robot;

	// Read name of map file
	printf("\nEnter environment filename:\n");
	scanf("%s", filename);
	// Read starting and goal coordinates
	printf("Enter starting X:\n");
	scanf("%d", &x0);
	printf("Enter starting Y:\n");
	scanf("%d", &y0);
	printf("Enter goal X:\n");
	scanf("%d", &xG);
	printf("Enter goal Y:\n");
	scanf("%d", &yG);

	// Create new environment with these values
	env = newEnvironment(filename,x0,y0,xG,yG);

	// Create new robot with 50 history spaces
	robot = newRobot(x0,y0,1,M_PI,50);

	// Print occupancy map
	printOccMap(&env);
	printf("\nBefore running Dijkstra - ");

	// Print initialised action map
	printActionMap(&env);

	// Generate action map using Dijkstra
	dijkstra(&env,actions,8);

	// Print generated action map
	printf("\nAfter running Dijkstra - ");
	printActionMap(&env);

	// Search action map for path from start to goal
	// Store waypoints of solution path in xArr and yArr
	searchActionMap(&env,&xArr,&yArr,&numWP);

	// Print the waypoints of the solution path
	printf("\nWaypoints from (%d,%d) to (%d,%d):\n", x0, y0, xG, yG);
	for(i = 0 ; i < numWP ; i++){
		printf("X = %5.2f, Y = %5.2f\n", xArr[i], yArr[i]);
	}

	// Follow the waypoints with the robot
	followWaypointSequence(&robot,xArr,yArr,numWP);
	printf("Waypoints followed\n");
	writeStateHistoryText("plannedPath.txt",&robot);
	writeStateHistoryBinary("plannedPath.bin",&robot);
	printf("History written to text and binary files\n");

	// Free all the allocated memory
	free(xArr);
	free(yArr);
	free(actions);
	free(robot.stateHistory);
}
