/*
 -------------------------------------
 File:    a7q1.c
 Project: cp264_a7_mill8550
 file description
 -------------------------------------
 Author:  Kathleen Milligan
 ID:      160458550
 Email:   mill8550
 Version  2018-03-03
 -------------------------------------
 */

#include<stdio.h>
#include<stdlib.h>


//general binary tree with operations by recursion
typedef struct tree_node {
	int data;
	char visited; //used by general dfs algorithm
	struct tree_node *left;
	struct tree_node *right;
} tnode;

tnode *new_node(int);
void clean_tree(tnode*);
void display_preorder(tnode *);
void display_inorder(tnode *);
void display_postorder(tnode *);
int get_node_count(tnode*);
int get_height(tnode*);

//stack for depth-first by iteration
typedef struct stack_node {
	tnode *tnp;
	struct stack_node *next;
} snode;
void push(snode **, tnode*);
tnode *pop(snode **);
void clean_stack(snode **);
/*
 * display binary tree using stack and iteration, not use visited field
 * @param opt, opt==0 for pre-order; opt==1 for pre-order; opt==2 for in-order;
 */
void display_df_iteration(tnode*, int opt);
/*
 * general depth-first-search using stack and iteration and visited field
 */
tnode *dfs_iteration(tnode *, int);

//queue for breadth-first by iteration
typedef struct queue_node {
	tnode *tnp;
	struct queue_node *next;
} qnode;
void enqueue(qnode **, qnode **, tnode*);
tnode *dequeue(qnode **, qnode **);
void clean_queue(qnode **, qnode **);
/*
 * display in breadth-first-order using queue and iteration
 */
void display_bfs_iteration(tnode*);
/*
 * general breadth-first-search using queue and iteration
 */
tnode *bfs_iteration(tnode*, int val);

//main test driver program
int main() {
	tnode *a = new_node('A');
	tnode *b = new_node('B');
	tnode *c = new_node('C');
	tnode *d = new_node('D');
	tnode *e = new_node('E');
	tnode *f = new_node('F');
	tnode *g = new_node('G');

	a->left = b;
	a->right = c;
	b->left = d;
	b->right = e;
	c->left = f;
	c->right = g;

	tnode *root = a;

	printf("\n%-22s%d", "node count:", get_node_count(root));
	printf("\n%-22s%d", "tree height:", get_height(root));

	printf("\n%-22s", "pre-order-recursion:");
	display_preorder(root);

	printf("\n%-22s", "pre-order-iteration:");
	display_df_iteration(root, 0);

	printf("\n%-22s", "post-order-recursion:");
	display_postorder(root);
	printf("\n%-22s", "post-order-iteration:");
	display_df_iteration(root, 1);

	printf("\n%-22s", "in-order-recursion: ");
	display_inorder(root);
	printf("\n%-22s", "in-order-iteration: ");
	display_df_iteration(root, 2);

	printf("\n%-22s", "bf-order-iteration: ");
	display_bfs_iteration(root);
	printf("\n%-22s%c", "bfs-iteration:", 'G');
	tnode *tnp = bfs_iteration(root, 'G');
	if (tnp)
		printf("\n%-22s%c", "Found:", tnp->data);

	printf("\n%-22s%c", "dfs-iteration:", 'F');
	tnp = dfs_iteration(root, 'F');
	if (tnp)
		printf("\n%-22s%c", "Found:", tnp->data);
	printf("\n");
	clean_tree(root);
	return 0;
}

//binary tree
tnode *new_node(int data) {
	tnode *np = (tnode *) malloc(sizeof(tnode));
	if (np == NULL)
		return NULL;
	np->data = data;
	np->visited = 0;
	np->left = NULL;
	np->right = NULL;
	return np;
}

int get_node_count(tnode *root) {
	int count = 1;
	if (root->left != NULL) {
		count += get_node_count(root->left);
	}
	if (root->right != NULL) {
		count += get_node_count(root->right);
	}
	return count;

}


int get_height(tnode *root) {
	int left;
	int right;
	if (root == NULL) {
		return 0;
	}
	left = get_height(root->left);
	right = get_height(root->right);

	if (left > right) {
		return left + 1;
	} else {
		return right + 1;
	}

}

void clean_tree(tnode *root) {
	if (root) {
		clean_tree(root->left);
		clean_tree(root->right);
		free(root);
	}
}

void display_preorder(tnode *root) {
	if (root == NULL) {
		return;
	}
	printf("%c ", root->data);
	display_preorder(root->left);
	display_preorder(root->right);
}

void display_inorder(tnode *root) {
	if (root == NULL) {
		return;
	}
	display_inorder(root->left);
	printf("%c ", root->data);
	display_inorder(root->right);
}

void display_postorder(tnode *root) {
	if (root == NULL) {
		return;
	}
	display_postorder(root->left);
	display_postorder(root->right);
	printf("%c ", root->data);
}

