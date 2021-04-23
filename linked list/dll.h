#ifndef __DLL_H__
#define __DLL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* DLL_DATA;

typedef struct Element Element;
struct Element {
	DLL_DATA data;
	Element *next, *prev;
};

typedef struct DLList {
	Element *head, *tail;
} DLList;

DLList* dllInit();

void dllInsertHead(DLL_DATA data, DLList* dll);
void dllInsertTail(DLL_DATA data, DLList* dll);
void dllInsertAfter(DLL_DATA data, Element* e, DLList* dll);

void dllDeleteHead(DLList* dll);
void dllDeleteTail(DLList* dll);
void dllDeleteAfter(Element* e, DLList* dll);
void dllDeleteBefore(Element* e, DLList* dll);
void dllDeleteAll(DLList* dll);

int dllLength(DLList* dll); // same ll
void dllPrint(DLList* dll); // same ll
Element* dllSeek(int pos, DLList* dll); // same ll

//void printElem(Element* e); // same ll
//void dllForEach(DLList* dll, void (*func)(Element* e)); // random

void swapData(Element* a, Element* b); // same ll
void dllSort(DLList* dll); // using bubble sort

#endif // __DLL_H__



