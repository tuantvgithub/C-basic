#include "dll.h"

/* =========== dll_init ========== */

DLList* dllInit() {
	DLList* dll = (DLList*)malloc(sizeof(DLList));

	if(dll) {
		dll->tail = dll->head = NULL;
		return dll;
	}
}

/* ========== dll_suport_function ========== */

int dllIsEmpty(DLList* dll) {
	if(!dll) return -1;
	else if(!dll->head && !dll->tail) return 1;
	else return 0;
}

int dllLength(DLList* dll) {
	Element* temp = NULL;
	int count = 0;

	if(!dll) {
		return -1;
	} else {
		for(temp = dll->head; temp; temp = temp->next, count++);
		return count;
	}
}

Element* dllSeek(int pos, DLList* dll) {
	Element* temp = NULL;

	if(!dll || dllIsEmpty(dll)) {
		printf("llSeek that bai.\n");
	} else {
		temp = dll->head;
		for(int i = 1; i < pos; i++, temp = temp->next); 
	}
	return temp;
}

void dllPrint(DLList* dll) {
	Element* temp = NULL;
	
	if(!dll) return;
	if(dllIsEmpty(dll)) {
		printf("Double linked list is empty.\n");		
	} else {
		for(temp = dll->head; temp; temp = temp->next) {
			printf("%s\n", temp->data);
		}
	}
	return;
}

/* =========== dll_insert ========== */

void dllInsertHead(DLL_DATA data, DLList* dll) {
	Element* temp = (Element*)malloc(sizeof(Element));

	if(!dll || !temp) {
		if(temp) free(temp);
	} else {
		int len = strlen(data);
		temp->data = (DLL_DATA)malloc(len + 1);
		if(!temp->data) return;
		strcpy(temp->data, data);

		temp->next = dll->head;
		temp->prev = NULL;
		
		if(dllIsEmpty(dll)) { // double linked list is empty
			dll->tail = temp;
		} else {
			dll->head->prev = temp;			
		}
		dll->head = temp;
	}
	return;
}

void dllInsertTail(DLL_DATA data, DLList* dll) {
	Element* temp = (Element*)malloc(sizeof(Element));

	if(!dll || !temp) {
		if(temp) free(temp);
	} else {
		int len = strlen(data);
		temp->data = (DLL_DATA)malloc(len + 1);
		if(!temp->data) return;
		strcpy(temp->data, data);

		temp->next = NULL;
		temp->prev = dll->tail;
		
		if(dllIsEmpty(dll)) { // double linked list is empty
			dll->head = temp;	
		} else {
			dll->tail->next = temp;
		}
		dll->tail = temp;
	}
}

void dllInsertAfter(DLL_DATA data, Element* e, DLList* dll) {
	Element* temp = (Element*)malloc(sizeof(Element));

	if(!e || !temp) {
		if(temp) free(temp);
	} else {
		int len = strlen(data);
		temp->data = (DLL_DATA)malloc(len + 1);
		if(!temp->data) return;
		strcpy(temp->data, data);

		temp->next = e->next;
		temp->prev = e;
		if(e != dll->tail) {
			e->next->prev = temp;	
		} else {
			dll->tail = temp;
		}
		e->next = temp;	
	}
	return;
}

/* ========== dll_delete ========== */

void deleteData(Element* e) {
	if(e) {
		free(e->data);
	}
}

void dllDeleteHead(DLList* dll) {
	Element* temp = NULL;

	if(!dll) return;

	temp = dll->head;
	if(temp) {
		if(temp == dll->tail) {
			dll->head = dll->tail = NULL;
		} else {
			dll->head = temp->next;
			dll->head->prev = NULL;
		}

		deleteData(temp);
		free(temp);
		return;
	}
}

void dllDeleteTail(DLList* dll) {
	Element* temp = NULL;
	
	if(!dll) return;
	
	temp = dll->tail;
	if(temp) { // temp == null --> return
		if(temp == dll->head) { // the double linked list has 1 element
			dll->head = dll->tail = NULL;
		} else {
			dll->tail = temp->prev;
			dll->tail->next = NULL;
		}
		
		deleteData(temp);
		free(temp);
		return;
	}
}

void dllDeleteAfter(Element* e, DLList* dll) {
	Element* temp = NULL;

	if(!e || !e->next || !dll || dllIsEmpty(dll)) return;
	
	temp = e->next;

	if(temp == dll->tail) {
		dllDeleteTail(dll);
	} else {
		if(temp->next) {
			temp->next->prev = e;
		}
		
		e->next = temp->next;
		deleteData(temp);
		free(temp);
	}	
	return;	
}

void dllDeleteBefore(Element* e, DLList* dll) {
	Element* temp = NULL;

	if(!e || !e->prev || !dll || dllIsEmpty(dll)) return;

	temp = e->prev;
	
	if(temp == dll->head) {
		dllDeleteHead(dll);
	} else {
		if(temp->prev) {
			temp->prev->next = e;
		}

		e->prev = temp->prev;
		deleteData(temp);
		free(temp);
	}
	return;
}

void dllDeleteAll(DLList* dll) {
	while(!dllIsEmpty(dll)) {
		dllDeleteHead(dll);
	}	
	return;
}

/* =========== Soring using bubble sort ========== */

void swapData(Element* a, Element* b) {
	int sz = strlen(a->data);
	DLL_DATA temp = (DLL_DATA)malloc(sizeof(char)*sz);
	
	strcpy(temp, a->data);
	strcpy(a->data, b->data);
	strcpy(b->data, temp);
	return;
}

void dllSort(DLList* dll) {
	Element *i, *j;
	int sorted = 1;

	if(!dll || dllIsEmpty(dll)) return;
	else {
		for(i = dll->tail; i->prev != NULL; i = i->prev) {
			for(j = dll->head; j != i; j = j->next) {
				if(strcmp(j->data, j->next->data) > 0) {
					swapData(j, j->next);
					sorted = 0;
				}
			}
			if(sorted == 1) return;
		}	
	}
}






