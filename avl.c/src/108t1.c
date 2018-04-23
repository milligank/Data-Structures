/*
-------------------------------------
File:    108t1.c
Project: avl.c
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-03-05
-------------------------------------
 */

#include "avl.h"

int main() {
	struct Node *root = NULL;

	/* Constructing tree given in the above figure */
	/*root = insert(root, 9);
	root = insert(root, 5);
	root = insert(root, 10);
	root = insert(root, 0);
	root = insert(root, 6);
	root = insert(root, 11);
	root = insert(root, -1);
	root = insert(root, 1);
	 root = insert(root, 2);*/

	root = insert(root, 1);
	print_tree(root, 0);
	root = insert(root, 2);
	print_tree(root, 0);
	root = insert(root, 3);
	print_tree(root, 0);
	root = insert(root, 4);
	print_tree(root, 0);
	root = insert(root, 5);
	print_tree(root, 0);
	root = insert(root, 6);
	print_tree(root, 0);
	root = insert(root, 7);
	print_tree(root, 0);
	root = insert(root, 8);
	print_tree(root, 0);
	root = insert(root, 9);
	print_tree(root, 0);
	root = insert(root, 10);
	print_tree(root, 0);
	root = insert(root, 11);
	print_tree(root, 0);
	root = insert(root, 12);
	print_tree(root, 0);
	root = insert(root, 13);
	print_tree(root, 0);
	root = insert(root, 14);
	print_tree(root, 0);
	root = insert(root, 15);
	print_tree(root, 0);

	/* The constructed AVL Tree would be
	 9
	 /  \
          1    10
	 /  \     \
       0    5     11
	 /    /  \
     -1   2    6
	 */

	printf("Preorder traversal of the constructed AVL "
			"tree is \n");
	preOrder(root);

	root = deleteNode(root, 10);

	/* The AVL Tree after deletion of 10
	 1
	 /  \
          0    9
	 /     /  \
       -1    5     11
	 /  \
          2    6
	 */

	printf("\nPreorder traversal after deletion of 10 \n");
	preOrder(root);

	printf("\nIs balanced check (1 = true, 0= false) \n");
	int i = is_balanced(root);
	printf("%d", i);

	return 0;
}
