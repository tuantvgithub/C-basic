#include "ll.h"

/* =========== llInit =========== */

LList* llInit() {
	LList* ll = (LList*)malloc(sizeof(LList));

	if(!ll) printf("llInit that bai.\n");
	else ll->root = NULL;
	return ll;
}

/* ========== llInsert ========== */

void llInsertHead(LL_DATA data, LList* ll) {
	Element* temp = (Element*)malloc(sizeof(Element));

	if(!temp || !ll) {
		if(temp) free(temp);
	} else {
		temp->data = data;
		temp->next = ll->root;
		ll->root = temp;
	}
	return;
}

void llInsertTail(LL_DATA data, LList* ll) {
	Element* newElem = (Element*)malloc(sizeof(Element));
	Element* temp = NULL;

	if(!newElem || !ll) {
		if(newElem) free(newElem);
	} else if(!ll->root){
		ll->root = newElem;
	} else {
		for(temp = ll->root; temp->next; temp = temp->next);
		temp->next = newElem;
	}
	newElem->next = NULL;
	newElem->data = data;
	return;	
}

void llInsertAfter(LL_DATA data, Element* e) {
	Element* newElem = (Element*)malloc(sizeof(Element));

	if(!newElem || !e) {
		if(newElem) free(newElem);
	} else {
		newElem->next = e->next;
		newElem->data = data;
		e->next = newElem;
	}
	return;
}

/* ========== llDelete ========== */

void llDeleteHead(LList* ll) {
	Element* temp = NULL;
	
	if(!ll || !ll->root) {
		return;
	} else {
		temp = ll->root;
		ll->root = temp->next;
		free(temp);
	}
	return;
}

void llDeleteTail(LList* ll) {
	Element *tail = NULL, *temp = NULL;
	
	if(!ll || !ll->root) {
		return;
	} else if(!ll->root->next) {
		tail = ll->root;
		free(tail);
		ll->root = NULL;		
	} else {
		for(temp = ll->root; temp->next->next; temp = temp->next);
		tail = temp->next;
		free(tail);	
		temp->next = NULL;
	}	
	return;
}

void llDeleteAfter(Element* e) {
	Element* temp = NULL;
	
	if(!e || !e->next) {
		printf("llDeleteAfter co van de.\n");
	} else {
		temp = e->next;
		e->next = temp->next;
		free(temp);
	}
	return;
}

void llDeleteAll(LList* ll) {
	if(ll) {
		while(ll->root) {
			llDeleteHead(ll);
		}
	}
	return;
}

/* ========== llSuportFunction ========== */

void llPrint(LList* ll) {
	Element* temp = NULL;
	
	if(!ll) return;
	if(!ll->root) {
		printf("Linked list is empty.\n");		
	} else {
		for(temp = ll->root; temp; temp = temp->next) {
			printf("%d  ", temp->data);
		}
		printf("\n");
	}
	return;
}

void printElem(Element* e) {
	printf("%d  ", e->data);
	return;
}

void llForEach(LList* ll, void (*func)(Element* e)) {
	Element* temp = NULL;
		
	if(!ll) {
		printf("llForEach that bai.\n");
	} else {
		for(temp = ll->root; temp; temp = temp->next) {
			func(temp);
		}
		printf("\n");
	}
	return;
}

int llLength(LList* ll) {
	Element* temp = NULL;
	int count = 0;

	if(!ll) {
		printf("llLength that bai.\n");
		return -1;
	} else {
		for(temp = ll->root; temp; temp = temp->next, count++);
		return count;
	}
}

Element* llSeek(int pos, LList* ll) {
	Element* temp = NULL;

	if(!ll || !ll->root) {
		printf("llSeek that bai.\n");
	} else {
		temp = ll->root;
		for(int i = 1; i < pos; i++, temp = temp->next); 
	}
	return temp;
}

/* =========== Sorting ========== */

void swapData(Element* a, Element* b) {
	LL_DATA t = a->data;
	
	a->data = b->data;
	b->data = t;
	return;
}

void llSort(LList* ll) {
	Element *i = NULL, *j = NULL, *iMin = NULL;

	if(!ll || !ll->root) return;
	else {
		for(i = ll->root; i->next->next; i = i->next) {
			iMin = i;
			for(j = i->next; j->next; j = j->next) {
				if(j->data < iMin->data)
					iMin = j;
			}
			swapData(i, iMin);
		}
		return;
	} 
}






















