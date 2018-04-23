/*
-------------------------------------
File:    a2q1.c
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
#include <time.h>

int* la;
int* ha;
int count;
int i;

int ifib(int n) {
	count++;
	if (&n < la) {
		la = &n;
	}
	
	int x;
	int f1 = 1;
	int f2 = 1;
	
	for (i = 2; i < n; i++){
		
		if ( i <= 0){
			x = i;
		}else{
			
			x = f1 + f2;
			f2 = f1;
			f1 = x;
		}
	}
	return x;
}

int rfib(int n) {
	count++;
	if (&n < la) {
		la = &n;
	}
	
	if (n <= 1){
		return n;
	}else{
		return rfib(n-1) + rfib(n-2);
	}
}

int main()
{
	int i=0, n = 40;

  //memory test for ifib(n)	
	printf("Iterative algorithm:\n");
	ha = &i;
	la = ha;
	count = 1;	
	printf("ifib(%d)=%d\n", n, ifib(n));
	printf("highest address: %lu\n", ha);
	printf("lowest address: %lu\n", la);
	int d = (unsigned long) ha - (unsigned long) la;
	printf("maximum stack height: %d\n",d);
	printf("number of function calls: %d\n", count);
	
   //memory test for rfib(n)
   printf("\nRecursive algorithm:\n");
	ha = &i;
	la = ha;
	count = 1;	
	printf("rfib(%d)=%d\n", n, rfib(n));
	printf("highest address: %lu\n", ha);
	printf("lowest address: %lu\n", la);
	d = (unsigned long) ha - (unsigned long) la;
	printf("maximum stack height: %d\n",d);
	printf("number of function calls: %d\n", count);
	
   
   //run time test for ifib(n)
	int m = 100000;
	clock_t t1, t2;
	t1=clock();
	for (i=0; i< m; i++) {
		ifib(n);
	}
	t2=clock();
	printf("\nifib(%d) takes %.0f milliseconds for %d times\n",  n, (double) t2-t1, m);
	
	//run time test for rfib(n)
	m = 10;
	t1 = clock();
	for (i=0; i < m; i++){
		rfib(n);
	}
	t2=clock();
	printf("\nrfib(%d) takes %.0f milliseconds for %d times\n",  n, (double) t2-t1, m);
	return 0;
}

