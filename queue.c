#include "queue.h"

#include <stdlib.h>

#include "pocket.h"

// Checks if a given cube position is already in the queue.
// Returns 1 if it is, 0 if it's not.
int check_in_queue(struct LinkedQueue* queue, struct Cube* cube) {
	struct LinkedNode* current = queue->head;
	int rtn = 0;
	while (current != NULL) {
		if (check_cubes_equal(current->cube, cube)) {
			rtn = 1;
			break;
		}
		current = current->next;
	}
	return rtn;
}

// Inserts a new node with the given cube position into the
// queue at the end. Does not verify that it does not already
// exist in the queue.
void insert(struct LinkedQueue* queue, struct Cube* cube) {
	// Allocate a new LinkedNode to hold this cube.
	struct LinkedNode* new_node = malloc(sizeof(struct LinkedNode));
	new_node->cube = cube;
	new_node->next = NULL;
	
	if (queue->head == NULL) {
		// This is the first and only item in the queue.
		queue->head = new_node;
		queue->tail = new_node;
	} else {
		// This is a normal insertion.
		queue->tail->next = new_node;
		queue->tail = new_node;
	}
}

// Removes the first node from the queue. Frees the node's
// memory and returns the pointer to the cube.
struct Cube* pop(struct LinkedQueue* queue) {
	struct Cube* rtn;
	struct LinkedNode* new_head;
	if (queue->head == NULL) {
		// The queue is empty. Return NULL.
		rtn = NULL;
	} else {
		// Get the cube to return.
		rtn = queue->head->cube;
		// Save off the new head, free the old head, and reset
		// the head.
		new_head = queue->head->next;
		free(queue->head);
		queue->head = new_head;

		// Check if the queue is now empty, which means we also need
		// to set the tail to NULL.
		if (queue->head == NULL) {
			queue->tail = NULL;
		}
	}
	return rtn;
}
