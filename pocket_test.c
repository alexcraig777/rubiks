#include "pocket.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
	struct Cube* id = identity_cube();
	struct Cube* cube = identity_cube();

	printf("Identity cube:\n");
	
	print_cube(cube);

	int k = 0;
	while (1) {
		apply_f(cube);
		apply_t(cube);
		apply_r(cube);

		k++;

		if (check_cubes_equal(cube, id)) {
			break;
		}
	}
	
	printf("Applied ftr %d times:\n", k);
	
	print_cube(cube);

	free(cube);
	free(id);
	
	return 0;
}
