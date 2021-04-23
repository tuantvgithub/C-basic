#ifndef __LL_H__
#define __LL_H__

#include <stdio.h>
#include <stdlib.h>

typedef int LL_DATA;

typedef struct Element Element;
struct Element {
	LL_DATA data;
	Element* next;
};

typedef struct LList {
	Element* root;
} LList;

LList* llInit();

void llInsertHead(LL_DATA data, LList* ll);
void llInsertTail(LL_DATA data, LList* ll);
void llInsertAfter(LL_DATA data, Element* e);

void llDeleteHead(LList* ll);
void llDeleteTail(LList* ll);
void llDeleteAfter(Element* e);
void llDeleteAll(LList* ll);

int llLength(LList* ll);
void llPrint(LList* ll);
Element* llSeek(int pos, LList* ll);

void printElem(Element* e);
void llForEach(LList* ll, void (*func)(Element* e));

void swapData(Element* a, Element* b);
void llSort(LList* ll); // using selection sort

#endif // __LL_H__




