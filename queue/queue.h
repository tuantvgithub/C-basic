#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX_SIZE 10

typedef int QUEUE_DATA;

typedef struct QUEUE {
	QUEUE_DATA elem[QUEUE_MAX_SIZE];
	int head;
	int tail;
} QUEUE;

QUEUE* Q_init();
void Q_print(QUEUE* q); // from head to tail
QUEUE_DATA deQueue(QUEUE* q);
void enQueue(QUEUE_DATA data, QUEUE* q);
int queueIsEmpty(QUEUE* q);
int queueIsFull(QUEUE* q);
int queueLength(QUEUE* q);

#endif
