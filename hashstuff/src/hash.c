/*
-------------------------------------
File:    hash.c
Project: lab09
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-19
-------------------------------------
 */


#include <stdio.h>
#include <malloc.h>
#define SIZE 20

typedef struct DataItem {
	int key;
	int data;
} hashdata;

int hashCode(int key) {
	return key % SIZE;
}

//create hash by dynamic created array
hashdata **new_hash(int size) {
	hashdata **hp = (hashdata**) malloc(sizeof(hashdata*) * size);
	int i;
	for (i = 0; i < size; i++)
		*(hp + i) = NULL;
	return hp;
}

hashdata *search(hashdata *hashArray[], int key) {
//or hashdata *search(hashdata **hashArray, int key) {

	int hashIndex = hashCode(key);

	while (hashArray[hashIndex] != NULL) {
		if (hashArray[hashIndex]->key == key && hashArray[hashIndex]->key != -1)
			return hashArray[hashIndex];

		++hashIndex;
		if (hashIndex >= SIZE)
			hashIndex %= SIZE; //wrap around the table
	}

	return NULL;
}

void insert(hashdata *hashArray[], int key, int data) {

	hashdata *item = (hashdata*) malloc(sizeof(hashdata));
	item->data = data;
	item->key = key;
	printf("inserting %d\n", data);

	int hashIndex = hashCode(key);

	printf("initial hash index = %d\n", hashIndex);
	//move in array until an empty or deleted cell
	while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
		++hashIndex;
		if (hashIndex >= SIZE)
			hashIndex %= SIZE; //wrap around the table
	}
	hashArray[hashIndex] = item;

	printf("final hash index = %d\n", hashIndex);
}

int delete(hashdata *hashArray[], hashdata *item) {
	int key = item->key;
	int hashIndex = hashCode(key);

	//move in array until an empty
	while (hashArray[hashIndex] != NULL) {
		if (hashArray[hashIndex]->key == key
				&& hashArray[hashIndex]->key != -1) {
			hashArray[hashIndex]->key = -1;
			return 1;
		}
		++hashIndex;
		if (hashIndex >= SIZE)
			hashIndex %= SIZE; //wrap around the table
	}
	return 0;
}

void display(hashdata *hashArray[]) {
	int i = 0;
	for (i = 0; i < SIZE; i++) {
		if (hashArray[i] != NULL)
			printf("(%d,%d,%d)\n", i, hashArray[i]->key, hashArray[i]->data);
		else
			printf("(%d, NULL)\n", i);
	}
	printf("\n");
}

int main() {
	//use static array to create array of DataItem pointers and initialized to be NULL
	hashdata *hashArray[SIZE] = { 0 };

	//or use dynamically created array
	//hashdata **hashArray = new_hash(SIZE);
	insert(hashArray, 1, 20);
	insert(hashArray, 2, 70);
	insert(hashArray, 42, 80);
	insert(hashArray, 4, 25);
	insert(hashArray, 12, 44);
	insert(hashArray, 14, 32);
	insert(hashArray, 17, 11);
	insert(hashArray, 13, 78);
	insert(hashArray, 37, 97);

	display(hashArray);

	hashdata *item = search(hashArray, 37);
	if (item != NULL) {
		printf("Element found: %d\n", item->data);
	} else {
		printf("Element not found\n");
	}

	delete(hashArray, item);
	item = search(hashArray, 37);
	if (item != NULL) {
		printf("Element found: %d\n", item->data);
	} else {
		printf("Element not found\n");
	}

	display(hashArray);

	return 0;
}




