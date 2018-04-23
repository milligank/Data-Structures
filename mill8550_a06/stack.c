/*
-------------------------------------
File:    stack.c
Project: mill8550_a04
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-01-29
-------------------------------------
 */


#include "stack.h"

void push(stack **topp, int val) {
	stack *ptr = (stack*) malloc(sizeof(stack));
	ptr->data = val;
	if (*topp == NULL) {
		ptr->next = NULL;
		*topp = ptr;
	}else{
		ptr->next = *topp;
		*topp = ptr;
	}
}

void pop(stack **topp) {
	if (*topp != NULL){
	    stack *np = *topp;
		*topp = np->next;
	}
}

int peek(stack *top) {
	if (top == NULL) {
		printf("\nsnode IS EMPTY");
		return -1;
	}	
	else
		return top->data;
}

void clean(stack **topp) {
	stack *temp;
	stack *np = *topp;
	while (np != NULL){
		temp = np;
		np = np->next;
		free(temp);
	}
	*topp = NULL;
}





