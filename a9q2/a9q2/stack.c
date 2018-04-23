/*
-------------------------------------
File:    stack.c
Project: cp264_a9_mill8550
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-21
-------------------------------------
 */





#include "stack.h"


void push(snode **topp, snode *np) {
	if (*topp == NULL) {
		*topp = np;
		np->next = NULL;
	} else {
		np->next = *topp;
		*topp = np;
	}
}

snode *pop(snode **topp) {
	if (*topp) {
		snode *tmp = *topp;
		*topp = tmp->next;
		tmp->next = NULL;
		return tmp;

	} else
		return NULL;
	}
int peek(snode *top) {
	if (top == NULL) {
		printf("\nsnode IS EMPTY");
		return -1;
	} else
		return top->data;
}

void clean(snode **topp) {
	snode *temp;
	snode *np = *topp;
	while (np != NULL) {
		temp = np;
		np = np->next;
		free(temp);
	}
	*topp = NULL;
}

void push_back(snode **topp, snode **bottom, snode *np) {
	if (*topp == NULL) {
		*topp = np;
		*bottom = np;
		np->next = NULL;
	} else {
		(*bottom)->next = np;
		*bottom = np;
	}
}

snode *new_node(int val, int type) {
	snode *np = (snode *) malloc(sizeof(snode));
	np->data = val;
	np->type = type;
	np->next = NULL;
}

void display_stack(snode *top) {

	snode *p = top;
	if (p == NULL)
		printf("\nSTACK IS EMPTY");
	else {
		while (p != NULL) {
			printf("%d\n", p->data);
			p = p->next;
		}
	}
}

