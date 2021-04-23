#include "queue.h"

void main() {
	QUEUE* q = Q_init();
	
	if(q) {
		enQueue(0, q);
		enQueue(1, q);
		enQueue(2, q);
		enQueue(3, q);
		enQueue(4, q);
		enQueue(5, q);
		enQueue(6, q);
		enQueue(7, q);
		enQueue(8, q);
		enQueue(9, q);
		Q_print(q);
		printf("\nLength : %d\n", queueLength(q));
		printf("Head : %d\n", q->elem[q->head]);
		printf("Tail : %d\n", q->elem[q->tail]);
		
		free(q);
	}
	return;
}
