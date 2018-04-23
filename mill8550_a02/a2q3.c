/*
-------------------------------------
File:    a2q3.c
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

void array_print(int *, int);
void array_copy(int *, int*, int);
void selection_sort(int *, int);
void quick_sort(int *, int, int);
void swap(int *, int *);

int main(int argc, char *args[]){
	int n = argc - 1; // number of elements in array to sort
	int a[n];         // to hold array of integers 
	int b[n];         // to hold array for sorting, copy a to b
	int i = 0;

	//get array data from command line arguments
	for (i = 0; i < n; i++) {
		a[i] = atoi(args[i + 1]);
	}
	
	printf("Array:");
	print_array(a, n);
	printf("\n"); 

	array_copy(a, b, n);
	printf("Selection Sort result:");
	selection_sort(b, n);
	print_array(b, n);
	printf("\n");
	

	array_copy(a, b, n);
	printf("Quicksort result:");
	quick_sort(b, 0, n);
	print_array(b, n);
	printf("\n"); 

	return 0;
}

void print_array(int *a, int n){
  int j = 0;  
  for (j=0; j<n; ++j){
    if (j%10 == 0) printf("\n");
    printf("%d ", *(a+j));
  } 
}

void array_copy(int *a, int *b, int n){
	int i;
	for (i=0; i<n; i++){
		*(b + i) = *(a + i);
	}
}

void selection_sort(int *list, int n){
	int i,j,temp;
	for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
        {
            if(*(list+i)>*(list+j))
            {
                temp=*(list+j);
                *(list+j)=*(list+i);
                *(list+i)=temp;
	
            }
        }
    }

void quick_sort(int *list, int m, int n){ 

   int temp;
   int i;
   int j;
   int k;
	if (m < n){
		k = (m+n) / 2;
		swap(list+m, list+k);
		temp = *(list+m);
		i = m+1;
		j = n;
		while(i <= j){
			while(i <= n && *(list+i) <= temp)
				i++;
			while(j >= m && *(list+j) > temp)
				j--;
			if(i < j)
				swap(list+i,list+j);
		}
		swap(list+m, list+j);
		quick_sort(list,m,j-1);
		quick_sort(list,j+1,n);
	}
}

void swap(int *first, int *second )
{
  int temp;
  temp = *first;
  *first = *second;
  *second = temp;
}
