#include "pocket.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
	struct Cube* e = identity_cube();

	printf("Identity cube:\n");
	
	print_cube(e);

	apply_f(e);
	apply_t(e);
	apply_r(e);

	printf("Applied rotations:\n");
	
	print_cube(e);

	free(e);
	
	return 0;
}
