/*
 -------------------------------------
 File:    stats.h
 Project: a8q2.c
 file description
 -------------------------------------
 Author:  Kathleen Milligan
 ID:      160458550
 Email:   mill8550@mylaurier.ca
 Version  2018-03-09
 -------------------------------------
 */

#ifndef STATS
#define STATS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "avl.h"

typedef struct statistic_summary {
	tnode *bst;
	int count;
	float mean;
	float stddev;
} statdata;

void add_data(statdata *, char *, float);
void remove_data(statdata *, char *);
void display_stat(statdata *);
void clean_data(statdata *);

void merge_data(statdata *, statdata *); //merge tree of root2 into root1,

char letter_grade(float);
void data_report(statdata *, char *);
void data_import(statdata *, char *);
void print_to_file(tnode *, FILE *);

#endif
