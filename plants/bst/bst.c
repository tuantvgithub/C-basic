#include "bst.h"

BST_Node* createNode(BST_Data data) {
	BST_Node* temp = (BST_Node*)malloc(sizeof(BST_Node));
	
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

void insertNode(BST_Data data, BST_Node** root) {
	if(!(*root)) {
		*root = createNode(data);
	} else if(data > (*root)->data){
		insertNode(data, &(*root)->right);
	} else if(data < (*root)->data){
		insertNode(data, &(*root)->left);
	} else return;
}

BST_Node* findMin(BST_Node* root) {
	if(!root) return NULL;
	else if(!root->left) return root;
	else return findMin(root->left);
}

BST_Node* findMax(BST_Node* root) {
	if(!root) return NULL;
	else if(!root->right) return root;
	else return findMax(root->right);
}

BST_Node* searchNode(BST_Data data, BST_Node* root) {
	if(!root) return NULL;
	else if(data > root->data) return searchNode(data, root->right);
	else if(data < root->data) return searchNode(data, root->left);
	else return root;
}

void deleteNode(BST_Data data, BST_Node** root) {
	if(!(*root)) return;
	else if(data > (*root)->data) deleteNode(data, &(*root)->right);
	else if(data < (*root)->data) deleteNode(data, &(*root)->left);
	else {
		if(!(*root)->left && !(*root)->right) {
			free(*root);
			*root = NULL;
		} else if((*root)->left) {
			(*root)->data = findMax((*root)->left)->data;
			deleteNode((*root)->data, &(*root)->left);
		} else {
			(*root)->data = findMin((*root)->right)->data;
			deleteNode((*root)->data, &(*root)->right);		
		}
	}
	return;
}

/* ========== Count Node ========== */

int BST_height(BST_Node* root) {
	int lHeight, rHeight;
	
	if(!root)
		return 0;
	else {
		lHeight = BST_height(root->left);
		rHeight = BST_height(root->right);

		return lHeight > rHeight ? lHeight + 1 : rHeight + 1;
	}
}

int BST_countNode(BST_Node* root) {
	int left, right;

	if(!root)
		return 0;
	else {
		left = BST_countNode(root->left);
		right = BST_countNode(root->right);

		return left + right + 1;
	}
}

int BST_countLeaf(BST_Node* root) {
	int l, r;

	if(!root)
		return 0;
	else if(!root->left && !root->right)
		return 1;
	else {
		l = BST_countLeaf(root->left);
		r = BST_countLeaf(root->right);

		return l + r;
	}
}

/* ========== Print list ========== */

void inOrder(BST_Node* root) {
	if(!root) return;

	inOrder(root->left);
	printf("%d  ", root->data);
	inOrder(root->right);
}

void preoOrder(BST_Node* root) {
	if(!root) return;

	printf("%d  ", root->data);
	preoOrder(root->left);
	preoOrder(root->right);
}

void postOrder(BST_Node* root) {
	if(!root) return;

	postOrder(root->left);
	postOrder(root->right);
	printf("%d  ", root->data);
}

void printLevel(int level, BST_Node* root) {
	if(!root)
		return;
	if(level == 1) {
		printf("%d  ", root->data);
	} else if(level > 1) {
		printLevel(level - 1, root->left);
		printLevel(level - 1, root->right);
	}
	return;
}

void levelOrder(BST_Node* root) {
	int n;

	if(!root)
		return;
	n = BST_height(root);
	for(int i = 1; i <= n; i++)
		printLevel(i, root);
	return;
}





