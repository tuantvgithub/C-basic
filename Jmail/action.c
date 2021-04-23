#include "action.h"

BST_NODE* loadFileNetwork(FILE* fl) {
	BST_NODE* root = NULL;
	BST_DATA temp;
	int end = 1;

	while(end) {
		fscanf(fl, "%s%s%s%s", temp.user, temp.pass, temp.info.sdt, temp.info.yearOfBirth);
		if(fscanf(fl, "%[^\n]s", temp.info.name) == EOF)
			end = 0;
		insertNode(temp, &root);
	}	

	return root;
}

void printDataToFile(BST_DATA data, FILE* fl) {
	fprintf(fl, "%s\t%s\t%s\t%s\t%s\n", 
		data.user,
		data.pass,
		data.info.sdt,
		data.info.yearOfBirth,
		data.info.name);
	return;
}

void updateNetwork(BST_NODE* root, FILE* fl) { // fl = network.txt
	if(!root) return;
	updateNetwork(root->left, fl);
	printDataToFile(root->data, fl);
	updateNetwork(root->right, fl);	
}

void getName(char* name) {
	printf("- Full name : ");
	while(getchar() != '\n');
	scanf("%[^\n]s", name);
}

int sdtError(char* sdt) {
	for(int i = 0; sdt[i] != '\0'; i++) {
		if(sdt[i] < 48 || sdt[i] > 57)
			return 1;
	}

	return 0;
}

void getSdt(char* sdt) {
	do {
		printf("- Sdt : ");
		while(getchar() != '\n');
		scanf("%[^\n]s", sdt);
	} while(sdtError(sdt));
}

int yearOfBirthError(char* year) {
	for(int i = 0; year[i] != '\0'; i++) {
		if(year[i] < 48 || year[i] > 57)
			return 1;
	}

	return 0;	
}

void getYearOfBirth(char* yearOfBirth) {
	do {
		printf("- Year of birth : ");
		while(getchar() != '\n');
		scanf("%[^\n]s", yearOfBirth);
	} while(yearOfBirthError(yearOfBirth));
}

int userError(char* user) {
	for(int i = 0; user[i] != '\0'; i++) {
		if(user[i] == ' ')
			return 1;
	}

	return 0;
}

void getUser(char* user) {
	do {
		turn--;
		printf("- Username (no space): ");
		while(getchar() != '\n');
		scanf("%s", user);
	} while(userError(user));
}

int passError(char* pass) {
	if(strlen(pass) < 6) return 1;
	for(int i = 0; pass[i] != '\0'; i++) {
		if(pass[i] == ' ')
			return 1;
	}

	return 0;
}

void getPass(char* pass) {
	do {
		turn--;
		printf("- Password (no space, minimum 6 character): ");
		while(getchar() != '\n');
		scanf("%s", pass);
	} while(passError(pass));
}

/* -------------------------- Login ---------------------------- */

/* ---------- Admin mode ---------- */

void listOfUser(BST_NODE* root) {
	if(!root) return;
	listOfUser(root->left);
	if(strcmp(root->data.user, "Admin0") != 0)
		printData(root->data);
	listOfUser(root->right);
}

void deleteAccount(BST_NODE** root) {
	char userDel[SIZE_USER];
	BST_NODE* del = NULL;

	getUser(userDel);
	del = searchNodeByUser(userDel, (*root));
	deleteNode(del->data, root);

	return;	
}

void adminMode(BST_NODE** root) {
	int event;
	FILE* fl = NULL;
	
	do {
		printf("1. List of user\n");
		printf("2. Delete account\n");
		printf("3. update network\n");
		printf("4. back\n");

		printf("You choose : "); scanf("%d", &event);

		switch(event) {
			case 1:
				listOfUser((*root));
				break;
			case 2:
				deleteAccount(root);
				break;
			case 3:
				fl = fopen("network.txt", "w");
				updateNetwork((*root), fl);
				fclose(fl);
				break;
			case 4:
				break;
			default:
				printf("ERROR!\n");
		}
	} while(event != 4); 
}

/* ----------- Client mode ----------- */

char* getNameFileInbox(char* user) {
	int n = strlen(user);
	char* name = (char*)malloc(sizeof(char) * (n + 6));

	strcpy(name, user);
	strcat(name, "in.txt");

	return name;
}

char* getNameFileOutbox(char* user) {
	int n = strlen(user);
	char* name = (char*)malloc(sizeof(char) * (n + 7));

	strcpy(name, user);
	strcat(name, "out.txt");

	return name;
}

void mailing(BST_NODE* curNode, BST_NODE** root) {
	char temp[SIZE_CONTENT]; // address
	char* nameFileOutbox = getNameFileOutbox(curNode->data.user); // of sender
	char* nameFileInbox = NULL; // address
	BST_NODE* address = NULL;
	int turn = 2;
	
	do {	
		getUser(temp);
		address = searchNodeByUser(temp, (*root));
		if(!address) {
			printf("- Not found.\n");
			turn--;
		}	
		else {
			nameFileInbox = getNameFileInbox(address->data.user);
			address->data.inbox = fopen(nameFileInbox, "a");
			curNode->data.outbox = fopen(nameFileOutbox, "a");

			printf("- Content () :\n");
			while(getchar() != '\n');
			scanf("%[^\n]s", temp);
			
			fprintf(address->data.inbox, "%s\n%s\n%s", curNode->data.user, temp, "/\n");
			fprintf(curNode->data.outbox, "%s\n%s\n%s", address->data.user, temp, "/\n");
		}
	} while(!address && turn != 0);
	
	fclose(curNode->data.outbox);
	fclose(address->data.inbox);
	
	return;
}

