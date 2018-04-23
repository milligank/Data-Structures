/*
-------------------------------------
File:    a7q2.c
Project: cp264_a7_mill8550
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-03
-------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "stats.h"

int main(int argc, char* args[]) {
	char infilename[40] = "marks.txt";
	char outfilename[40] = "report.txt";
	if (argc > 1) {
		if (argc >= 2)
			strcpy(infilename, args[1]);
		if (argc >= 3)
			strcpy(outfilename, args[2]);
	}

	//create and initiate stats and bst data structure
	statdata dataset;
	dataset.bst = NULL;
	dataset.count = 0;
	dataset.mean = 0;
	dataset.stddev = 0;

	//import mark records into bst data structure and
	data_import(&dataset, infilename);
	display(dataset.bst);
	display_stat(&dataset);

	//add, search, and remove operations
	add_data(&dataset, "Moore", 92.0);
	add_data(&dataset, "Fan", 88.0);
	add_data(&dataset, "Lu", 85.0);

	tnode *tp = search(dataset.bst, "Moore");
	if (tp == NULL)
		printf("\nNot Fount\n");
	else
		printf("\nFound: (%s, %3.1f)\n", tp->name, tp->score);

	tp = search(dataset.bst, "Ellis");
	if (tp == NULL)
		printf("\nNot Found\n");
	else
		printf("\nFound: (%s, %3.1f)\n", tp->name, tp->score);

	remove_data(&dataset, "Wang");
	remove_data(&dataset, "Chabot");

	//output mark report and simple statistic summary
	data_report(&dataset, outfilename);

	//clean bst data structure
	clean(dataset.bst);

	return 0;
}



