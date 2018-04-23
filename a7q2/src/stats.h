/*
-------------------------------------
File:    stats.h
 Project: stats.c
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-03
-------------------------------------
 */



#ifndef STATS_H
#define STATS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"

typedef struct statistic_summary {
	tnode *bst;
	int count;
	float mean;
	float stddev;
} statdata;

void add_data(statdata *, char *, float);
void remove_data(statdata *, char *);
void display_stat(statdata *);

char letter_grade(float);
void data_report(statdata *, char *);
void data_import(statdata *, char *);
void print_to_file(tnode *, FILE *);

#endif
