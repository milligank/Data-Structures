/*
-------------------------------------
File:    expeval.h
Project: mill8550_a04
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-01-29
-------------------------------------
 */

#ifndef EXPEVAL
#define EXPEVAL

#include "stack.h"

void InfixToPostfix(char *infixstr, char *postfixstr);
int evaluatePostfix(char *postfixstr);
int getPriority(char opr);
int operand(char op);


#endif


