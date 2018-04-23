/*
-------------------------------------
File:    heap.h
Project: cp264_a9_mill8550
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-21
-------------------------------------
 */


#ifndef HEAP_H_
#define HEAP_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATATYPE int
#define MIN_CAPACITY 4

typedef struct heap {
	unsigned int capacity;
	unsigned int size;
	DATATYPE *data;
} heap;

heap *new_heap(int capacity);
void insert(heap *, DATATYPE);
DATATYPE extract_min(heap *);
void decrease_key(heap *h, int nodeindex, int newkeyvalue);
int find_index(heap *, DATATYPE);
void display_heap(heap *);
int cmp(DATATYPE a, DATATYPE b);
void heapify_down(heap *h, int index);
void heapify_up(heap *h, int index);


#endif /* HEAP_H_ */
