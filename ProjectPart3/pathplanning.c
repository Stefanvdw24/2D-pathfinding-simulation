/* Filename: pathplanning.c
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

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include "pathplanning.h"
#include "datastructs.h"


//Functions

void printOccMap(Environment *envPtr)
{
	int yCur,xCur;

	printf("\nOccupancy map:\n");
	printf("\n");
	// Count the Y coordinate backwards
	for (yCur = envPtr->height-1 ; yCur >= 0 ; yCur--) {
		printf("%2d  ",yCur); // Print the y coordinate
		// Count the X coordinate forwards
		for (xCur = 0 ; xCur < envPtr->width ; xCur++){
			if (envPtr->occupancyMap[xCur][yCur])
				printf("X "); // Obstructed cell
			else if (yCur == envPtr->yStart && xCur == envPtr->xStart)
				printf("S "); // Starting position
			else if (yCur == envPtr->yGoal && xCur == envPtr->xGoal)
				printf("G "); // Goal position
			else
				printf("  "); // Passable cell
		}
		printf("\n");
	}

	printf("   ");
	for (xCur = 0 ; xCur < envPtr->width ; xCur++)
		printf("%2d", xCur%10); // Print X coordinates
	printf("\n");


}

void printActionMap(Environment *envPtr)
{
	int xCur,yCur;
	printf("Action map:\n");
	// Count the Y coordinate backwards
	for (yCur = envPtr->height-1 ; yCur >= 0 ; yCur--) {
		printf("%2d  ",yCur); // Print the y coordinate
		// Count the X coordinate forwards
				for (xCur = 0 ; xCur < envPtr->width ; xCur++){
			if (xCur == envPtr->xGoal && yCur == envPtr->yGoal)
				printf(" <>"); // Goal position
			else
				printf(" %2s", envPtr->actionMap[xCur][yCur].name); // Action name
		}
		printf("\n");
	}

	printf("   ");
	for (xCur = 0 ; xCur < envPtr->width ; xCur++)
		printf("%3d", xCur%10); // Print X coordinates
	printf("\n");
}

Action* defaultActionArray()
{
	int i;
	// Create an array to store the actions
	Action* arr = malloc(8*sizeof(Action));

	// Initialise the dx and dy values of each action
	arr[0].dx = -1; arr[0].dy = -1; strcpy(arr[0].name,"SW");// SW
	arr[1].dx =  0; arr[1].dy = -1; strcpy(arr[1].name,"S ");// S
	arr[2].dx =  1; arr[2].dy = -1; strcpy(arr[2].name,"SE");// SE
	arr[3].dx =  1; arr[3].dy =  0; strcpy(arr[3].name,"E ");// E
	arr[4].dx =  1; arr[4].dy =  1; strcpy(arr[4].name,"NE");// NE
	arr[5].dx =  0; arr[5].dy =  1; strcpy(arr[5].name,"N ");// N
	arr[6].dx = -1; arr[6].dy =  1; strcpy(arr[6].name,"NW");// NW
	arr[7].dx = -1; arr[7].dy =  0; strcpy(arr[7].name,"W ");// W

	// Count the cost of each action
	for (i = 0 ; i < 8 ; i++)
		arr[i].length = sqrt(pow(arr[i].dx,2) + pow(arr[i].dy,2));

	return arr;
}

int dijkstra(Environment *envPtr,Action *actionArray,int numActions)
{
	Queue q = {NULL,NULL};
	int actionIndex;
	int success = 0;

	int x,y; // Counters
	float costMap[MAX_ENV_WIDTH][MAX_ENV_HEIGHT];

	// Initialise all entries in the cost map to -1
	for (x = 0 ; x < envPtr->width ; x++){
		for (y = 0 ; y < envPtr->height ; y++){
			costMap[x][y] = -1;
		}
	}
	// Initialise cost map entry for goal to 0
	costMap[envPtr->xGoal][envPtr->yGoal] = 0;

	// Add xg to Q
	addToQueue(&q,envPtr->xGoal,envPtr->yGoal);

	// While Q not empty
	while(q.head != NULL){
		// r,c = Get first element from Q
		int xCur,yCur;
		removeFromQueue(&q,&xCur,&yCur);
		// For each input
		for (actionIndex = 0 ; actionIndex < numActions ; actionIndex++) {
			// yNew,xNew = apply input in reverse
			int xNew = xCur-actionArray[actionIndex].dx;
			int yNew = yCur-actionArray[actionIndex].dy;

			// Check if new position falls withing environment bounds
			int exists = (yNew < envPtr->height) && (yNew >= 0) && (xNew < envPtr->width) && (xNew >= 0);
			// If (yNew,xNew) exists
			if (exists) {

				// Cost to go from (r1,c1) to goal
				float newCost = costMap[xCur][yCur]+actionArray[actionIndex].length;

				// Set flags
				int improves = (newCost < costMap[xNew][yNew]) || (costMap[xNew][yNew] < 0);
				int lessThanCurrentStartCost = (newCost < costMap[envPtr->xStart][envPtr->yStart])
																|| (costMap[envPtr->xStart][envPtr->yStart] < 0);
				int obstructed = envPtr->occupancyMap[xNew][yNew];

				// If unobstructed and new cost is less than both old cost and current cost from start
				if(!obstructed && improves && lessThanCurrentStartCost) {
					// Update the cost of (r1,c1)
					costMap[xNew][yNew] = newCost;
					envPtr->actionMap[xNew][yNew] = actionArray[actionIndex];
					// If (r1,c1) is not the start
					if ( (yNew != envPtr->yStart) || (xNew != envPtr->xStart) )
						addToQueue(&q,xNew,yNew); // Add (r1,c1) to the queue
					else
						success = 1; // Indicate that goal has been reached
				} // End if
			} // End if exists
		} // End for
	} // End while

	// Return 1 if start has been reached
	return success;
}

Environment newEnvironment(char mapFileName[], int x0, int y0, int xG, int yG) //Read the environment from a file and create the necessary maps
{
	FILE *filePtr; //initialize a file pointer
	int counter1, counter2; //loop counters
	char charHolder; //variable to hold scanned character;
	char commaChar;

	//Declare a new variable of type Environment. Initialise its starting and goal coordinates to the values passed as parameters:
	Environment environmentVar;
	environmentVar.xStart = x0;
	environmentVar.yStart = y0;
	environmentVar.xGoal = xG;
	environmentVar.yGoal = yG;

	filePtr = fopen(mapFileName, "r"); //open the file for reading and store the return value of fopen in a file pointer.

	fscanf(filePtr, "%d%c%d", &environmentVar.width, &commaChar, &environmentVar.height); //Read the width and height from the first line of the file


	for ( counter1=1 ; counter1<=environmentVar.height ; counter1++ ) //loop through each row
	{
		for ( counter2=0 ; counter2<=environmentVar.width ; counter2++ ) //loop through each column for that row
		{
			fscanf(filePtr, "%c", &charHolder ); //scan character from location
			if (charHolder == 'X') //if the character is X
			{
				environmentVar.occupancyMap[counter2-1][environmentVar.height - counter1] = 1; //set the occupancy value to 1
			}
			else //if the character is not X
			{
				environmentVar.occupancyMap[counter2-1][environmentVar.height - counter1] = 0; //set the occupancy value to 0
			}
		}
	} // end scan loop


	//Initialise all the entries of the action map to indicate that it is unknown which
	//action to take from the corresponding position:
	for ( counter1=1 ; counter1<=environmentVar.height ; counter1++ ) //loop through each row
	{
		for ( counter2=0 ; counter2<=environmentVar.width ; counter2++ ) //loop through each column for that row
		{
			environmentVar.actionMap[counter2-1][environmentVar.height - counter1].dx = 0; //set dx = 0
			environmentVar.actionMap[counter2-1][environmentVar.height - counter1].dy = 0; //set dy =0
			environmentVar.actionMap[counter2-1][environmentVar.height - counter1].length = 0; //set thelength = 0
			strcpy(environmentVar.actionMap[counter2-1][environmentVar.height - counter1].name, "xx"); //initialise the name of the action
		}
	}


	fclose(filePtr); //close the file pointer
	return environmentVar; //return the environment variable
}

void searchActionMap(Environment *envPtr,float** xArrPtr, float** yArrPtr, int* numWaypoints) //Search the action map
{

	Queue *theQueue;
	theQueue = NULL; //Create an empty queue to store the waypoints temporarily

	addToQueue(theQueue, envPtr->xStart, envPtr->yStart); //add the starting position to the queue.
	(*numWaypoints) = 1; //Initialise the number of waypoints to 1.
	int currentX = envPtr->xStart; //Declare two integers to store the X and Y values of the current
	int currentY = envPtr->yStart; //position, and initialise them to the starting position.

	while (currentX != envPtr->xStart && currentY != envPtr->yGoal)
	{
		//Read the action to be taken at the current position from the action map
		//Determine the X and Y coordinates of the new position reached after applying
		//that action from the current position
		//Add the new position to the queue, and increment the number of waypoints.
		numWaypoints++;
		//Update the current position to the new position
	}

	//Once the goal has been reached and the number of waypoints has been determined,
	//allocate memory for the X and Y arrays. Each array should have
	//enough space to store a coordinate for each waypoint as a float.

	free(theQueue);

}
