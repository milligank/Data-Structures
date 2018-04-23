/*
-------------------------------------
File:    heap.c
Project: a10q1
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-04-01
-------------------------------------
 */


#include "heap.h"

heap *new_heap(int capacity) {
	heap *hp = (heap*) malloc(sizeof(heap));
	hp->capacity = capacity;
	hp->size = 0;
	hp->data = malloc(sizeof(DATATYPE) * capacity);
	return hp;
}

void insert(heap *h, DATATYPE value)
{
	unsigned int index, parent;
	DATATYPE *temp;

	// Resize the array if it is overflow
	if (h->size == h->capacity)
	{
		h->capacity <<= 1;
		temp = realloc(h->data, sizeof(DATATYPE) * h->capacity);

		if (temp) {
			h->data = temp;
		} else {
			temp = malloc(sizeof(DATATYPE) * h->capacity);
			if (temp) {
				memcpy(temp, h->data, sizeof(DATATYPE) * h->size);
				free(h->data);
				h->data = temp;
			} else {
				printf("memory expansion failed\n");
			}
		}
	}

	//heapify up
	for(index = h->size++; index; index = parent)
	{
		parent = (index - 1) >> 1;
		if (cmp(h->data[parent], value)) break;
		h->data[index] = h->data[parent];
	}
	h->data[index] = value;
}

// Removes the top element from the heap
DATATYPE extract_min(heap *h)
{
	unsigned int index, swap, other;
	DATATYPE top = h->data[0];
	DATATYPE temp = h->data[--h->size];

	// Resize the array size to a 1/4
	if ((h->size <= (h->capacity >> 2)) && (h->capacity > MIN_CAPACITY)) {
		h->capacity >>= 1;
		h->data = realloc(h->data, sizeof(DATATYPE) * h->capacity);
		if (!h->data) _exit(1); // Exit if the memory allocation fails
	}

	//heapify_down
	for(index = 0; 1; index = swap) {
		swap = (index << 1) + 1;
		if (swap >= h->size) break;
		other = swap + 1;
		if ((other < h->size) && cmp(h->data[other], h->data[swap]))
		swap = other;
		if (cmp(temp, h->data[swap]))
		break;
		h->data[index] = h->data[swap];
	}

	h->data[index] = temp;
	return top;
}

void display_heap(heap *h) {
	int i;
	for (i = 0; i < h->size; i++) {
		printf("\n(%d, %d) ", h->data[i]->key, h->data[i]->vertex);
	}
}

DATATYPE new_gnode(int key, int vertex) {
	gnode *np = malloc(sizeof(gnode));
	np->key = key;
	np->vertex = vertex;
	return np;
}

int cmp(DATATYPE a, DATATYPE b) {
	return a->key <= b->key ? 1 : 0;
}

void decrease_key(heap *h, int node_index, int keyvalue) {
	unsigned int index, parent;
	for (index = node_index; index; index = parent) {
		parent = (index - 1) >> 1;
		if (h->data[parent]->key <= keyvalue)
			break;
		h->data[index] = h->data[parent];
	}
	h->data[index]->key = keyvalue;
}

int find_index(heap *h, int vertex) {
	int i;
	for (i = 0; i < h->size; i++) {
		if (h->data[i]->vertex == vertex)
			return i;
	}
	return -1;
}




