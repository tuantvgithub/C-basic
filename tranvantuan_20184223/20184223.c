// ho ten : Tran Van Tuan
// mssv : 20184223

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========== for binary search tree =========== */

typedef struct BST_Data {
	char en[30]; // key
	char vi[30];
} BST_Data;

typedef struct BST_Node {
	BST_Data data;
	struct BST_Node *left, *right;
} BST_Node;

BST_Data createData(char* en, char* vi) {
	BST_Data temp;

	strcpy(temp.en, en);
	strcpy(temp.vi, vi);
	return temp;
}

BST_Node* createNode(BST_Data data) {
	BST_Node* temp = (BST_Node*)malloc(sizeof(BST_Node));
	
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

void insertNode(BST_Data data, BST_Node** root) {
	if(!(*root)) {
		*root = createNode(data);
	} else if(strcmp(data.en, (*root)->data.en) > 0){
		insertNode(data, &(*root)->right);
	} else if(strcmp(data.en, (*root)->data.en) < 0){
		insertNode(data, &(*root)->left);
	} else return;
}

/* =========== doc file va in ra man hinh ========== */

void docFile(BST_Node** root) {
	FILE* fl = fopen("tudien.txt", "r");
	BST_Data data;
	
	if(!fl) printf("Doc file that bai.\n");
	else {
		while(fscanf(fl, "%s%s", data.en, data.vi) != EOF) {
			printf("%s %s\n", data.en, data.vi);
			insertNode(data, root);
		}
		fclose(fl);
	}
	return;
}

/* =========== 1.duyet theo chieu sau va in cay BST ========== */

void preoOrder(BST_Node* root) {
	if(!root) return;

	printf("%s\n", root->data.en);
	preoOrder(root->left);
	preoOrder(root->right);
}

/* ========== 2.them tu vao cay BST ========== */

void addWord(BST_Node** root) {
	BST_Data data;

	printf("Nhap tu : ");
	while(getchar() != '\n');
	scanf("%[^\n]s", data.en);
	printf("Nhap nghia : ");
	while(getchar() != '\n');
	scanf("%[^\n]s", data.vi);

	insertNode(data, root);
	return;
}

/* =========== 3.dich tu ========== */

BST_Node* searchByEnglishWord(char* enWord, BST_Node* root) {
	if(!root) return NULL;
	else if(strcmp(enWord, root->data.en) > 0) {
		printf("%s ", root->data.en);		
		return searchByEnglishWord(enWord, root->right);
	}
	else if(strcmp(enWord, root->data.en) < 0) {
		printf("%s ", root->data.en);
		return searchByEnglishWord(enWord, root->left);
	}
	else return root;
}

void dich(BST_Node* root) {
	char enWord[30];
	BST_Node* temp = NULL;

	printf("Nhap tu tieng anh : ");
	while(getchar() != '\n');
	scanf("%[^\n]s", enWord);
	
	printf("\n");
	temp = searchByEnglishWord(enWord, root);
	if(!temp)
		printf("\n\nKhong tim thay tu can tra.\n");
	else {
		printf("\n\nNghia : %s\n", temp->data.vi);
	}
	return;
}

void main() {
	BST_Node* root = NULL;
	int event = 0;
	
	printf("Noi dung file tudien.txt :\n\n");
	docFile(&root);
	
	do {
		printf("\n---------------Menu---------------\n");
		printf("1. duyet theo chieu sau va in ra\n");
		printf("2. them tu\n");
		printf("3. dich\n");
		printf("4. thoat\n");
		printf("Lua chon cua ban : "); scanf("%d", &event);
		
		printf("\n");
		switch(event) {
			case 1:
				preoOrder(root);
				break;
			case 2:
				addWord(&root);
				break;
			case 3:
				dich(root);
				break;
			case 4:
				break;
			default:
				printf("ERROR.\n");
		}
	} while(event != 4);	
	return;
}





