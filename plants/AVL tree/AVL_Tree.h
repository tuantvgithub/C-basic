#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	void* data;
	int balance_factor;
	struct Node *left, *right;
};

struct Node* create_int_node(void* data, int data_size);
int int_compare(void* a, void* b);
void int_swap_data(struct Node* node_1, struct Node* node_2);

struct Node* create_str_node(void* data, int data_size);
int str_compare(void* a, void* b);
void str_swap_data(struct Node* node_1, struct Node* node_2);

struct Node* insert_node (
	void* value, int data_size, 
	struct Node* root, 
	int (*compare_node) (void*, void*),
	struct Node* (*create_node) (void*, int)
);

struct Node* left_rotate(struct Node* root);
struct Node* right_rotate(struct Node* root);
struct Node* left_right_rotate(struct Node* root);
struct Node* right_left_rotate(struct Node* root);
struct Node* balancer(struct Node* root);

struct Node* search_node_max(struct Node* root);
struct Node* search_node_min(struct Node* root);
struct Node* search_node(
	void* data,
	struct Node* root,
	int (*compare_node) (void*, void*)
);

struct Node* delete_node(
	void* data,
	struct Node* root,
	int (*compare_node) (void*, void*),
	void (*swap_data) (struct Node*, struct Node*)
);


int max(int a, int b);
int height_of(struct Node* root);
void swap_data(struct Node* a, struct Node* b);

void int_pre_order(struct Node* root);
void str_pre_order(struct Node* root);

#endif // AVL_TREE_H



