/*
-------------------------------------
File:    hash.c
Project: cp264_a9_mill8550
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-21
-------------------------------------
 */

#include "hash.h"


int hash(char *name) {
	unsigned int hash = 0, i;
	for (i = 0; name[i] != '\0'; i++) {
		hash += name[i];
	}
	return hash % SIZE;
}
hashdata *search(hashdata *hashmap[], char *name) {
	int hashIndex = hash(name);
	while (hashmap[hashIndex] != NULL) {
		if (strcmp(hashmap[hashIndex]->name, name)
				== 0&& hashmap[hashIndex]!=NULL) {
		return hashmap[hashIndex];
		}
		++hashIndex;
		hashIndex %= SIZE;
	}
	return NULL;

}
hashdata *put(hashdata *hashmap[], char *name, int data) {
	int hashIndex = hash(name);

	hashdata *item = (hashdata*) malloc(sizeof(hashdata));
	item->data = data;
	strcpy(item->name, name);
	item->key = hashIndex;

	while (hashmap[hashIndex] != NULL && hashmap[hashIndex]->key != -1) {
		if (strcmp(hashmap[hashIndex]->name, name) == 0) {
			hashmap[hashIndex]->data = data;
			hashmap[hashIndex]->key = hashIndex;
			return hashmap[hashIndex];
		}
		++hashIndex;
		if (hashIndex >= SIZE) {
			hashIndex %= SIZE;
		}
		}
	hashmap[hashIndex] = item;

	return hashmap[hashIndex];

	}


int get(hashdata *hashmap[], char *name) {
	int hashIndex = hash(name), counter = 0;
	while (hashmap[hashIndex] != NULL && counter < SIZE) {
		if (strcmp(hashmap[hashIndex]->name, name) == 0
				&& hashmap[hashIndex]->key != -1)
			return hashmap[hashIndex]->data;
		++hashIndex;
		hashIndex %= SIZE;
		counter++;

	}
	return -1;



}
int contains(hashdata *hashmap[], char *name) {

	hashdata *result = search(hashmap, name);

	if (result != NULL) {
		return 1;
	} else {
		return 0;
	}
	}

void display_hash(hashdata *hashmap[], int opt) {
	int i = 0;
	for (i = 0; i < SIZE; i++) {
		if (hashmap[i] != NULL) {
			printf("%s=%d\n", hashmap[i]->name, hashmap[i]->data);
		}
	}
	printf("\n");
	}
int remove_item(hashdata *hashmap[], char *name) {
	int hashIndex = hash(name), counter = 0;
	while (hashmap[hashIndex] != NULL && counter < SIZE) {
		if (strcmp(hashmap[hashIndex]->name, name) == 0
				&& hashmap[hashIndex]->key != -1) {
			return 1;
		}
		++hashIndex;
		counter++;
		hashIndex %= SIZE;
	}
	return 0;

}
int clear(hashdata *hashmap[]) {
	int i;
	for (i = 0; i < SIZE; i++) {
		hashmap[i]->data = 0;
		hashmap[i]->key = 0;
		strcpy(hashmap[i]->name, "\0");
	}
	return 0;
}
int size(hashdata *hashmap[]) {
	int hashIndex = 0;
	int counter = 0;
	int size = 0;
	while (counter < SIZE) {
		if (hashmap[hashIndex] != NULL && hashmap[hashIndex]->key != -10) {
			size++;

		}
		counter++;
		++hashIndex;
		hashIndex %= SIZE;

	}
	return SIZE;


}
