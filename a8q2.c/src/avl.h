/*
-------------------------------------
File:    avl.h
Project: a8q1.c
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
 Email:   mill8550@mylaurier.ca
Version  2018-03-09
-------------------------------------
 */


#ifndef AVL_H
#define AVL_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node {
	char name[20];
	float score;
	int height;
	struct node *left;
	struct node *right;

} tnode;

tnode *new_node(char *, float);
tnode *rotate_left(tnode *);
tnode *rotate_right(tnode *);
void insert(tnode **, char *, float);
void delete(tnode **, char *);
tnode *extract_smallest_node(tnode **rootp);
tnode *search(tnode *, char *);
void clean_tree(tnode **);

void merge_tree(tnode **, tnode *); //merge tree of root2 into root1,

int height(tnode *);
int balance_factor(tnode *);
void display_inorder(tnode *);
void display_tree(tnode *root, int prelen);

int max(int a, int b); //return a>=b?a:b;
void merge_tree(tnode **rootp1, tnode *root2);

#endif
