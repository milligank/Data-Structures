/*
-------------------------------------
File:    a8q2.c
Project: a8q2.c
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-10
-------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "stats.h"

int main(int argc, char* args[]) {
	char infilename1[40] = "marks.txt_1";
	char infilename2[40] = "marks.txt_2";
	char outfilename[40] = "report.txt";
	if (argc > 1) {
		if (argc >= 2)
			strcpy(infilename1, args[1]);
		if (argc >= 3)
			strcpy(infilename2, args[2]);
		if (argc >= 4)
			strcpy(outfilename, args[3]);
	}

	//create and load dataset1
	statdata dataset1;
	dataset1.bst = NULL;
	dataset1.count = 0;
	dataset1.mean = 0;
	dataset1.stddev = 0;
	data_import(&dataset1, infilename1);
	display_inorder(dataset1.bst);
	display_stat(&dataset1);

	//create and load dataset2
	statdata dataset2;
	dataset2.bst = NULL;
	dataset2.count = 0;
	dataset2.mean = 0;
	dataset2.stddev = 0;
	data_import(&dataset2, infilename2);
	display_inorder(dataset2.bst);
	display_stat(&dataset2);

	//merge dataset2 to dataset1
	merge_data(&dataset1, &dataset2);

	//clean dataset2
	clean_data(&dataset2);

	display_inorder(dataset1.bst);
	display_inorder(dataset2.bst);
	display_stat(&dataset1);

	//output mark report and simple statistic summary
	//data_report(&dataset1, outfilename);
	data_report(&dataset1, outfilename);

	clean_data(&dataset1);

	return 0;
}
