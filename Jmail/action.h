#ifndef __ACTION_H__
#define __ACTION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "constant.h"

BST_NODE* loadFileNetwork(FILE* fl);
void printDataToFile(BST_DATA data, FILE* fl);
void updateNetwork(BST_NODE* root, FILE* fl);

void getName(char* name);
void getSdt(char* sdt);
void getYearOfBirth(char* yearOfBirth);
void getUser(char* user);
void getPass(char* pass);

/* -------------------- Login ---------------------- */

/* -------- Admin mode -------- */
void listOfUser(BST_NODE* root);
void deleteAccount(BST_NODE** root);

void adminMode(BST_NODE** root);

/* -------- Client mode ------- */
char* getNameFileInbox(char* user);
char* getNameFileOutbox(char* user);
void mailing(BST_NODE* curNode, BST_NODE** root);
void inbox(BST_NODE* curNode);
void outbox(BST_NODE* curNode);
void changePass(BST_NODE* curNode);
void editInformation(BST_NODE* curNode);

void clientMode(BST_NODE* curNode, BST_NODE** root);

/* -------- Login ------------- */
int findAccount(BST_DATA acc, BST_NODE* root);

void signIn(BST_NODE** root);

/* -------------------- Logout --------------------- */
int userAlreadyExists(char* user, BST_NODE* root);
void createFileBox(BST_DATA* temp);
BST_DATA getAccount(BST_NODE* root);

void signUp(BST_NODE** root);

#endif //__ACTION_H__


