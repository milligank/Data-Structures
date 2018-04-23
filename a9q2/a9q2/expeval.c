/*
-------------------------------------
File:    expeval.c
Project: cp264_a9_mill8550
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-21
-------------------------------------
 */



#include "expeval.h"

int getPriority(char op) {
	if (op == '/' || op == '*' || op == '%')
		return 1;
	else if (op == '+' || op == '-')
		return 0;
	return 0;
}

int isOperator(char op) {
	if (op == '/' || op == '*' || op == '%' || op == '+' || op == '-')
		return 1;
	else
		return 0;
}

int isSymbol(char s) {
	if (!isOperator(s) && !isdigit(s) && s != ')' && s != '(') {
		return 1;
	} else
		return 0;
}

int infix_eval(hashdata *hashmap[], char *infixstr) {
	//convert prefix to postfix expression using stack as working data structure and queue to hold postfix expression
	snode *front = NULL, *rear = NULL, *top = NULL;
	char *p = infixstr;
	char symbol[11] = { 0 };
	int sign = 1;
	int num = 0;

	while (*p) {
		if (*p == '-' && (p == infixstr || *(p - 1) == '(')) {
			sign = -1;
		} else if (*p == '(') {
			push(&top, new_node('(', 3));
		} else if (*p >= 48 && *p <= 57) {
			num = *p - '0';
			while ((*(p + 1) >= 48 && *(p + 1) <= 57)) {
				num = num * 10 + *(p + 1) - '0';
				p++;
			}
			push_back(&front, &rear, new_node(sign * num, 0));
			sign = 1;
		} else if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
			char *sp = symbol;
				*sp = *p;
			while ((*(p + 1) >= 'a' && *(p + 1) <= 'z')
					|| (*(p + 1) >= 'A' && *(p + 1) <= 'Z')
					|| (*(p + 1) >= '0' && *(p + 1) <= '9')) {
				p++;
				sp++;
				*sp = *p;
			}
			*(sp + 1) = '\0';

			if (search(hashmap, symbol) == NULL) {
				printf("%s can be evaluated\n", symbol);
				return -1;
			} else {
				num = get(hashmap, symbol);
				push_back(&front, &rear, new_node(num, 0));
			}
		} else if (*p == ')') {
			while (top) {
				if (top->type == 3) {
					free(pop(&top));
					break;
				}
				push_back(&front, &rear, pop(&top));
			}
		} else if (isOperator(*p)) {
			while (top && top->type == 1
					&& getPriority(top->data) >= getPriority(*p)) {
				push_back(&front, &rear, pop(&top));
				}
			push(&top, new_node(*p, 1));
			}
		p++;
	}
	while (top) {
		push_back(&front, &rear, pop(&top));
		}

	//using the existing values of symbols from hashtab to do evaluation, return the final evaluation result
	return num;
	}
int statement_process(hashdata *hashmap[], char* statement) {
	char s[10] = { 0 };
	char *dest = strstr(statement, "=");
	if (dest)
		*dest = '\0';
	else
		dest = statement;
	strcpy(s, statement);
	if (isSymbol(s[0])) {
		put(hashmap, s, infix_eval(hashmap, dest + 1));
		return 1;
	}
	return 0;
}



void trim_space(char *s) {
	if (s == NULL || *s == '\0')
		return;
	char *p = s, *dp = s;
	while (*p) {
		if (*p != ' ')
			*dp++ = *p;
		p++;
	}
	*dp = '\0';
}

