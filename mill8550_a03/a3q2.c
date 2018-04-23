/*
-------------------------------------
File:    a3q2.c
Project: mill8550_a01
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-01-11
-------------------------------------
 */



#include <stdio.h>
#include <ctype.h>

int strLength(char *);
int wordCount(char *);
void lowerCase(char *);
void trim(char *);

int main(int argc, char* args[]) {
	setbuf(stdout, NULL);
	char str[100] = "     This Is    a Test   ";
	
	printf("\nWord count:%d", wordCount(str));
	printf("\nBefore trimming:\"%s\"", str);
	printf("\nlength:%d", strLength(str));
	trim(str);
	lowerCase(str);
	printf("\nAfter trimming:\"%s\"", str);
	printf("\nlength:%d", strLength(str));
	return 0;
}


int strLength(char *s) {
	int str=0;
    while(*s!='\0')
    {
        str++;
        *s++;
    }
    return(str);
}


int wordCount(char *s) {
    char prev = ' ';
    int n = 0;

    while(*s){
        if(isspace(prev) && !isspace(*s)){
            ++n;
        }
        prev = *s++;
    }
    return n;
}


void lowerCase(char *s) {
    while( *s ) {
    *s = tolower(*s);
    s++;
    }
}


void trim(char *s) {

	int i,j;
    for(i=j=0; s[i]; ++i)
    {
        if(!isspace(s[i]) || (i>0 && !isspace(s[i-1])))
        {
            s[j++] = s[i];
        }
    }
    if (s[i] == '\0' && s[i-1] == ' ')
    {
        s[j-1] = '\0';
    }
    else
    {
        s[j] = '\0';
    }
	
	

 
}

