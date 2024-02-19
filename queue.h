#ifndef QUEUE_H
#define QUEUE_H

struct LinkedNode {
	struct Cube* cube;
	struct LinkedNode* next;
};
	
struct LinkedQueue {
	struct LinkedNode* head;
	struct LinkedNode* tail;
};

int check_in_queue(struct LinkedQueue* queue, struct Cube* cube);

void insert(struct LinkedQueue* queue, struct Cube* cube);

struct Cube* pop(struct LinkedQueue* queue);

#endif
