#include "bst.h"

void printData(BST_DATA data) { // only user and pass of client
	printf("%-30s %-20s\n", data.user, data.pass);
	return;
}

void inOrder(BST_NODE* root) {
	if(!root) return;
	inOrder(root->left);
	printData(root->data);
	inOrder(root->right);
	return;
}

int dataCompare(BST_DATA a, BST_DATA b) { // 1 : a > b | -1 : a < b || key is user
	if(strcmp(a.user, b.user) > 0) return 1;
	else if(strcmp(a.user, b.user) < 0) return -1;
	else return 0;
}

int lengthBST(BST_NODE* root) {
	int lRight = 0, lLeft = 0;	
	
	if(!root)
		return 0;
	else if(!root->left && !root->right)
		return 1;
	else {
		lLeft = lengthBST(root->left);
		lRight = lengthBST(root->right);

		return lLeft + lRight + 1;
	}
}

BST_NODE* createNode(BST_DATA data) {
	BST_NODE* temp = (BST_NODE*)malloc(sizeof(BST_NODE));

	if(temp) {
		temp->data = data;
		temp->left = temp->right = NULL;
	}

	return temp;
}

void insertNode(BST_DATA data, BST_NODE** root) {
	if(!(*root)) (*root) = createNode(data);
	else if(dataCompare(data, (*root)->data) > 0) insertNode(data, &(*root)->right);
	else if(dataCompare(data, (*root)->data) < 0) insertNode(data, &(*root)->left);
	else return;
}

BST_NODE* searchNodeByUser(char* user, BST_NODE* root) {
	if(!root)
		return NULL;
	else if(strcmp(user, root->data.user) > 0)
		return searchNodeByUser(user, root->right);
	else if(strcmp(user, root->data.user) < 0)
		return searchNodeByUser(user, root->left);
	else 
		return root;
}

BST_NODE* searchNodeByData(BST_DATA data, BST_NODE* root) {
	if(!root)
		return NULL;
	else if(dataCompare(data, root->data) > 0)
		return searchNodeByData(data, root->right);
	else if(dataCompare(data, root->data) < 0)
		return searchNodeByData(data, root->left);
	else
		return root;
} 

BST_NODE* findMin(BST_NODE* root) {
	if(!root) return NULL;
	else if(!root->left) return root;
	else return findMin(root->left);
}

BST_NODE* findMax(BST_NODE* root) {
	if(!root) return NULL;
	else if(!root->right) return root;
	else return findMax(root->right);
}

void deleteNode(BST_DATA data, BST_NODE** root) {	
	BST_NODE* temp = NULL;
	
	if(!(*root))
		return;
	else if(dataCompare(data, (*root)->data) > 0)
		deleteNode(data, &(*root)->right);
	else if(dataCompare(data, (*root)->data) < 0)
		deleteNode(data, &(*root)->left);
	else {
		if(!(*root)->left && !(*root)->right) {
			free((*root));
			*root = NULL;
		}
		else if(!(*root)->left) {
			temp = findMin((*root)->right);
			(*root)->data = temp->data;
			deleteNode(temp->data, &(*root)->right);
		}
		else {
			temp = findMax((*root)->left);
			(*root)->data = temp->data;
			deleteNode(temp->data, &(*root)->left);
		}
		return;
	}		
}


































