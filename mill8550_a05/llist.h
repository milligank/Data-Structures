/*
-------------------------------------
File:    llist.h
Project: mill8550_a04
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-01-29
-------------------------------------
 */

#ifndef LLIST_H
#define LLIST_H

#define MAX_NAME 40

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
	int data;
	struct node *next;
	float score;
	char name[MAX_NAME];
} node;

void clean(node **start);
void display(node *start);
node *search(node *start, char *name);
void insert(node **start, char *name, float score);
void delete(node **start, char *name);
void data_import(node **startp, char *filename);
void data_report(node *start, char *filename);
char letter_grade(float score);
void swap(float *first, float *second );
void quick_sort(float *a, int m, int n);
float median(node *start);

#endif