//stack operation functions, modified from a6q2
void push(snode **topp, tnode *tp) {
	snode *np = malloc(sizeof(tnode));
	snode *temp;

	temp = *topp;
	if (*topp != NULL) {
		np->next = temp;
		np->tnp = tp;
		*topp = np;

	} else {
		np->next = NULL;
		np->tnp = tp;
		*topp = np;
	}
}

tnode *pop(snode **topp) {
	tnode *r_tnode = NULL;
	snode *np;

	if (*topp != NULL) {
		np = *topp;
		*topp = (*topp)->next;
		r_tnode = np->tnp;

	}
	return r_tnode;
}

void clean_stack(snode **topp) {
	snode *temp;
	snode *np = *topp;
	while (np != NULL) {
		temp = np;
		np = np->next;
		free(temp);
	}
	*topp = NULL;
}

void display_df_iteration(tnode *root, int option) {
	if (root == NULL)
		return;
	snode *top = NULL;
	tnode *p = root, *c = NULL;
	push(&top, root);
	if (option == 0)
		printf("%c ", root->data);

	while (top) {
		p = top->tnp;

		if (p->left == NULL && p->right == NULL) {
			c = pop(&top);
			if (option == 1)
				printf("%c ", (char) c->data);
			if (option == 2)
				printf("%c ", (char) c->data);
		} else if (p->right == c) {
			c = pop(&top);
			if (option == 1)
				printf("%c ", (char) c->data);
		} else if (p->left == c) {
			if (p->right == NULL) {
				c = pop(&top);
				if (option == 1)
					printf("%c ", (char) c->data);
				if (option == 2)
					printf("%c ", (char) top->tnp->data);
			} else {
				if (option == 2)
					printf("%c ", top->tnp->data);
				push(&top, p->right);
				if (option == 0)
					printf("%c ", p->right->data);

			}
		} else if (p->left != NULL) {
			push(&top, p->left);
			if (option == 0)
				printf("%c ", p->left->data);

		} else if (p->left == NULL) {
			c = p->left;
			if (option == 1)
				printf("%c ", (char) c->data);
		}
	}
}

tnode *dfs_iteration(tnode *root, int val) {
	if (root == NULL) {
		return NULL;
	}
	snode *top = NULL;
	tnode *p = root;
	p->visited = 1;
	push(&top, p);

	while (top) {
		p = pop(&top);

		if (p->data == val) {
			clean_stack(&top);
			return p;
		}
		if (p->right && p->right->visited == 0) {
			p->right->visited = 1;
			push(&top, p->right);

		}
		if (p->left && p->left->visited == 0) {
			p->left->visited = 1;
			push(&top, p->left);
		}

	}
	return NULL;

}

//queue operation functions
void enqueue(qnode **frontp, qnode **rearp, tnode *tp) {
	qnode *newnode;
	newnode = malloc(sizeof(qnode));
	newnode->tnp = tp;
	newnode->next = NULL;

	if (*frontp == NULL) {
		*frontp = newnode;
		*rearp = newnode;
	} else {
		(*rearp)->next = newnode;
		*rearp = newnode;
	}
}

tnode *dequeue(qnode **frontp, qnode **rearp) {
	tnode *r_tnode = NULL;
	qnode *head;
	head = *frontp;

	if (*frontp == NULL) {
		return NULL;
	} else {
		r_tnode = head->tnp;
		*frontp = head->next;
		if (*frontp == NULL) {
			*rearp = NULL;
		}
		return r_tnode;
	}
}

void clean_queue(qnode **frontp, qnode **rearp) {
	qnode *qnp = *frontp;
	qnode *temp;

	while (qnp != NULL) {
		temp = qnp;
		qnp = qnp->next;
		free(temp);
	}
	*frontp = NULL;
	*rearp = NULL;
}

void display_bfs_iteration(tnode *root) {
	if (root == NULL)
		return;
	else {
		tnode *tp;
		qnode *front = NULL, *rear = NULL;
		enqueue(&front, &rear, root);
		while (front) {
			tp = dequeue(&front, &rear);
			printf("%c ", tp->data);
			if (tp->left)
				enqueue(&front, &rear, tp->left);
			if (tp->right)
				enqueue(&front, &rear, tp->right);
		}
		clean_queue(&front, &rear);
	}
}

tnode *bfs_iteration(tnode *root, int val) {
	if (root == NULL) {
		return NULL;
	} else {
		tnode *tp;
		qnode *front = NULL, *rear = NULL;
		enqueue(&front, &rear, root);
		while (front) {
			tp = dequeue(&front, &rear);
			if (tp->left) {
				enqueue(&front, &rear, tp->left);
			}
			if (tp->right) {
				enqueue(&front, &rear, tp->right);
			}

		}
		return tp;
	}

}
