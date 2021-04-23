#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVL_Tree.h"

int main(int argc, char* argv[]) {
	char* s[] = {
		"a",
		"b",
		"c",
		"d",
		"e",
		"f",
		"g",
		"h"
	};	
	struct Node* root = NULL;
	int i = 0;

	while(getchar() == '\n' && i < 4) {
		root = insert_node(s[i], sizeof(char) * strlen(s[i]), root, 
					str_compare, create_str_node);
		i++;
		str_pre_order(root);
		printf("\n");
	}
	
	char partem[] = "a";
	root = delete_node(partem, root, 
			str_compare, str_swap_data);

	str_pre_order(root);
	printf("\n");
	
	return 0;
}
