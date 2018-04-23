/*
-------------------------------------
File:    bst.h
 Project: bst
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-03
-------------------------------------
 */



#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
	char name[20];
	float score;
	struct node *left;
	struct node *right;
} tnode;

void display(tnode *);
void insert(tnode **, char *, float);
void delete(tnode **, char *);
tnode *get_smallest_element(tnode *);
tnode *search(tnode *, char *);
void clean(tnode *);

#endif
