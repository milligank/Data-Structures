/*
 -------------------------------------
 File:    a8q1.c
 Project: a8q1.c
 file description
 -------------------------------------
 Author:  Kathleen Milligan
 ID:      160458550
 Email:   mill8550@mylaurier.ca
 Version  2018-03-09
 -------------------------------------
 */

#include "avl.h"

int main(int argc, char* args[]) {
	int n = 8;
	if (argc > 1) {
		n = atoi(args[1]);
	}
//
	tnode *root = NULL, *np;

	int i;
	char name[20];
	for (i = 0; i < n; i++) {
		itoa(i, name, 10);  //itoa(int value, char *string, int radix)
		insert(&root, name, i + 0.0);
	}

	display_tree(root, 0);
	display_inorder(root);
	printf("\n");
	for (i = 0; i < n; i++) {
		if (i % 2 == 0) {
			itoa(i, name, 10);
			delete(&root, name);
		}
	}

	display_tree(root, 0);
	display_inorder(root);
	printf("\n");
	for (i = 0; i < n; i++) {
		itoa(i, name, 10);
		np = search(root, name);
		if (np == NULL)
			printf("not found %d\n", i);
		else
			printf("found %s, score %3.1f\n", np->name, np->score);
	}

	clean_tree(&root);
	return 0;
}
