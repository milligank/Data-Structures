/*
 -------------------------------------
 File:    stats.c
 Project: a8q2.c
 file description
 -------------------------------------
 Author:  Kathleen Milligan
 ID:      160458550
 Email:   mill8550@mylaurier.ca
 Version  2018-03-09
 -------------------------------------
 */
#include "stats.h"
#include "avl.h"

void add_data(statdata *sd, char *name, float score) {
// your implementation
// 1. search
	tnode *np;
	np = search(sd->bst, name);
// 2. insert to the bst
	if (np == NULL) {
		insert(&sd->bst, name, score);
		sd->count += 1;
// 3. use the score to update the statistic summary	without going through all data records
		float prevMean = sd->mean;

		float total = sd->mean * (sd->count - 1);
		total = total + score;
		sd->mean = total / sd->count;

		float stde = sd->stddev;
		stde = stde * stde;
		stde = stde + (prevMean * prevMean);
		stde = stde * (sd->count - 1);

		stde += score * score;
		sd->stddev = sqrt(stde / sd->count - (sd->mean * sd->mean));
	}

}

void merge_data(statdata *ds1, statdata *ds2) {
	//first do merge tree
	merge_tree(&ds1->bst, ds2->bst);
	//ds1->count += ds2->count;
	int count1 = ds1->count;
	int count2 = ds2->count;
	float mean1 = ds1->mean;
	float mean2 = ds2->mean;
	ds1->count = count1 + count2;
	ds1->mean = (mean1 * count1 + mean2 * count2) / (count1 + count2);

	ds1->stddev = sqrt(
			((ds1->stddev * ds1->stddev + mean1 * mean1) * count1
					+ (ds2->stddev * ds2->stddev + mean2 * mean2) * count2)
					/ (count1 + count2) - ds1->mean * ds1->mean);
}

void clean_data(statdata *ds) {

	clean_tree(&ds->bst);

	ds->count = 0;
	ds->mean = 0;
	ds->stddev = 0;
}

void remove_data(statdata *sd, char *name) {
// your implementation
// 1. search
	tnode *np;
	np = search(sd->bst, name);
	float score;
// 2. if found, get the score
	if (np != NULL) {
		score = np->score;
// 3. delete the node
		delete(&sd->bst, name);
		sd->count -= 1;
// 4. use the score to update the statistic summary	without going through all data records
		float prevMean = sd->mean;

		float total = sd->mean * (sd->count + 1);
		total = total - score;
		sd->mean = total / sd->count;

		float stde = sd->stddev;
		stde = stde * stde;
		stde = stde + (prevMean * prevMean);
		stde = stde * (sd->count + 1);

		stde -= score * score;
		sd->stddev = sqrt(stde / sd->count - (sd->mean * sd->mean));
	}
}

void display_stat(statdata *sd) {
	printf("\nstatistics summary\n");
	printf("%-15s%d\n", "count", sd->count);
	printf("%-15s%3.1f\n", "mean", sd->mean);
	printf("%-15s%3.1f\n", "stddev", sd->stddev);
}

void data_report(statdata *sd, char *filename) {
	FILE *fp = fopen(filename, "w");
	fprintf(fp, "grade report\n");
	print_to_file(sd->bst, fp);
	fprintf(fp, "\nstatistics summary\n");
	fprintf(fp, "%-15s%d\n", "count", sd->count);
	fprintf(fp, "%-15s%3.1f\n", "mean", sd->mean);
	fprintf(fp, "%-15s%3.1f\n", "stddev", sd->stddev);
	fclose(fp);
}

//modified from a5q2
void data_import(statdata *ds, char *filename) {
	char line[40], name[20];
	FILE *fp = fopen(filename, "r");
	char *result = NULL;
	char delimiters[] = ",";
	float score = 0;
	int count = 0;
	float mean = 0, stddev = 0;

	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), fp) != NULL) {
		result = strtok(line, delimiters);
		strcpy(name, result);
		result = strtok(NULL, delimiters);
		score = atof(result);
		count++;
		mean += score;
		stddev += score * score;
		insert(&ds->bst, name, score);
	}

	ds->count = count;
	mean /= count;
	ds->mean = mean;
	ds->stddev = sqrt(stddev / count - mean * mean);
	fclose(fp);
}

//auxiliary function used
void print_to_file(tnode *root, FILE *fp) {
	if (root) {
		if (root->left)
			print_to_file(root->left, fp);
		fprintf(fp, "%-15s%3.1f%4c\n", root->name, root->score,
				letter_grade(root->score));
		if (root->right)
			print_to_file(root->right, fp);
	}
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
