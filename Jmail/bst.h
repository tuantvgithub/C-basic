#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constant.h"

typedef struct info {
	char name[SIZE_NAME];
	char sdt[SIZE_SDT];
	char yearOfBirth[SIZE_YEAR_OF_BIRTH];
} info;

typedef struct account {
	char user[SIZE_USER], pass[SIZE_PASS]; // key of binary search tree if user
	FILE *inbox, *outbox;
	info info;
} BST_DATA;

typedef struct BST_NODE {
	BST_DATA data;
	struct BST_NODE *left, *right;
} BST_NODE;

int dataCompare(BST_DATA a, BST_DATA b); // 1 : a > b | -1 : a < b || key is user
int lengthBST(BST_NODE* root);

void printData(BST_DATA data);
void inOrder(BST_NODE* root);

BST_NODE* createNode(BST_DATA data);
void insertNode(BST_DATA data, BST_NODE** root);

BST_NODE* searchNodeByUser(char* user, BST_NODE* root);
BST_NODE* searchNodeByData(BST_DATA data, BST_NODE* root);
BST_NODE* findMin(BST_NODE* root);
BST_NODE* findMax(BST_NODE* root);

void deleteNode(BST_DATA data, BST_NODE** root);

#endif //__BST_H__















