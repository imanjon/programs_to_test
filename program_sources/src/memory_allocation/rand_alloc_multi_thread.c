/*
 * threads.c
 *
 *  Created on: Dec 1, 2016
 *      Author: lks
 *
 *       Brief: Creates a queue and several threads to share it.
 *              They enqueue data and free it randomly.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define FALSE				0
#define TRUE				1

#define THREADS_TO_LAUNCH	10
#define NUM_THREAD_OPS		10
#define QUEUE_LIMIT			70

/* a link in the queue, holds the info and point to the next Node*/
typedef struct {
    int info;
    char* buffer;
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
    int count;
    int active;
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
        queue->size = 0;
    }
    queue->limit = limit;
    queue->size = 0;
    queue->count = 0;
    queue->head = NULL;
    queue->tail = NULL;
    queue->active = 0;

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
    }
    else{
        return FALSE;
    }
}

// = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx;

void *Thread1(void *x) {
	int ret;
	int RandNum;
	int i;
    NODE *pN;

    Queue *pQ = (Queue *)x;
    pQ->active++;
    pthread_mutex_unlock(&mtx);
    printf("Working with the queue\n");

    for (i = 0; i < NUM_THREAD_OPS; i++) {
    	RandNum = rand() % 2;
    	if (RandNum){
    		pN = (NODE*) malloc(sizeof (NODE));
			printf("Memory was allocated for the node\n");
			pthread_mutex_lock(&mtx);
			pN->data.info = 100 + pQ->count;
			pN->data.buffer = malloc(200 * ( (rand() % 10) + 1) );
			pQ->count += 1;
			ret = Enqueue(pQ, pN);
			pthread_mutex_unlock(&mtx);
			if (!ret){
				free(pN);
				printf("Memory was freed for the node\n");
			}
    	}
    	else{
    		pthread_mutex_lock(&mtx);
			pN = Dequeue(pQ);
			pthread_mutex_unlock(&mtx);
			if (pN){
				free(pN->data.buffer);
				free(pN);
				printf("Memory was freed for the node\n");
			}
    	}
    	sleep(1);
	}
    pthread_mutex_lock(&mtx);
    pQ->active--;
    pthread_mutex_unlock(&mtx);

    printf("Forcing the Dequeue\n");
	return NULL;
}

int main() {
    int i;
    Queue *pQ = ConstructQueue(QUEUE_LIMIT);
    pthread_t t[THREADS_TO_LAUNCH];

    // Seed top create random numbers
    srand(time(NULL));

    pthread_mutex_init(&mtx, NULL);
    for (i = 0; i < THREADS_TO_LAUNCH; i++){
    	pthread_mutex_lock(&mtx);
    	pthread_create(&t[i], NULL, Thread1, pQ);
    }

    printf("Waiting for all threads to finish\n");
    while(pQ->active > 0);

    DestructQueue(pQ);

    for (i = 0; i < THREADS_TO_LAUNCH; i++)
    	pthread_join(t[i], NULL);
    pthread_mutex_destroy(&mtx);

    return (EXIT_SUCCESS);
}
