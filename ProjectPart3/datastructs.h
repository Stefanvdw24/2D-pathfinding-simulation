/* Filename: datastructs.h
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


#ifndef DATASTRUCTS_H_
#define DATASTRUCTS_H_


//Structures

typedef struct QueueNode_t{
struct QueueNode_t *next;
int x, y;
} QueueNode;

typedef struct Queue_t{
QueueNode *head, *tail;
} Queue;


//Function Prototypes

void printQueue(Queue *q); //Print the queue on the screen
void addToQueue(Queue *queuePtr, int x, int y); //Add a new node to the queue
int removeFromQueue(Queue *queuePtr, int *x, int *y); //remove a node from the head of the queue
void freeQueue(Queue *queuePtr);//a function which frees all the memory allocated for the nodes in a queue.


#endif /* DATASTRUCTS_H_ */
