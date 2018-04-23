/*
-------------------------------------
File:    a6q2.c
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
#include "expeval.h"

#include "stack.h"
#include "expeval.h"

int main(int argc, char *args[]) {
	char str[] = "9-((3*4)+8)/4";
	char *infix = str;
	if (argc > 1) infix = args[1];
	
	//printf("%s\n",infix); 
	
	char postfix[1000]; // = "22+"; // for testing

	InfixToPostfix(infix, postfix);
	//printf("%s\n",postfix); 
	
	int val = evaluatePostfix(postfix);
	printf("%s = %d", infix, val);
	
	return 0;
}
