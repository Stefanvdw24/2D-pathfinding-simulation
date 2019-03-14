/* Filename: datastructs.c
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
#include "datastructs.h"


//Functions

void printQueue(Queue *q) //Print the queue on the screen
{
	// Initialise a node pointer to the head of the queue
	QueueNode *node = q->head;
	printf("Printing the queue:\n");
	// As long as there are more nodes to print
	while (node != NULL){
		// Print the node
		printf(" x = %2d, y = %2d\n",node->x,node->y);
		// Move on the the next node
		node = node->next;
	}
	printf("Queue printed.\n");
} //end printQueue

void addToQueue(Queue *queuePtr, int x, int y) //Add a new node to the queue
{

		QueueNode *newNode;
		newNode = malloc(sizeof(QueueNode)); //allocate memory for a QueueNode and store address in newNode
		newNode->x = x; //set x of newNode = x
		newNode->y = y; //set y of newNode = y
		newNode->next = NULL; //set next pointer of newNode = NULL

		if (queuePtr->head == NULL) //if queue is empty
		{
			queuePtr->head = newNode; //set head pointer of queue = newNode
		}
		else
		{
			queuePtr->tail->next = newNode; //set next pointer of last node in queue to newNode
		}

		queuePtr->tail = newNode; //set tail pointer of queue = newNode

} //end addToQueue

int removeFromQueue(Queue *queuePtr, int *x, int *y) //remove a node from the head of the queue
{
		int success = 0; //initialise success = 0
		QueueNode *secondNodePtr;

		if (queuePtr != NULL)//if queue is not empty
		{
			success = 1; //set success = 1

			*x = queuePtr->head->x; //set x = x of head of queue
			*y = queuePtr->head->y; //set y = y of head of queue

			secondNodePtr = queuePtr->head->next; //initialise secondNodePtr = address of 2nd node in queue
			free(queuePtr->head);//free the head of the queue
			queuePtr->head = secondNodePtr; //set head of queue to secondNodePtr
		}

		return success; //return success

} //end removeFromQueue

void freeQueue(Queue *queuePtr) //frees all the memory allocated for the nodes in a queue.
{
	int x, y; //variables for use by removeFromQueue function

	//Make pointers to the variables:
	int* xPtr;
	int* yPtr;
	xPtr = &x;
	yPtr = &y;

	while (queuePtr != NULL) //while the queue is not empty
	{
		removeFromQueue(queuePtr, xPtr, yPtr); //remove the head node from the queue
	}

	free(xPtr); //free the variable pointers
	free(yPtr);
}
