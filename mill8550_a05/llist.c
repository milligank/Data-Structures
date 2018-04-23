/*
-------------------------------------
File:    llist.h
Project: mill8550_a04
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-01-29
-------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

void data_import(node **startp, char *filename) {
	char line[40], name[20];
	FILE *fp = fopen(filename, "r");
	char *result = NULL;
	char delimiters[] = ",";
	float score = 0;

	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), fp) != NULL) {
		result = strtok(line, delimiters);
		strcpy(name, result);
		result = strtok(NULL, delimiters);
		score = atof(result);

		insert(startp, name, score);

	} /* while */

	fclose(fp);

} /* data_import */

void data_report(node *start, char *filename) {
	int count = 0;
	float mean = 0;
	float stddev = 0;

	float med = 0;
	int histogram[6] = { 0 }; //to hold the counts for histogram

	FILE *fp = fopen(filename, "w");
	fprintf(fp, "grade report\n");

	//traversal linked list to compute
	node *np = start;
	while (np != NULL) {
		count++;
		mean += np->score;
		stddev += np->score * np->score;

		//histogram data
		if (np->score >= 100)
			histogram[0]++;
		else if (np->score < 50)
			histogram[5]++;
		else
			histogram[(unsigned int) (99.99 - np->score) / 10]++;

		fprintf(fp, "%-15s%3.1f%4c\n", np->name, np->score,
				letter_grade(np->score));
		np = np->next;
	}
	mean /= count;
	stddev = sqrt(stddev / count - mean * mean);

	//compute median here
	med = median(start);

	fprintf(fp, "\nstatistics summary\n");
	fprintf(fp, "%-15s%d\n", "count", count);
	fprintf(fp, "%-15s%3.1f\n", "mean", mean);
	fprintf(fp, "%-15s%3.1f\n", "stddev", stddev);
	fprintf(fp, "%-15s%3.1f\n", "median", med);

	fprintf(fp, "histogram\n");
	//output histogram here

	fprintf(fp, "[100,90)      %d\n", histogram[0]);
	fprintf(fp, "(90,80)       %d\n", histogram[1]);
	fprintf(fp, "(80,70)       %d\n", histogram[2]);
	fprintf(fp, "(70,60)       %d\n", histogram[3]);
	fprintf(fp, "(60,50)       %d\n", histogram[4]);
	fprintf(fp, "(50,0]        %d\n", histogram[5]);

	fclose(fp);
}

char letter_grade(float s) {
	char r = 'F';
	if (s >= 85)
		r = 'A';
	else if (s >= 70)
		r = 'B';
	else if (s >= 60)
		r = 'C';
	else if (s >= 50)
		r = 'D';
	else
		r = 'F';
	return r;
}

void swap(float *first, float *second) {
	float temp;
	temp = *first;
	*first = *second;
	*second = temp;
}

void quick_sort(float *a, int m, int n) {
	float key;
	int i, j, k;

	if (m < n) {
		k = (m + n) / 2;
		swap(a + m, a + k);
		key = *(a + m);
		i = m + 1;
		j = n;
		while (i <= j) {
			while (i <= n && *(a + i) <= key)
				i++;
			while (j >= m && *(a + j) > key)
				j--;
			if (i < j)
				swap(a + i, a + j);
		}
		swap(a + m, a + j);
		quick_sort(a, m, j - 1);
		quick_sort(a, j + 1, n);
	}
}

float median(node *start) {

	int n = 0;
	float *a;
	int i = 0;
	node *counter = NULL;

	counter = start;

	if (start == NULL)
		return 0;

	while (counter != NULL) {
		n++;
		counter = counter->next;
	}

	counter = start; 	// reset counter to start of list

	a = malloc(n * sizeof(float));

	for (i = 0; i < n; i++) {
		*(a + i) = counter->score;
		printf("%3.2f\n", *(a + i));
		counter = counter->next;
	}

	quick_sort(a, 0, n);

	return (a[n / 2]);

}

void display(node *start) {

	printf("screen output: \n");

	while (start != NULL) {
		printf("%-15s%3.1f\n", start->name, start->score);
		start = start->next;
	}

}

node *search(node *start, char *name) {
	node *result = NULL;
	int done = 0;

	while ((start != NULL) || (done = 0)) {
		if (strcmp(name, start->name) == 0)
			result = start;
		done = 1;
		start = start->next;
	}

	return result;
}

void insert(node **start, char *name, float score) {

	node *new_node = NULL;

	while (*start != NULL) {
		start = &(*start)->next;
	}

	new_node = malloc(sizeof(node));

	strcpy(new_node->name, name);
	new_node->score = score;
	new_node->next = NULL;

	*start = new_node;

} /* insert */

void delete(node **start, char *name) {

	node *temp;
	node **current;
	for (current = start; *current != NULL; current = &(*current)->next) {
		if (strcmp((*current)->name, name) == 0) {
			temp = *current;
			*current = (*current)->next;
			free(temp);
			break;
		}
	}

}

void clean(node **start) {

	node *temp = *start;

	while (temp != NULL) {
		node *todelete = temp;
		temp = temp->next;
		free(todelete);
	}

	*start = NULL;
}

