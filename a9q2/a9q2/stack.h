/*
-------------------------------------
File:    stack.h
Project: cp264_a9_mill8550
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-21
-------------------------------------
 */


#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

#include "hash.h"

typedef struct node {
	int data;
	int type; //0:integer number; 1:opeator;2:symbol; 3:( ; 4:symbol
	struct node *next;
} snode;

snode *new_node(int val, int type);
void push(snode **topp, snode *np);
snode *pop(snode **topp);
void push_back(snode **top, snode **bottom, snode *np);
void clean(snode **topp);
void display_stack(snode *top);



#endif /* STACK_H_ */
