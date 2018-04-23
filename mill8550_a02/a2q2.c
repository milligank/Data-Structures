/*
-------------------------------------
File:    a2q2.c
Project: mill8550_a01
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-01-11
-------------------------------------
 */



#include<stdio.h>
 


int main(int argc, char* args[])
{	

	if (argc <= 3) {
		printf("need more than two integer arguments: 2 1 2 3 4\n");
		return 0;
	}
	
	int i, x = atoi(args[1]), n = argc-2;
	int a[n];
    for (i=0;i<n;i++) {
	   a[i] = atoi(args[i+2]);
	}
	for (i =0; i <n; i++){
		if (n-1 == i){	
		printf("%d*%d^%d", a[i],x, (n-1-i));
		}else{
			printf("%d*%d^%d + ", a[i],x, (n-1-i));
		}
	}
	printf("= %d", horner(x, n, a));
			
		
	return 0;
}

int horner(int x, int n, int a[])
{
	int ans = a[0];
    int i = 0;
    while(i < x)
    {
        ans = ans*n + a[i+1];
        i++;
    }
    return ans;
}