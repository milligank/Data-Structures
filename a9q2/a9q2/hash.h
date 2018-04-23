/*
-------------------------------------
File:    hash.h
Project: cp264_a9_mill8550
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-21
-------------------------------------
 */


#ifndef HASH_H_
#define HASH_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20

typedef struct hashdata {
	int key;
	char name[10];
	int data;
} hashdata;

int hash(char *);
hashdata *search(hashdata *hashmap[], char *name);
hashdata *put(hashdata *hashmap[], char *name, int data);
int get(hashdata *hashmap[], char *name);
int contains(hashdata *hashmap[], char *name);
void display_hash(hashdata *hashmap[], int opt);

int remove_item(hashdata *hashmap[], char *name);
int clear(hashdata *hashmap[]);
int size(hashdata *hashmap[]);


#endif /* HASH_H_ */
