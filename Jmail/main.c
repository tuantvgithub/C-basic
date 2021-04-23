#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "constant.h"
#include "action.h"

void main() {
	int event;
	FILE* fl = fopen("network.txt", "r");
	BST_NODE* root = NULL;

	if(fl) {
		root = loadFileNetwork(fl);
		fclose(fl);
	}

	printf("\n========== Welcome to demo of jmail ==========\n\n");
	
	do {	
		printf("1. Sign in\n");
		printf("2. Sign up\n");
		printf("0. Exit\n");

		printf("You choose : "); scanf("%d", &event);

		switch(event) {
			case 0:
				break;
			case 1:
				signIn(&root);
				break;
			case 2:
				signUp(&root);
				break;
			default:
				printf("ERROR!!\n");
		}		
	} while(event != 0);	

	return;
}








