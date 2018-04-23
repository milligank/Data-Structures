/*
-------------------------------------
File:    graph.c
Project: a10q1
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-04-01
-------------------------------------
 */



#include "graph.h"
#include "heap.h"

graph *new_graph(int vertex_number) {
	graph *gp = malloc(sizeof(graph));
	adjnode **np = malloc(vertex_number * sizeof(adjnode*));
	int i;
	for (i = 0; i < vertex_number; i++) {
		np[i] = NULL;
	}
	gp->vn = vertex_number;
	gp->adjlist = np;
	return gp;
}

void add_edge(graph *g, int from, int to, int weight) {

	adjnode *itemindex = g->adjlist[from]; // itemitemindex of the original list
	adjnode *temp;

	if (g->adjlist[from] == NULL) {
		g->adjlist[from] = malloc(sizeof(adjnode));
		g->adjlist[from]->vertex = to;
		g->adjlist[from]->weight = weight;
		g->adjlist[from]->next = NULL;

	} else {
		temp = malloc(sizeof(adjnode));

		temp->vertex = to;
		temp->weight = weight;
		temp->next = NULL;

		while (g->adjlist[from]->next != NULL) {
			g->adjlist[from] = g->adjlist[from]->next;
		}

		g->adjlist[from]->next = temp;
		g->adjlist[from] = itemindex;

	}
} /* add_edge */

int get_weight(graph *g, int from, int to) {

	return 0;
}

void display_graph(graph *g) {

	int i;
	adjnode *itemitemindex;
	printf("\n");
	for (i = 0; i < g->vn; i++) {
		itemitemindex = g->adjlist[i];
		printf("node %d: ", i);
		while (g->adjlist[i] != NULL) {
			printf("(%d, %d) ", g->adjlist[i]->vertex, g->adjlist[i]->weight);
			g->adjlist[i] = g->adjlist[i]->next;
		}
		printf("\n");
		g->adjlist[i] = itemitemindex; //fixes destructive read problem
	}

} /* display_graph */

void delete_graph(graph *g) {

	int i;
	adjnode *temp, *ptr;

	for (i = 0; i < g->vn; i++) {

		temp = g->adjlist[i];

		while (temp->next != NULL) {
			ptr = temp;
			temp = temp->next;
			free(ptr);
		}

	}

	free(g);

} /* delete_graph */

elgraph *new_elgraph() {
	elgraph *tp = malloc(sizeof(elgraph));
	tp->en = 0;
	tp->edgeliststart = NULL;
	tp->edgelistend = NULL;
	return tp;
}

int weight_elgraph(elgraph *t) {

	int cost = 0;
	edge *itemindex = t->edgeliststart;

	while (itemindex != NULL) {
		cost += itemindex->weight;
		itemindex = itemindex->next;
	}

	return cost;
}

void display_elgraph(elgraph *t) {

	edge *itemindex = t->edgeliststart;

	while (itemindex != NULL) {
		printf("(%d, %d, %d)\n", itemindex->from, itemindex->to,
				itemindex->weight);
		itemindex = itemindex->next;
	}

}

void delete_elgraph(elgraph *t) {

	edge *temp, *ptr;

	temp = t->edgeliststart;

	while (temp->next != NULL) {
		ptr = temp;
		temp = temp->next;
		free(ptr);
	}

	free(t);
}

void add_elgraph_edge(elgraph *t, int from, int to, int weight) {

	edge *itemindex = t->edgeliststart; 	// hold original pointer
	edge *newedge = malloc(sizeof(edge));

	newedge->from = from;
	newedge->to = to;
	newedge->weight = weight;
	newedge->next = NULL;

	if (t->edgeliststart == NULL) {
		t->edgeliststart = malloc(sizeof(edge));
		t->edgeliststart = newedge;
	} else {
		while (t->edgeliststart->next != NULL) {
			t->edgeliststart = t->edgeliststart->next;
		}
		t->edgeliststart->next = newedge;
		t->edgeliststart = itemindex;
	}

	t->en++;

} /* add_elgraph_edge */

elgraph *mst_prim(graph *g, int start) {
	if (g == NULL)
		return NULL;

	int i, heapitemindex, u, n = g->vn;
	int visited[n], parent[n];
	for (i = 0; i < n; i++) {
		visited[i] = 0;
	}

	gnode *gn;

	heap *h = new_heap(4);

	adjnode *temp = g->adjlist[start];
	visited[start] = 1;

	while (temp) {
		insert(h, new_gnode(temp->weight, temp->vertex));
		parent[temp->vertex] = start;
		visited[temp->vertex] = 0;
		parent[temp->vertex] = start;
		temp = temp->next;
	}

	elgraph *mst = new_elgraph();

	while (h->size > 0) {
		gn = extract_min(h);
		u = gn->vertex;
		visited[u] = 1;
		add_elgraph_edge(mst, parent[u], u, gn->key);
		free(gn);

		temp = g->adjlist[u];

		while (temp) {
			heapitemindex = find_index(h, temp->vertex);
			if (heapitemindex >= 0) {
				if (visited[temp->vertex] == 0
						&& temp->weight < h->data[heapitemindex]->key) {
					decrease_key(h, heapitemindex, temp->weight);
					parent[temp->vertex] = u;
				}
			} else {
				if (visited[temp->vertex] == 0) {
					insert(h, new_gnode(temp->weight, temp->vertex));
					parent[temp->vertex] = u;
				}

			}
			temp = temp->next;
		} /* while */
	} /* while */
	return mst;
} /* mst_prim */

