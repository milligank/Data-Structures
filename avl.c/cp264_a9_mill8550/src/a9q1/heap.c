/*
 -------------------------------------
 File:    heap.c
 Project: cp264_a9_mill8550
 file description
 -------------------------------------
 Author:  Kathleen Milligan
 ID:      160458550
 Email:   mill8550
 Version  2018-03-21
 -------------------------------------
 */



#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

heap *new_heap(int capacity) {
	heap *hp = (heap*) malloc(sizeof(heap));
	hp->capacity = capacity;
	hp->size = 0;
	hp->data = (DATATYPE*) malloc(sizeof(DATATYPE) * capacity);
	return hp;
}

void insert(heap *h, DATATYPE value) {
	int *temp;
	if (h->size == h->capacity) {
		h->capacity *= 2;
		temp = realloc(h->data, sizeof(int) * h->capacity);
		if (temp) {
			h->data = temp;
		} else {
			temp = malloc(sizeof(int) * h->capacity);
			if (temp) {
				memcpy(temp, h->data, sizeof(int) * h->size);
				free(h->data);
				h->data = temp;
			}

		}
	}

	h->data[h->size] = value;
	heapify_up(h, h->size);
	h->size++;

}

void heapify_up(heap *h, int index) {
	int parentIndex = 0;
	int tempVal = 0;

	if (h && h->size > 0 && index > 0) {
		parentIndex = (index - 1) / 2;
		if (h->data[parentIndex] > h->data[index]) {
			tempVal = h->data[parentIndex];
			h->data[parentIndex] = h->data[index];
			h->data[index] = tempVal;
			heapify_up(h, parentIndex);
		}
	}
}


DATATYPE extract_min(heap *h) {
	DATATYPE min;
	if (h && h->size > 0) {
		min = h->data[0];
		h->data[0] = h->data[h->size - 1];
		h->size--;
		heapify_down(h, 0);
	} else {
		printf("Operation Failed! Heap is Empty!\n");
		}
	return min;
}

void heapify_down(heap *h, int index) {
	int leftChildIndex, rightChildIndex, smallIndex, tempVal;

	leftChildIndex = (index * 2) + 1;
	rightChildIndex = (index * 2) + 2;

	if (rightChildIndex >= h->size && leftChildIndex >= h->size)
		return;
	else if (rightChildIndex >= h->size) {
		smallIndex = leftChildIndex;
	} else {
		smallIndex =
				h->data[leftChildIndex] <= h->data[rightChildIndex] ?
						leftChildIndex : rightChildIndex;
	}

	if (h->data[index] > h->data[smallIndex]) {
		tempVal = h->data[index];
		h->data[index] = h->data[smallIndex];
		h->data[smallIndex] = tempVal;
		heapify_down(h, smallIndex);
	}
}

void decrease_key(heap *h, int node_index, int keyvalue) {
//your implementation

	DATATYPE tempVal;

	h->data[node_index] = keyvalue;
	while (node_index != 0
			&& h->data[(node_index - 1) / 2] > h->data[node_index]) {
		tempVal = h->data[(node_index - 1) / 2];
		h->data[(node_index - 1) / 2] = h->data[node_index];
		h->data[node_index] = tempVal;
		node_index = (node_index - 1) / 2;
	}
}

int find_index(heap *h, DATATYPE value) {

	int i = 0;

	for (i = 0; i < h->size; i++) {
		if (h->data[i] == value)
			return i;
	}

	return -1;
}

void display_heap(heap *hp) {
	printf("\nsize=%d;capacity=%d\n", hp->size, hp->capacity);
	if (hp->size > 0)
		printf("%d", hp->data[0]);
	if (hp->size > 1) {
		int i;
		for (i = 1; i < hp->size; i++)
			printf(", %d", hp->data[i]);
		printf("\n");
	}
}

int cmp(DATATYPE a, DATATYPE b) {
	return a <= b ? 1 : 0;
}
