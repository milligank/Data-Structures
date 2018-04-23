/*
-------------------------------------
File:    a4q1.c
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

#define MAX_WORD 40
#define MAX_LEN 500
#define MAX_WORDS 1000

struct word{
	char word[MAX_WORD];
	int count;
};

void trim(char *);
void lowerCase(char *);
int is_stopword(char *, char *);


int main(int argc, char *args[]) {
  const char delimiters[] = " .,;:!-\n\t\r"; // delimiters used to split words of a string
  int line_count = 0, word_count = 0, new_word_count = 0, j = 0;
  char stopwordstr[1000]; // char array to hold the string of stop words
  char line[MAX_LEN];     // char array to hold  
  struct word wordmap[MAX_WORDS]; 
  char infilename[40] = "textdata.txt"; //default input file name
  char outfilename[40] = "result.txt";  //default output file name
  char stopwordfilename[40] = "common-english-words.txt"; //default stop word file
  char *word_token; // word token pointer   
  FILE *fi, *fo;    // file pointers 
  int match = 0;
  
  //get i/o file names by command lines
  if (argc > 1) {  
	if (argc >= 2) strcpy(infilename, args[1]);
    if (argc >= 3) strcpy(outfilename, args[2]);
	if (argc >= 4) strcpy(stopwordfilename, args[3]);
  }  
 
  //load stopwords
  fi = fopen(stopwordfilename, "r");
  fgets(stopwordstr, sizeof(stopwordstr), fi);
  close(fi);

	//open input data file
	fi = fopen(infilename, "r");
	if (fi == NULL) {  // Cannot open the file.
		perror("error");
		return 0;
	} 
	
    // Process the file line by line. 
	while (fgets(line, MAX_LEN, fi) != NULL) {
		printf(line);
		// Increment the line count
		line_count++;

		//trim in case of need
		trim(line);

		// Convert each alphabetic character to lower case
		lowerCase(line);

		// Get the pointer to the first word word
		word_token = strtok(line, delimiters);

		while (word_token != NULL) {
			printf("%s\n", word_token);
			word_count++;
			if (!is_stopword(stopwordstr, word_token)){
				if (new_word_count ==0){
					strcpy(wordmap[new_word_count].word, word_token);
					wordmap[new_word_count].count++;
					new_word_count++;
				}else{
					int i;
					for(i=0; i<new_word_count; i++){
						if (strcmp(word_token, wordmap[i].word)== 0){
							wordmap[i].count++;
							match = 1;
						}
					}
					
					if (match == 0){
						strcpy(wordmap[new_word_count].word, word_token);
						wordmap[new_word_count].count++;
						new_word_count++;
					}
				}
			}
			
			word_token = strtok(NULL, delimiters);
							
		}
    }
    fclose(fi);
	
    // Write to the output file
    fo = fopen(outfilename, "w");
    fprintf(fo, "%-20s  %8d\n", "Line count", line_count);
    fprintf(fo, "%-20s  %8d\n", "Word count", word_count);
	fprintf(fo, "%-18s  %10s\n", "Non-stop-word", "frequency");
    for (j = 0; j < new_word_count; j++) {
      fprintf(fo, "%-20s  %8d\n", wordmap[j].word, wordmap[j].count);
    }
    fprintf(fo, "\n");
    fclose(fo);
 
  return 0;
}

void lowerCase(char *s) {
	if (s == NULL) return;
	while (*s) {
		if (*s >= 'A' && *s <= 'Z' ) *s += 32;
		s++;
	}
}

void trim(char *s) {
	if (s == NULL || *s == '\0') return;
	char *p=s, *dp=s;
	while (*p) {
	   if (*p != ' ' || (p > s && *(p-1) != ' '))
		  *dp++ = *p;
	   p++;
	}
	if (*(p-1) == ' ') *(dp-1) = '\0';
	else *dp = '\0';
}


int is_stopword(char *stopwordstr, char *word) {
	if (stopwordstr == NULL || word == NULL) return 0;
	if(strstr(stopwordstr, word)!= NULL){
		return 1;
	}
	return 0;
}
		

