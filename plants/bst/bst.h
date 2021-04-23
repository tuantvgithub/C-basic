#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int BST_Data;
typedef struct BST_Node {
	BST_Data data;
	struct BST_Node* left;
	struct BST_Node* right;
} BST_Node;

BST_Node* createNode(BST_Data data);
BST_Node* findMin(BST_Node* root);
BST_Node* findMax(BST_Node* root);
BST_Node* searchNode(BST_Data data, BST_Node* root);

void insertNode(BST_Data data, BST_Node** root);
void deleteNode(BST_Data data, BST_Node** root);

int BST_height(BST_Node* root);
int BST_countNode(BST_Node* root);
int BST_countLeaf(BST_Node* root);

void inOrder(BST_Node* root);
void preoOrder(BST_Node* root);
void postOrder(BST_Node* root);
void levelOrder(BST_Node* root);

#endif // __BST_H__
