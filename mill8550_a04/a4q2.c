/*
-------------------------------------
File:    a4q2.c
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
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_REC 100
#define MAX_LINE 100

typedef struct  {
	char name[MAX_REC];
	float score;
	
} RECORD;

char letter_grade(float);
int data_import(RECORD dataset[], char *);
int data_report(RECORD dataset[], int, char *);


int main(int argc, char *args[]) {
	RECORD dataset[MAX_REC];
	int record_count = 0;
	FILE *fi, *fo;

	char infilename[40] = "marks.txt";    //default input file name
	char outfilename[40]= "report.txt";   //default output file name

	if (argc > 1) {
		if (argc >= 2) strcpy(infilename, args[1]);
		if (argc >= 3) strcpy(outfilename,args[2]);
	}  

	record_count = data_import(dataset, infilename); 

    if (record_count >=1) 
		data_report(dataset, record_count, outfilename);
	else 
		printf("no data is found");

	return 0;
}

char letter_grade(float score){
	if (score >= 85){
		return 'A';
	}else if (score >= 70){
		return 'B';
	}else if (score >= 60){
		return 'C';
	}else if (score >= 50){
		return 'D';
	}else{
		return 'F';
	}
}


int data_import(RECORD dataset[], char *filename) { 
	char line[MAX_LINE];
	char delimiters[] = ",";
	int i = 0;
	char mark[10];
	FILE *fi, *fo;

	char infilename[40] = "marks.txt";    //default input file name
	char outfilename[40]= "report.txt";   //default output file name

	fi = fopen(infilename, "r");
	if (fi == NULL) {  // Cannot open the file.
		perror("error");
		return 0;
	} 
	
	while (fgets(line, MAX_LINE, fi) != NULL) {
		strcpy(dataset[i].name, strtok(line, delimiters));
		strcpy(mark, strtok(NULL,delimiters));
		dataset[i].score = atof(mark);
		i++;
		
	}
	close(fi);


return i;
}


int data_report(RECORD dataset[], int n, char *filename) {
	FILE *fi, *fo;
	char infilename[40] = "marks.txt";    //default input file name
	char outfilename[40]= "report.txt";   //default output file name
	float mean=0, sdev=0, total=0, var=0, diff=0;
	int i;
	
	for (i =0; i<n; i++){
		total = total + dataset[i].score;
	}
	mean = total/n;
	
	for(i=0; i<n; i++){
		diff = dataset[i].score - mean;
		var = var + pow(diff, 2);
	}
	sdev = sqrt(var/n);
	
	fo = fopen(outfilename, "w");
	fprintf(fo,"letter grade\n");
	
	for(i=0; i<n; i++){
		fprintf(fo, "%-15s%c\n", dataset[i].name, letter_grade(dataset[i].score));
	}
	fprintf(fo, "\n");
	
	fprintf(fo, "summary\n");
	
	fprintf(fo, "%-20s%.d\n", "record count:", n); 
	fprintf(fo,"%-20s%3.1f\n", "average:", mean); 
	fprintf(fo,"%-20s%3.1f\n", "standard deviation:", sdev); 
return 0;
}