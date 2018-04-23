


#include <stdio.h>
#include <stdlib.h>

//double linked list
typedef struct node {
	char data;  // to store one digit as its number, or code of operator
	struct node *next;
	struct node *prev;
} node;

node *new_node(int data);
void insert_beg(node **headp, node **tailp, node *np);
void insert_end(node **headp, node **tailp, node *np);
void display_forward(node *head);
void display_backward(node *tail);
void clean(node **headp, node **tailp);

//structure to represent big number
typedef struct bigint {
	node *head;
	node *tail;
} BigInt;

//functions for big number
void bigint_print(BigInt bignumber);
void bigint_clean(BigInt *bignumberp);
BigInt sum(BigInt oprand1, BigInt oprand2);
/*
-------------------------------------
File:    a6q1.c
Project: mill8550_a04
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-01-29
-------------------------------------
 */

BigInt Fibonacci(int n);

int main(int argc, char* args[]) {		 
	//default input or from command line arguments
	char str[] = "11111111111111111111+88888888888888888889";	
	char *p = str;	
	int n = 100;
    if (argc > 1) p = args[1];
	if (argc > 2 ) n = atoi(args[2]); 
		
	//BigInt variables for operands and results	
	BigInt op1={0}, op2={0}, result={0};

	//parse expression to retrieve operands and operator
	char operator = ' ';
    int readstate = 1;
	while (*p != '\0') {
		if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
			operator = *p;
			readstate = 2;
		} else if (readstate == 1 && *p >= '0' && *p <= '9' ){
			insert_end(&op1.head, &op1.tail, new_node(*p -'0'));
		} else if (readstate == 2 && *p >= '0' && *p <= '9' ){
			insert_end(&op2.head, &op2.tail, new_node(*p-'0'));
		} else {
			printf("Invalid input");
			return 0;
		}
		p++;
	}

	//do big number computing according operator, we only do + operation
	if (operator != '+') {
	   printf("Invalid operator");
	} else {
		bigint_print(op1);
		printf("%c", operator);
		bigint_print(op2);
		printf("=", operator);
		result = sum(op1, op2);
		bigint_print(result);
	}
	
	//clean double linked lists of operands and result
	bigint_clean(&result);
	bigint_clean(&op1);
	bigint_clean(&op2);

	//compute nth Fibonacci number
	printf("\nFibonacci(%d)=", n);
	result = Fibonacci(n);
	bigint_print(result);
    bigint_clean(&result);	
	
	return 0;
}

//updated from a5q1
node *new_node(int data) {
	node* np = (node *) malloc(sizeof(node));
	np->data = data;
	np->prev = NULL;
	np->next = NULL;
	return np;
}

void insert_beg(node **headp, node **tailp, node *newnode) {
	if (*headp == NULL && *tailp == NULL) {
		*headp = newnode;
		*tailp = newnode;
	} else {
		node* np = *headp;
		np->prev = newnode;
		*headp = newnode;
		newnode->next = np;
	}
}

//updated from a5q1
void insert_end(node **headp, node **tailp, node *newnode) {
	if (*headp == NULL && *tailp == NULL) {
		*headp = newnode;
		*tailp = newnode;
	} else {
		node* np = *tailp;
		np->next = newnode;
		newnode->prev = np;
		*tailp = newnode;
	}
}

void display_forward(node *head) {
	while ( head != NULL) {
		printf("%d", head->data);
		head = head->next;
	}
}

//updated from a5q1
void clean(node **headp, node **tailp) {
	node *temp, *np = *headp;
	while (np != NULL)  {
		temp = np;
		np = np->next;
		free(temp);
	}
	*headp = NULL;
	*tailp = NULL;
}

void bigint_print(BigInt bignumber) {
	display_forward(bignumber.head);
}

void bigint_clean(BigInt *bignumberp) {
	clean(&bignumberp->head, &bignumberp->tail);
}

BigInt sum(BigInt opa1, BigInt opa2) {
	BigInt result = {0};
	node *p1 = opa1.tail;
	node *p2 = opa2.tail;	
	int a=0, b=0, s = 0, c = 0;
	
	while(p1 || p2){
		a = 0; b =0;
		if(p1){
			a= p1->data;
			p1 = p1->prev;
		} if(p2){
			b = p2->data;
			p2 = p2->prev;
		}
		s = a + b + c;
		//... 
		if(s >= 10){
			s -= 10; 
			c = 1;
			
		}else{
			c = 0;
		}
		insert_beg(&result.head, &result.tail, new_node(s));
	}
	if(c ==1){
		insert_beg(&result.head, &result.tail, new_node(c));
	}
	return result;
}

BigInt Fibonacci(int n) {
	BigInt result = {0};
    BigInt f1 = {0};
	BigInt f2 = {0};
	BigInt temp = {0};
	
	insert_beg(&f1.head, &f1.tail, new_node(1));
	insert_beg(&f2.head, &f2.tail, new_node(1));	
	
	if (n <= 2 ) {
		result.head = f2.head;
		result.tail = f2.tail; 
		bigint_clean(&f1);
		
	} else {
		int i = 0;
		for (i=1 ; i<n/2 ; i++){
			temp = sum(f1,f2);
			
			bigint_clean(&f1);
			f1 = sum(f2,temp);
			
			bigint_clean(&f2);
			f2 = f1;
			f1 = temp;
		}
		if(n%2 == 1){
			
			result = sum(f1,f2);
			bigint_clean(&f1);
			bigint_clean(&f2);
		}else if(n % 2 ==0){
			result = f2; 
			bigint_clean(&temp);
		}		
	}
	return result;
}
