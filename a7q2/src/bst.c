/*
 -------------------------------------
 File:    bst.c
 Project: cp264_a7_mill8550
 file description
 -------------------------------------
 Author:  Kathleen Milligan
 ID:      160458550
 Email:   mill8550
 Version  2018-03-03
 -------------------------------------
 */

#include "bst.h"

void display(tnode *root) {
	if (root) {
		if (root->left)
			display(root->left);
		printf("%s\t%6.1f\n", root->name, root->score);
		if (root->right)
			display(root->right);
	}
}

void insert(tnode **treepp, char *name, float score) {
	tnode *np = (tnode*) malloc(sizeof(tnode));
	strcpy(np->name, name);
	np->score = score;
	np->left = NULL;
	np->right = NULL;

	if (*treepp == NULL) {
		*treepp = np;
	} else {
		if (strcmp(name, (*treepp)->name) < 0) {
			insert(&(*treepp)->left, name, score);
		} else {
			insert(&(*treepp)->right, name, score);
		}
	}
}

void delete(tnode **treepp, char *name) {
	tnode *root = *treepp;
	tnode *tnp;

	if (root == NULL) {
		return;
	} else if (strcmp(name, root->name) == 0) {

		if (root->left == NULL && root->right == NULL) {
			free(root);
			*treepp = NULL;
		} else if (root->left != NULL && root->right == NULL) {
			tnp = root->left;
			free(root);
			*treepp = tnp;
		} else if (root->left == NULL && root != NULL) {
			tnp = root->right;
			free(root);
			*treepp = tnp;
		} else if (root->left != NULL && root->right != NULL) {
			tnp = get_smallest_element(root->right);
			tnp->left = root->left;
			tnp->right = root->right;
			*treepp = tnp;
			free(root);
		}
	} else {

		if (strcmp(name, root->name) < 0) {
			delete(&root->left, name);
		} else {
			delete(&root->right, name);
		}
	}
}

tnode* search(tnode *root, char *name) {
	while (root) {
		if (strcmp(name, root->name) == 0) {
			return root;
		} else if (strcmp(name, root->name) < 0) {
			root = root->left;
		} else {
			root = root->right;
		}
	}
	return NULL;
}

void clean(tnode *root) {
	tnode *rootp = root;
	if (rootp) {
		if (root->left) {
			clean(root->left);
		}
		if (root->right) {
			clean(root->right);
		}
		free(root);
	}
	rootp = NULL;
}

//this is auxiliary function used in delete
tnode *get_smallest_element(tnode *root) {
	if (root == NULL) {
		return root;
	}
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}
