#include "queue.h"

QUEUE* Q_init() {
	QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));

	q->head = q->tail = -1;
	return q;
}

int queueIsFull(QUEUE* q) {
	return (q->tail + 1) % QUEUE_MAX_SIZE == q->head ? 1 : 0;
}

int queueIsEmpty(QUEUE* q) {
	return q->tail == -1 && q->head == -1 ? 1 : 0;
}

int queueLength(QUEUE* q) {
	if(queueIsEmpty(q)) return 0;
	else if(q->tail >= q->head) return q->tail - q->head + 1;
	else return QUEUE_MAX_SIZE - q->head + q->tail + 1;
}

void enQueue(QUEUE_DATA data, QUEUE* q) {
	if(queueIsFull(q)) return;
	else {
		q->tail = (q->tail + 1) % QUEUE_MAX_SIZE;
		q->elem[q->tail] = data;
		if(q->head == -1) q->head = q->tail;
	}	
}

QUEUE_DATA deQueue(QUEUE* q) {
	int val;

	if(queueIsEmpty(q)) return -1;

	val = q->elem[q->head];
	if(q->head == q->tail){
		q->head = q->tail = -1;
	}
	else {
		q->head = (q->head + 1) % QUEUE_MAX_SIZE;
	}
	return val;
}

void Q_print(QUEUE* q) {
	int n = queueLength(q);

	if(queueIsEmpty(q)) printf("Queue is empty\n");
	else {
		for(int i = 0; i < n; i++) {
			printf("%d  ", q->elem[(q->head + i) % QUEUE_MAX_SIZE]);
		}
		printf("\n");
	}
	return;
}





