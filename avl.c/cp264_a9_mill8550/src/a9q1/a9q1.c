/*
 ============================================================================
 Name        : cp264_a9_mill8550.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include "heap.h"

int main(int argc, char *args[]) {
	int c = 4, n = 10;
	int v = 6, k = 2, i = 0;

	if (argc > 1) {
		c = atoi(args[1]);
	}
	if (argc > 2) {
		n = atoi(args[2]);
	}
	if (argc > 3) {
		v = atoi(args[3]);
	}
	if (argc > 4) {
		k = atoi(args[4]);
	}

	heap *hp = new_heap(c);
	if (hp->data == NULL)
		return 0;

	display_heap(hp);

	printf("insert to heap:\n");

	for (i = 1; i <= n; i++) {
		insert(hp, n - i + 4);

	}
	printf("display heap after insertion:");
	display_heap(hp);

	i = find_index(hp, v);

	printf("the index of data value %d is %d\n", v, i);

	printf("decrease key value at index %d to %d", i, k);
	decrease_key(hp, i, k);
	display_heap(hp);

	printf("extract min\n");
	for (i = 0; i < 4 * n / 5; i++) {
		printf("%d ", extract_min(hp));
	}

	printf("\ndisplay heap after extract min:");
	display_heap(hp);

	return 0;
}
