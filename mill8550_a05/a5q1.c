#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define MAX_LENGTH 100

typedef struct node {
	char data;
	struct node *next;
	struct node *prev;
} node;

node *new_node(char data);
void insert(node **headp, node **tailp, node *new_np);
void display_forward(node *head);
void display_backward(node *tail);
void clean(node *head);

int main(int argc, char* args[]) {
	char *s = "123456", *p;
	if (argc > 1) s = args[1];

	printf("Static method:\n");
	//declare double linked list header and tail pointers
	node *shead=NULL, *stail=NULL;	
	node nodearray[MAX_LENGTH];
	int i = 0;
	p = s;
	while (*p) {
		nodearray[i].data = *p;
		nodearray[i].prev = NULL;
		nodearray[i].next = NULL;
		insert(&shead, &stail, &nodearray[i]);
		p++;
		i++;
	}
	display_forward(shead);
	printf("\n");
	display_backward(stail);
	printf("\n");
	
	//use dynamically allocated memory to hold nodes of linked list
	printf("Dynamic method:\n");
	node *dhead=NULL, *dtail=NULL;
	p = s;
	node *new_np = NULL;
	while (*p) {
	    new_np = new_node(*p);
		insert(&dhead, &dtail, new_np);
		p++;
	}
	display_forward(dhead);
	printf("\n");
	display_backward(dtail);
	clean(dhead); //needed to free dynamically allocated memory
	
	return 0;
}

node *new_node(char data) {
	node *p = NULL;
	p = malloc(sizeof(struct node));
	p-> data = data;
	p->next = NULL;
	p->prev = NULL;
	return p;
}

void insert(node **headp, node **tailp, node *new_np) {
	
	if (*headp == NULL){
		new_np -> prev = new_np -> prev;
		*headp = *tailp = new_np;
	}else{
		new_np->prev = *tailp;
		(*tailp)->next = new_np;
		new_np-> next = NULL;
		(*tailp) = new_np;
	}
	
}

void display_forward(node *head) {
	while (head) {
		printf("%c,", head->data);
		head = head->next;
	}
}

void display_backward(node *tail) {
	while (tail){
		printf("%c,", tail->data);
		tail = tail->prev;
	}
		
}

void clean(node *head) {
	node* temp;

	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}