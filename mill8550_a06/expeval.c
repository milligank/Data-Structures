/*
-------------------------------------
File:    expeval.c
Project: mill8550_a04
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-01-29
-------------------------------------
 */

#include "expeval.h"

void InfixToPostfix(char *infixstr, char *postfixstr) {
	stack *top = NULL;
	
	strcpy(postfixstr, "");
	int i = 0, j = 0;
	char temp;
	
	while (infixstr[i] != '\0') {
		if (infixstr[i] == '(') {
			push(&top, infixstr[i]);
			i++;
		} else if (infixstr[i] == ')') {
			//while ((top != -1) && (stk[top] != '(')) {
			 
			while ((top != NULL) && (peek(top) != '(')) { 
				postfixstr[j] = peek(top);
				pop(&top);
				j++;
			}
			if (top == NULL) {
				printf("\n INCORRECT EXPRESSION");
				return;
			}

			temp = peek(top);
			pop(&top);
			
			i++;
			
		} else if (isdigit(infixstr[i]) || isalpha(infixstr[i])) {
			postfixstr[j] = infixstr[i];
			j++;
			i++;
		} else if (infixstr[i] == '+' || infixstr[i] == '-' || infixstr[i] == '*' || infixstr[i] == '/' || infixstr[i] == '%') {
			while ((top != NULL) && (peek(top) != '(') && (getPriority(peek(top)) > getPriority(infixstr[i]))) {
				
				postfixstr[j] = peek(top);
				pop(&top);
				
				j++;
			}
			push(&top, infixstr[i]);
			i++;
		}else{
			printf("\n INCORRECT ELEMENT IN EXPRESSION");
			return;
		}
	}
	while ((top != NULL) && (peek(top) != '(')) {
		postfixstr[j] = peek(top);
		pop(&top);
		j++;
	}
	postfixstr[j] = '\0';	
}

int evaluatePostfix(char *exp) {
	int value=0;
	stack *top = NULL;
	int i = 0, op1, op2;
	
	while (exp[i] != '\0') {
		if (isdigit(exp[i])) {
			push(&top, (int)(exp[i] - '0'));
		}else{
				op2 = peek(top);
			pop(&top);
			
			op1 = peek(top);
			pop(&top);
			
			switch (exp[i]) {
			case '+':
				value = op1 + op2;
				break;
			case '-':
				value = op1 - op2;
				break;
			case '/':
				value = op1 / op2;
				break;
			case '*':
				value = op1 * op2;
				break;
			case '%':
				value = (int) op1 % (int) op2;
				break;
			}
			push(&top, value);
		}
		i++;
	}
	return value;
}

int getPriority(char op) {
	if (op == '/' || op == '*' || op == '%') return 1;
	else if (op == '+' || op == '-') return 0;
	return 0;
}


