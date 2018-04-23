/*
-------------------------------------
File:    a3q1.c
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

void magic_saquare(int *m, int n);
void display(int *, int);
int sum(int*, int);
void transpose(int *, int *, int);
void multiply(int *, int *, int *, int);


int main() {
	int n = 3;
	
	int m1[n][n];
	int m2[n][n];
	int m3[n][n];
	
	int *p1 = &m1[0][0];
	magic_saquare(p1, n);
	printf("\nM1=");
	display(p1, n);
	printf("\nsum(M1)=%d\n", sum(p1, n));	

	int *p2 = &m2[0][0];	
	transpose(p1, p2, n);
	printf("\nM1'=");
	display(p2, n);
	
	int *p3 = &m3[0][0];
	multiply(p1, p2, p3, n);	
	printf("\nM1*M1'=");
	display(p3, n);
	
	return 0;
}


void magic_saquare(int *m, int n) {
	int j;
	int val[9] = {8,1,6,3,5,7,4,9,2};
		for(j=0; j<9; j++){
			*(m + j) = val[j];
		}
}

int sum(int *m, int n) {
	int sum = 0;
	int i;
	for (i=0; i<9; i++){
		sum += *(m + i);
	}
	return sum;
}


void transpose(int *m1, int *m2, int n) {
   int i,j;
   for (i =0; i<n; i++){
		for(j=0; j<n; j++){
			*(m2 + i * n +j) = *(m1 + i + j*n);
		}
	}
}


void display(int *m, int n) {
	int j;
	int count = 1;
	
	for(j=0; j<9; j++){
		if (count == 3){
			printf("%d \n", *(m + j));
			count = 1;
		}
		else{
			printf("%d ", *(m + j));
			count +=1; 
		
		}	
		
	}

}


void multiply(int *m1, int *m2, int *m3, int n) {
	
    int i, j, k;
	
	for (i=0; i<n; i++){
		for (j=0; j<n; j++){
			*(m3 +i*n +j) =0;
			for (k=0; k<n; k++){
				*(m3 +i*n +j) = *(m3 + i*n +j) + *(m1 + i*n +k) * *(m2+ k*n +j);
			}
		}
	}
}

