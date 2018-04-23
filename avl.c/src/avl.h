/*
-------------------------------------
File:    avl.h
Project: avl.c
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-05
-------------------------------------
 */



#include<stdio.h>
#include<stdlib.h>

// An AVL tree node
struct Node {
	int key;
	int height;
	struct Node *left;
	struct Node *right;
};

int is_balanced(struct Node *node);
void preOrder(struct Node *root);
struct Node* deleteNode(struct Node* root, int key);
struct Node * minValueNode(struct Node* node);
struct Node* insert(struct Node* node, int key);
int getBalance(struct Node *N);
struct Node *leftRotate(struct Node *x);
struct Node *rightRotate(struct Node *y);
struct Node* newNode(int key);
int height(struct Node *N);
int max(int a, int b);
void print_tree(struct Node *node, int);





