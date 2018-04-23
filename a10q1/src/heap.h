/*
-------------------------------------
File:    heap.h
Project: a10q1
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-04-01
-------------------------------------
 */


#ifndef HEAP_H_
#define HEAP_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN_CAPACITY 4
#define DATATYPE gnode*

typedef struct gnode {
	int key;
	int vertex;
} gnode;

typedef struct heap {
	unsigned int capacity;
	unsigned int size;
	DATATYPE *data;
}heap;

heap *new_heap(int);
void insert(heap *, DATATYPE);
DATATYPE extract_min(heap *);

void display_heap(heap *);

DATATYPE new_gnode(int, int);
int cmp(DATATYPE a, DATATYPE b);
void decrease_key(heap *h, int node, int newkeyvalue);
int find_index(heap *, int);


#endif /* HEAP_H_ */