elgraph *spt_dijsktra(graph *g, int start) {
	if (g == NULL)
		return NULL;

	int i = 0, heapitemindex = 0, u = 0;
	int n = g->vn;
	int visited[n], parent[n], label[n];
	for (i = 0; i < n; i++) {
		visited[i] = 0;
		label[i] = 9999;
	}

	gnode *gn;

	heap *h = new_heap(4);
	adjnode *temp = g->adjlist[start];
	visited[start] = 1;
	label[start] = 0;

	while (temp) {
		insert(h, new_gnode(temp->weight, temp->vertex));
		parent[temp->vertex] = start;
		visited[temp->vertex] = 0;
		temp = temp->next;
	} /* while */

	elgraph *spt = new_elgraph();

	while (h->size > 0) {
		gn = extract_min(h);
		u = gn->vertex;
		visited[u] = 1;
		add_elgraph_edge(spt, parent[u], u, gn->key);
		free(gn);

		temp = g->adjlist[u];

		while (temp) {
			heapitemindex = find_index(h, temp->vertex);
			if (heapitemindex >= 0) {
				if ((visited[temp->vertex] == 0)
						&& (temp->weight + label[u]
								< h->data[heapitemindex]->key)) {
					decrease_key(h, heapitemindex, (temp->weight));
					parent[temp->vertex] = u;
				}
			} else {
				if (visited[temp->vertex] == 0) {
					insert(h, new_gnode(temp->weight, temp->vertex));
					parent[temp->vertex] = u;
				}
			}

			temp = temp->next;

		} /* while */
	} /* while */

	return spt;
} /* spt_dijsktra */

elgraph *sp_dijsktra(graph *g, int start, int end) {
	if (!g)
		return NULL;

	int i = 0, heapitemindex = 0, u = 0;
	int n = g->vn;
	int done = 0;
	int visited[n], parent[n], label[n];
	for (i = 0; i < n; i++) {
		visited[i] = 0;
		label[i] = 9999;
	}

	gnode *gn;

	heap *h = new_heap(4);
	adjnode *temp = g->adjlist[start];
	visited[start] = 1;
	label[start] = 0;

	while (temp) {
		insert(h, new_gnode(temp->weight, temp->vertex));
		parent[temp->vertex] = start;
		visited[temp->vertex] = 0;
		temp = temp->next;
	} /* while */

	elgraph *spt = new_elgraph();

	while ((h->size > 0) && (done == 0)) {
		gn = extract_min(h);
		u = gn->vertex;
		visited[u] = 1;
		add_elgraph_edge(spt, parent[u], u, gn->key);
		if (gn->key == end) {
			done = 1;
		}
		free(gn);

		temp = g->adjlist[u];

		while (temp) {
			heapitemindex = find_index(h, temp->vertex);
			if (heapitemindex >= 0) {
				if ((visited[temp->vertex] == 0)
						&& (temp->weight + label[u]
								< h->data[heapitemindex]->key)) {
					decrease_key(h, heapitemindex, (temp->weight));
					parent[temp->vertex] = u;
				}
			} else {
				if (visited[temp->vertex] == 0) {
					insert(h, new_gnode(temp->weight, temp->vertex));
					parent[temp->vertex] = u;
				}
			}

			temp = temp->next;

		} /* while */
	} /* while */

	//build SPT by Dijsktra's shortest path tree algorithm, and break after the end node is added

	elgraph *sp = new_elgraph();
	elgraph *spreverse = new_elgraph();

	edge *itemindex = spt->edgeliststart;
	int weight = 0;
	done = 0;
	i = 0;
	u = end;

	while (u != start) {
		while ((done == 0) && (i < spt->en)) {
			while ((itemindex) && (done == 0)) {
				if ((itemindex->from == parent[u]) && (itemindex->to == u)) {
					weight = itemindex->weight;
					done = 1;
				} else {
					itemindex = itemindex->next;
					i++;

				}
			}
		}

		add_elgraph_edge(spreverse, parent[u], u, weight);
		u = parent[u];
		done = 0;
		i = 0;
		itemindex = spt->edgeliststart;
	}

	int vcount = 0; // number of vertices in the sp graph
	itemindex = spreverse->edgeliststart;

	while (itemindex != NULL) {
		vcount++;
		itemindex = itemindex->next;
	}

	edge *edgearray[vcount];
	edge *e;

	itemindex = spreverse->edgeliststart;

	for (i = 1; i <= vcount; i++) {
		edgearray[vcount - i] = malloc(sizeof(edge));
		e = edgearray[vcount - i];
		e->from = itemindex->from;
		e->to = itemindex->to;
		e->weight = itemindex->weight;
		itemindex = itemindex->next;
	}

	for (i = 0; i < vcount; i++) {
		add_elgraph_edge(sp, edgearray[i]->from, edgearray[i]->to,
				edgearray[i]->weight);
	}

	return sp;
}


