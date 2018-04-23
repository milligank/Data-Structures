/*
-------------------------------------
File:    stack.h
Project: mill8550_a04
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-01-29
-------------------------------------
 */

#ifndef STACK
#define STACK

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
	int data;
	struct node *next;
} stack;


void push(stack **topp, int);
void pop(stack **topp);
int peek(stack *top);
void clean(stack **topp);

#endif
