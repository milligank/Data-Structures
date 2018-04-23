/*
-------------------------------------
File:    expeval.h
Project: cp264_a9_mill8550
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-21
-------------------------------------
 */


#ifndef EXPEVAL_H_
#define EXPEVAL_H_

#include "hash.h"
#include "stack.h"

int getPriority(char opr);
int isOperator(char op);
int isSymbol(char s);

void trim_space(char *s);
int infix_eval(hashdata *hashmap[], char *infixstr);
int statement_process(hashdata *hashmap[], char* statement);

#endif /* EXPEVAL_H_ */
