/*
-------------------------------------
File:    a5q2.c
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
#include "llist.h"

int main(int argc, char* args[]) {
	char infilename[40] = "marks.txt";
	char outfilename[40] = "report.txt";
	if (argc > 1) {
		if (argc >= 2) strcpy(infilename, args[1]);
		if (argc >= 3) strcpy(outfilename, args[2]);
	}  

	/*
	* declare link list start pointer
	*/
	node *start = NULL;
	data_import(&start, infilename);
	display(start);

	insert(&start, "Moore", 92.0);
	node *p = search(start, "Moore");
	if (p == NULL)
	    printf("Not Fount\n");
	else
		printf("Found:%s, %5.2f\n", p->name, p->score);
	delete(&start, "Wang");
	data_report(start, outfilename);
	clean(&start);
	return 0;
}




