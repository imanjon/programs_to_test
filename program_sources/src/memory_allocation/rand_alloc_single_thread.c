/*
 * threads.c
 *
 *  Created on: Dec 1, 2016
 *      Author: lks
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TRUE  1
#define FALSE	0

/* a link in the queue, holds the info and point to the next Node*/
typedef struct {
    int info;
} DATA;

typedef struct Node_t {
    DATA data;
    struct Node_t *prev;
} NODE;

/* the HEAD of the Queue, hold the amount of node's that are in the queue*/
typedef struct Queue {
    NODE *head;
    NODE *tail;
    int size;
    int limit;
} Queue;

Queue *ConstructQueue(int limit);
void DestructQueue(Queue *queue);
int Enqueue(Queue *pQueue, NODE *item);
NODE *Dequeue(Queue *pQueue);
int isEmpty(Queue* pQueue);

Queue *ConstructQueue(int limit) {
    Queue *queue = (Queue*) malloc(sizeof (Queue));
    printf("Memory was allocated for the queue\n");
    if (queue == NULL) {
        return NULL;
    }
    if (limit <= 0) {
        limit = 65535;
    }
    queue->limit = limit;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

void DestructQueue(Queue *queue) {
    NODE *pN;
    while (!isEmpty(queue)) {
        pN = Dequeue(queue);
        free(pN);
        printf("Memory was freed for the node\n");
    }
    free(queue);
    printf("Memory was freed for the queue\n");
}

int Enqueue(Queue *pQueue, NODE *item) {
    // Bad parameter
    if ((pQueue == NULL) || (item == NULL)) {
        return FALSE;
    }
    // if(pQueue->limit != 0)
    if (pQueue->size >= pQueue->limit) {
        return FALSE;
    }
    // the queue is empty
    item->prev = NULL;
    if (pQueue->size == 0) {
        pQueue->head = item;
        pQueue->tail = item;

    } else {
        // adding item to the end of the queue
        pQueue->tail->prev = item;
        pQueue->tail = item;
    }
    pQueue->size++;

    printf("Queued: %d\n", item->data.info);

    return TRUE;
}

NODE * Dequeue(Queue *pQueue) {
    // the queue is empty or bad param
    NODE *item;
    if (isEmpty(pQueue))
        return NULL;
    item = pQueue->head;
    pQueue->head = (pQueue->head)->prev;
    pQueue->size--;
    printf("Dequeued: %d\n", item->data.info);
    return item;
}

int isEmpty(Queue* pQueue) {
    if (pQueue == NULL) {
        return FALSE;
    }
    if (pQueue->size == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int main() {
    int i;
    Queue *pQ = ConstructQueue(7);
    NODE *pN;

    // Seed top create random numbers
    srand(time(NULL));

    printf("Working with the queue\n");
    for (i = 0; i < 10; i++) {
    	int r = rand() % 2;    //returns a pseudo-random integer between 0 and RAND_MAX
    	if (r){
    		pN = (NODE*) malloc(sizeof (NODE));
			printf("Memory was allocated for the node\n");
			pN->data.info = 100 + i;
			if (!Enqueue(pQ, pN)){
				free(pN);
				printf("Memory was freed for the node\n");
			}
    	}
    	else{
			pN = Dequeue(pQ);
			if (pN){
				free(pN);
				printf("Memory was freed for the node\n");
			}
    	}
	}
    printf("Forcing the Dequeue\n");

    /*
    for (i = 0; i < 10; i++) {
        pN = (NODE*) malloc(sizeof (NODE));
        printf("Memory was allocated for the node\n");
		pN->data.info = 100 + i;
        if (!Enqueue(pQ, pN)){
        	free(pN);
        	printf("Memory was freed for the node\n");
        }
    }

    while (!isEmpty(pQ)) {
        pN = Dequeue(pQ);
        free(pN);
        printf("Memory was freed for the node\n");
    }
    */

    DestructQueue(pQ);
    return (EXIT_SUCCESS);
}
