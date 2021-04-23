#include "AVL_Tree.h"

struct Node* create_int_node(void* data, int data_size) {
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));	
	if(!new_node) return NULL;

	new_node->data = (int*)malloc(data_size);
	if(!new_node->data) return NULL;

	memcpy(new_node->data, data, data_size);
	new_node->balance_factor = 0;
	new_node->left = new_node->right = NULL;
	return new_node;
}

int int_compare(void* a, void* b) {
	if(*(int*)a == *(int*)b) return 0;
	else return *(int*)a > *(int*)b ? 1 : -1; 
}

void int_swap_data(struct Node* node_1, struct Node* node_2) {
	int temp = *(int*)node_1->data;
	*(int*)node_1->data = *(int*)node_2->data;
	*(int*)node_2->data = temp;
}

struct Node* create_str_node(void* data, int data_size) {
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	if(!new_node) return NULL;
	
	new_node->data = (char*)malloc(data_size);
	if(!new_node->data) return NULL;
	
	strcpy(new_node->data, (char*)data);
	new_node->balance_factor = 0;
	new_node->left = new_node->right = NULL;
	return new_node;	
}

int str_compare(void* a, void* b) {
	return strcmp((char*)a, (char*)b);
}

void str_swap_data(struct Node* node_1, struct Node* node_2) {
	char* temp = (char*)malloc(sizeof(char));
	strcpy(temp, (char*)node_1->data);
	strcpy((char*)node_1->data, (char*)node_2->data);
	strcpy((char*)node_2->data, temp);
}

int max(int a, int b) {
	return a > b ? a : b;
}

int height_of(struct Node* root) {
	if(!root) return 0;
	int lh = height_of(root->left);
	int rh = height_of(root->right);
	return 1 + max(lh, rh);
}

struct Node* left_rotate(struct Node* root) {
	struct Node* temp = root->right;

	root->right = temp->left;
	temp->left = root;

	temp->balance_factor = height_of(temp->left) - height_of(temp->right);
	root->balance_factor = height_of(root->left) - height_of(root->right);
	return temp;
}

struct Node* right_rotate(struct Node* root) {
	struct Node* temp = root->left;

	root->left = temp->right;
	temp->right = root;	

	temp->balance_factor = height_of(temp->left) - height_of(temp->right);
	root->balance_factor = height_of(root->left) - height_of(root->right);	
	return temp;
}

struct Node* left_right_rotate(struct Node* root) {
	root->left = left_rotate(root->left);
	return right_rotate(root);
}

struct Node* right_left_rotate(struct Node* root) {
	root->right = right_rotate(root->right);
	return left_rotate(root);
}

struct Node* balancer(struct Node* root) {
	if(!root)
		return NULL;
	if(root->balance_factor > 1) { 			// left - ? case
		if(root->left->balance_factor == 1) 	// left - left case
			return right_rotate(root);
		else 					// left - right case
			return left_right_rotate(root);
	} else if(root->balance_factor < -1) { 		// right - ? case
		if(root->right->balance_factor == -1) 	// right - right case
			return left_rotate(root);
		else 					// right - left case
			return right_left_rotate(root);
	} else // balanced..
		return root;
}

struct Node* insert_node(void* data, int data_size, struct Node* root, 
				int (*compare_node) (void*, void*),
			struct Node* (*create_node) (void*, int)) {	
	if(!root) {
		return create_node(data, data_size);	
	} else if(compare_node(data, root->data) > 0) {
		root->right = insert_node(data, data_size, root->right,
						compare_node, create_node);
	} else if(compare_node(data, root->data) < 0) {	
		root->left = insert_node(data, data_size, root->left,
						compare_node, create_node);
	}
	
	root->balance_factor = height_of(root->left) - height_of(root->right);

	return balancer(root);
}

struct Node* search_node_max(struct Node* root) {
	if(!root)
		return NULL;
	else if(!root->right)
		return root;
	else
		return search_node_max(root->right);
}	

struct Node* search_node_min(struct Node* root) {
	if(!root)
		return NULL;
	else if(!root->left)
		return root;
	else
		return search_node_min(root->left);
}

struct Node* search_node(void* data, struct Node* root, 
		int (*compare_node) (void*, void*)) {
	if(!root)
		return NULL;	
	else if(compare_node(data, root->data) < 0)
		return search_node(data, root->left, compare_node);
	else if(compare_node(data, root->data) > 0)
		return search_node(data, root->right, compare_node);
	else
		return root;
}

void release_node(struct Node* node) {
	if(!node) return;
	free(node->data);
	free(node);
}

struct Node* delete_node(void* data, struct Node* root,
		int (*compare_node) (void*, void*), 
			void (*swap_data) (struct Node*, struct Node*)) {
	if(!root) return NULL;
	else if(compare_node(data, root->data) > 0)
		root->right = delete_node(data, root->right, 
						compare_node, swap_data);
	else if(compare_node(data, root->data) < 0)
		root->left = delete_node(data, root->left,
						compare_node, swap_data);
	else { // found...
		if(!root->right && !root->left) { // 0 child
			free(root);
			return NULL;	
		} else if(!root->right) { // 1 left child
			struct Node* temp = search_node_max(root->left);
			swap_data(temp, root);
			root->left = delete_node(data, root->left,
						    compare_node, swap_data);
		} else { // 1 right child or 2 child
			struct Node* temp = search_node_min(root->right);
			swap_data(temp, root);
			root->right = delete_node(data, root->right, 
						    compare_node, swap_data);
		}
	}
	root->balance_factor = height_of(root->left) - height_of(root->right);
	return balancer(root);
}

void int_pre_order(struct Node* root) {
	if(!root) return;
	printf("%d(%d)  ", *(int*)root->data, root->balance_factor);	
	int_pre_order(root->left);
	int_pre_order(root->right);
}

void str_pre_order(struct Node* root) {
	if(!root) return;
	printf("%s(%d)[", (char*)root->data, root->balance_factor);	
	str_pre_order(root->left);
	printf(", ");
	str_pre_order(root->right);
	printf("]");
}
