void inbox(BST_NODE* curNode) {
	char* nameFile = getNameFileInbox(curNode->data.user);
	char c;

	curNode->data.inbox = fopen(nameFile, "r");

	if(curNode->data.inbox) {
		do {
			c = fgetc(curNode->data.inbox);
			if(c != '/' && c != EOF)			
				printf("%c", c);
		} while(c != EOF);
		fclose(curNode->data.inbox);
	}

	return;
}

void outbox(BST_NODE* curNode) {
	char* nameFile = getNameFileOutbox(curNode->data.user);
	char c;

	curNode->data.outbox = fopen(nameFile, "r");

	if(curNode->data.outbox) {
		do {
			c = fgetc(curNode->data.inbox);
			if(c != '/' && c != EOF)			
				printf("%c", c);
		} while(c != EOF);
		fclose(curNode->data.outbox);
	}

	return;
}

void changePass(BST_NODE* curNode) {
	char newPass[SIZE_PASS];
	char confirmPass[SIZE_PASS];
	int turn = 2;

	do {
		printf("- New password : ");
		while(getchar() != '\n');
		scanf("%[^\n]s", newPass);
	} while(passError(newPass));
	
	for(; turn > 0; turn--) {
		printf("- Confirm password : ");
		while(getchar() != '\n');
		scanf("%[^\n]s", confirmPass);
		
		if(!strcmp(confirmPass, newPass))
			break;
	}	

	strcpy(curNode->data.pass, newPass);

	return;
}

void editInformation(BST_NODE* curNode) {
	char newName[SIZE_NAME],
	     newSdt[SIZE_SDT],
	     newYearOfBirth[SIZE_YEAR_OF_BIRTH];

	getName(newName);
	getSdt(newSdt);
	getYearOfBirth(newYearOfBirth);

	strcpy(curNode->data.info.name, newName);
	strcpy(curNode->data.info.sdt, newSdt);
	strcpy(curNode->data.info.yearOfBirth, newYearOfBirth);	

	return;
}

void clientMode(BST_NODE* curNode, BST_NODE** root) {
	int event;
	FILE* fl = NULL;
	
	do {
		printf("1. Mailing\n");
		printf("2. Inbox\n");
		printf("3. Outbox\n");
		printf("4. Change password\n");
		printf("5. Edit information\n");
		printf("6. Sign out\n");

		printf("Your choose : "); scanf("%d", &event);

		switch(event) {
			case 1:
				mailing(curNode, root);
				break;
			case 2:
				inbox(curNode);
				break;
			case 3:
				outbox(curNode);
				break;
			case 4:
				changePass(curNode);
				fl = fopen("network.txt", "w");				
				updateNetwork((*root), fl);
				fclose(fl);
				break;
			case 5:		
				editInformation(curNode);
				fl = fopen("network.txt", "w");				
				updateNetwork((*root), fl);
				fclose(fl);
				break;
			case 6:
				break;
			default:
				printf("ERROR!\n");		
		}
	} while(event != 6);
	return;
}

int findAccount(BST_DATA acc, BST_NODE* root) { // key is user
	BST_NODE* temp = searchNodeByData(acc, root);
	
	if(!temp || strcmp(acc.pass, temp->data.pass) != 0)
		return NONE;
	else {
		if(!strcmp(acc.user, "Admin0"))
			return ADMIN;
		else
			return CLIENT;
	}
}

void signIn(BST_NODE** root) {
	BST_DATA acc;
	BST_NODE* curNode;
	Mode mode;

	getUser(acc.user);
	getPass(acc.pass);
	
	mode = findAccount(acc, (*root));

	switch(mode) {
		case NONE:
			printf("Username or password is incorrect.\n");
			break;
		case ADMIN:
			printf("You are logged in as a admin.\n");
			adminMode(root);
			break;
		case CLIENT:
			curNode = searchNodeByData(acc, (*root));
			printf("You are logged in as a client.\n");
			clientMode(curNode, root);
			break;
	}
	
	return;
}

/* -------------------------- sign up ---------------------------- */

int userAlreadyExists(char* user, BST_NODE* root) {
	if(!root) return 0;		
	else if(strcmp(user, root->data.user) == 0)
		return 1;
	else if(strcmp(user, root->data.user) > 0)		
		return userAlreadyExists(user, root->right);
	else		
		return userAlreadyExists(user, root->left);
}

void createFileBox(BST_DATA* temp) {
	char nameInbox[SIZE_USER + 10], nameOutbox[SIZE_USER + 10];
	
	strcpy(nameInbox, (*temp).user);
	strcat(nameInbox, "in.txt");
	strcpy(nameOutbox, (*temp).user);
	strcat(nameOutbox, "out.txt");

	(*temp).inbox = fopen(nameInbox, "a");
	(*temp).outbox = fopen(nameOutbox, "a");

	fclose((*temp).inbox);
	fclose((*temp).outbox);

	return;
}

BST_DATA getAccount(BST_NODE* root) {
	BST_DATA temp;

	getName(temp.info.name);	
	getSdt(temp.info.sdt);
	getYearOfBirth(temp.info.yearOfBirth);

	do {
		getUser(temp.user);
		if(userAlreadyExists(temp.user, root))
			printf("Already exists");
	} while(userAlreadyExists(temp.user, root));

	getPass(temp.pass);
	createFileBox(&temp);

	return temp;
}

void signUp(BST_NODE** root) {
	BST_DATA newAccount;
	FILE* fl = fopen("network.txt", "w");

	if(!fl) printf("Failed to open file 'network.txt'.\n");
	else {
		newAccount = getAccount((*root));
		insertNode(newAccount, root);		
		updateNetwork((*root), fl);
		
		if(userAlreadyExists(newAccount.user, (*root))) {
			printf("successfully.\n");
		} else {
			printf("failed.\n");
		}
		fclose(fl);
	}

	return;
}



