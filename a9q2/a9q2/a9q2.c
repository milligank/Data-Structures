/*
-------------------------------------
File:    a9q2.c
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
#include "stack.h"
#include "expeval.h"

int main(int argc, char* args[]) {
	char infilename[40] = "expression.txt";
	if (argc > 1)
		strcpy(infilename, args[1]);

	hashdata *hashmap[SIZE] = { 0 };

	char line[100];
	char delimiters[] = ";\n";
	char *st;

	FILE *fp = fopen(infilename, "r");
	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	while (fgets(line, sizeof(line), fp) != NULL) {
		trim_space(line);
		st = strtok(line, delimiters);
		while (st != NULL) {
			statement_process(hashmap, st);
			st = strtok(NULL, delimiters);
		}
	}
	fclose(fp);

	display_hash(hashmap, 0);
	return 0;
}
