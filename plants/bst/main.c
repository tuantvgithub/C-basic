#include "bst.h"

void main() {
	BST_Node* root = createNode(4);

	if(!root) return;
		
	insertNode(2, &root);
	insertNode(5, &root);
	insertNode(7, &root);
	insertNode(6, &root);
	insertNode(3, &root);
	
	levelOrder(root);
	printf("\n");

	printf("height : %d\ncount : %d\nleaf : %d\n", BST_height(root), BST_countNode(root), BST_countLeaf(root));
}
