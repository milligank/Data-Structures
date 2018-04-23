/*
-------------------------------------
File:    graph.h
Project: a10q1
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-04-01
-------------------------------------
 */


#ifndef GRAPH_H_
#define GRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define INFINITY 9999

//APIs for graph representation by adjacency list
typedef struct ADJNODE {
	int vertex;
	int weight;
	struct ADJNODE *next;
} adjnode;

typedef struct GRAPH {
	int vn;            //number of nodes
	adjnode **adjlist; //pointer to an array of pointers of neighbors
} graph;

graph *new_graph(int n);
void add_edge(graph *g, int from, int to, int weight);
int get_weight(graph *g, int from, int to);
void display_graph(graph *g);
void delete_graph(graph *g);

//APIs for graph representation by edge list
typedef struct EDGE {
	int from;
	int to;
	int weight;
	struct EDGE *next;
} edge;

typedef struct EDGELIST {
	int en;              //number of nodes, may some other info
	edge *edgeliststart; //pointer to the start of edge list
	edge *edgelistend;   //pointer to end of edge list
} elgraph;

elgraph *new_elgraph();
void add_elgraph_edge(elgraph *t, int from, int to, int weight);
void add_elgraph_start(elgraph *t, int from, int to, int weight);
int weight_elgraph(elgraph *t);
void display_elgraph(elgraph *t);
void delete_elgraph(elgraph *t);

//graph algorithms
elgraph *mst_prim(graph *g, int start);
elgraph *spt_dijsktra(graph *g, int start);
elgraph *sp_dijsktra(graph *g, int start, int end);


#endif /* GRAPH_H_ */
