/*
-------------------------------------
File:    a10q1.c
Project: a10q1
file description
-------------------------------------
Author:  Kathleen Milligan
ID:      160458550
Email:   mill8550
Version  2018-04-01
-------------------------------------
 */



#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"

int main(void) {
	//create a weighted graph
	graph *graph = new_graph(5);
	add_edge(graph, 0, 1, 7);
	add_edge(graph, 1, 0, 7);
	add_edge(graph, 0, 2, 3);
	add_edge(graph, 2, 0, 3);
	add_edge(graph, 1, 2, 4);
	add_edge(graph, 2, 1, 4);
	add_edge(graph, 2, 3, 10);
	add_edge(graph, 3, 2, 10);
	add_edge(graph, 1, 3, 9);
	add_edge(graph, 3, 1, 9);
	add_edge(graph, 1, 4, 11);
	add_edge(graph, 4, 1, 11);

	printf("\nWeighted graph in adjacency list");
	printf("\nnode from: (to weight) ... ");
	display_graph(graph);

	//compute MST by Prim's algorithm using min-heap
	elgraph *t = mst_prim(graph, 0);
	printf("\nMST in weighted edge list");
	printf("\n(from, to, weight)\n");
	display_elgraph(t);
	printf("\nCost: %d", weight_elgraph(t));
	delete_elgraph(t);
	printf("\nMST is deleted");

	//compute SPT by Dijsktra's algorithm using min-heap
	t = spt_dijsktra(graph, 0);
	printf("\nSPT in weighted edge list");
	printf("\n(from, to, weight)\n");
	display_elgraph(t);
	delete_elgraph(t);
	printf("\nSPT is deleted");

	//compute SP by Dijsktra's algorithm using min-heap
	int start = 0, end = 4;
	t = sp_dijsktra(graph, start, end);
	printf("\nShortest path from %d to %d\n", start, end);
	display_elgraph(t);
	printf("\nThe length of the shortest path: %d", weight_elgraph(t));
	delete_elgraph(t);
	printf("\nSP is deleted");

	//delete the graph
	delete_graph(graph);
	printf("\nGraph is deleted");

	return 0;
}


