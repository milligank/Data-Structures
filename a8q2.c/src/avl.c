/*
-------------------------------------
File:    avl.c
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

// A utility functions
int height(tnode *np) {
	if (np == NULL)
		return 0;
	return np->height;
}

//from a7q1.c
//modified from bst.c

tnode* new_node(char *name, float score) {
	tnode *np = (tnode*) malloc(sizeof(tnode));
	strcpy(np->name, name);
	np->score = score;
	np->height = 1;  // new node is initially added at leaf
	np->left = NULL;
	np->right = NULL;
	return np;
}

int get_height(tnode *root) {
	if (root == NULL) {
		return 0;
	} else {
		return root->height;
	}
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

tnode *rotate_right(tnode *y) {
	tnode *x = y->left;
	tnode *temp = x->right;

	x->right = y;
	y->left = temp;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

tnode *rotate_left(tnode *x) {
	tnode *y = x->right;
	tnode *temp = y->left;

	y->left = x;
	x->right = temp;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

void insert(tnode **rootp, char *name, float score) {
	// 1.  Perform the normal BST insertion
	if (*rootp == NULL) {
		*rootp = new_node(name, score);
		return;
	}
	tnode *root = *rootp;
	if (strcmp(name, root->name) < 0) {
		insert(&root->left, name, score);
	} else if (strcmp(name, root->name) > 0) {
		insert(&root->right, name, score);
	} else {
		return;
	}

	// 2. Update height of this ancestor node
	root->height = 1 + max(height(root->left), height(root->right));

	// 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
	int balance = balance_factor(root);

	// 4. If this node becomes unbalanced, then do rotation operation accordingly
	if (balance > 1) {
		if (balance_factor(root->left) >= 0) {
			*rootp = rotate_right(root);
		} else {
			root->left = rotate_left(root->left);
			*rootp = rotate_right(root);
		}
	} else if (balance < -1) {

		if (balance_factor(root->left) <= 0) {
			*rootp = rotate_left(root);
		} else {
			root->right = rotate_right(root->right);
			*rootp = rotate_left(root);
		}
	}
}

tnode *extract_smallest_node(tnode **rootp) {
	tnode *tnp = *rootp;
	tnode *parent = NULL;
	if (tnp == NULL) {
		return NULL;
	} else {
		while (tnp->left) {
			parent = tnp;
			tnp = tnp->left;
		}
		if (parent == NULL)
			*rootp = tnp->right;
		else
			parent->left = tnp->right;
		tnp->left = NULL;
		tnp->right = NULL;
		return tnp;
	}
}

tnode *search(tnode *root, char *name) {
	while (root != NULL) {
		if (strcmp(root->name, name) < 0) {
			return search(root->right, name);
		} else if (strcmp(root->name, name) > 0) {
			return search(root->left, name);
		} else {
			return root;
		}
	}
	return NULL;

}

void delete(tnode **rootp, char *name) {
	tnode *root = *rootp;
	tnode *np;

	// 1.  Perform the normal BST deletion
	if (root == NULL) {
		return;
	}
	if (strcmp(name, root->name) == 0) {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			*rootp = NULL;
		} else if (root->left != NULL && root->right == NULL) {
			np = root->left;
			free(root);
			*rootp = np;
		} else if (root->left == NULL && root->right != NULL) {
			np = root->right;
			free(root);
			*rootp = np;
		} else if (root->left != NULL && root->right != NULL) {
			np = extract_smallest_node(&root->right);
			np->left = root->left;
			np->right = root->right;
			free(root);
			*rootp = np;
		}
	} else {
		if (strcmp(name, root->name) < 0) {
			delete(&root->left, name);
		} else {
			delete(&root->right, name);
		}
	}

	// If the tree had only one node then return
	if (*rootp == NULL)
		return;

	root = *rootp;
	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + max(height(root->left), height(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
	// check whether this node became unbalanced)
	int balance = balance_factor(root);

	// If this node becomes unbalanced, then there are 4 cases
	if (balance > 1) {
		if (balance_factor(root->left) >= 0) {
			*rootp = rotate_right(root);
		} else {
			root->left = rotate_left(root->left);
			*rootp = rotate_right(root);
		}
	} else if (balance < -1) {
		if (balance_factor(root->left) <= 0) {
			*rootp = rotate_left(root);
		} else {
			root->right = rotate_right(root->right);
			*rootp = rotate_left(root);
		}
	}
}

void clean_tree(tnode **rootp) {
	if (*rootp) {
		tnode *np = *rootp;
		if (np->left)
			clean_tree(&np->left);
		if (np->right)
			clean_tree(&np->right);
		free(np);
	}
	*rootp = NULL;
	;
}

void merge_tree(tnode **rootp1, tnode *root2) {
	if (root2 == NULL) {
		return;
	} else {
		merge_tree(rootp1, root2->right);
		insert(rootp1, root2->name, root2->score);
		merge_tree(rootp1, root2->left);
	}

}

int balance_factor(tnode* np) {
	if (np == NULL) {
		return 0;
	} else {
		return (height(np->left) - height(np->right));

	}
}

void display_inorder(tnode *root) {
	if (root) {
		if (root->left)
			display_inorder(root->left);
		printf("%-22s%3.1f\n", root->name, root->score);
		if (root->right)
			display_inorder(root->right);
	}
}

void display_tree(tnode *root, int prelen) {
	if (root) {
		int i;
		for (i = 0; i < prelen; i++)
			printf("%c", ' ');
		printf("%s", "|___");
		printf("%s %3.1f \n", root->name, root->score);
		display_tree(root->left, prelen + 4);
		display_tree(root->right, prelen + 4);
	}
}
