#include "pocket.h"

#include <stdio.h>
#include <stdlib.h>

char color_char(enum Color color) {
	char rtn;
	if (color == red) {
		rtn = 'R';
	} else if (color == white) {
		rtn = 'W';
	} else if (color == blue) {
		rtn = 'B';
	} else if (color == green) {
		rtn = 'G';
	} else if (color == orange) {
		rtn = 'O';
	} else if (color == yellow) {
		rtn = 'Y';
	}
	return rtn;
}

void print_cube(struct Cube* cube) {
	printf("    %c%c\n",
		   color_char(cube->stickers.names.t_lb),
		   color_char(cube->stickers.names.t_br));
	printf("    %c%c\n",
		   color_char(cube->stickers.names.t_fl),
		   color_char(cube->stickers.names.t_rf));
	printf(" %c%c %c%c %c%c %c%c\n",
		   color_char(cube->stickers.names.l_bt),
		   color_char(cube->stickers.names.l_tf),
		   color_char(cube->stickers.names.f_lt),
		   color_char(cube->stickers.names.f_tr),
		   color_char(cube->stickers.names.r_ft),
		   color_char(cube->stickers.names.r_tb),
		   color_char(cube->stickers.names.b_rt),
		   color_char(cube->stickers.names.b_tl));
	printf(" %c%c %c%c %c%c %c%c\n",
		   color_char(cube->stickers.names.l_db),
		   color_char(cube->stickers.names.l_fd),
		   color_char(cube->stickers.names.f_dl),
		   color_char(cube->stickers.names.f_rd),
		   color_char(cube->stickers.names.r_df),
		   color_char(cube->stickers.names.r_bd),
		   color_char(cube->stickers.names.b_ld),
		   color_char(cube->stickers.names.b_dr));
	printf("    %c%c\n",
		   color_char(cube->stickers.names.d_lf),
		   color_char(cube->stickers.names.d_fr));
	printf("    %c%c\n",
		   color_char(cube->stickers.names.d_bl),
		   color_char(cube->stickers.names.d_rb));
}

// Returns a pointer to a newly allocated cube in the identity
// position.
struct Cube* identity_cube() {
	struct Cube* rtn = malloc(sizeof(struct Cube));
	// Notice that the indices are in octal!
	
	// top
	rtn->stickers.array[00] = green;
	rtn->stickers.array[01] = green;
	rtn->stickers.array[02] = green;
	rtn->stickers.array[03] = green;

	// deck
	rtn->stickers.array[04] = blue;
	rtn->stickers.array[05] = blue;
	rtn->stickers.array[06] = blue;
	rtn->stickers.array[07] = blue;

	// left
	rtn->stickers.array[010] = white;
	rtn->stickers.array[011] = white;
	rtn->stickers.array[012] = white;
	rtn->stickers.array[013] = white;

	// right
	rtn->stickers.array[014] = yellow;
	rtn->stickers.array[015] = yellow;
	rtn->stickers.array[016] = yellow;
	rtn->stickers.array[017] = yellow;

	// front
	rtn->stickers.array[020] = orange;
	rtn->stickers.array[021] = orange;
	rtn->stickers.array[022] = orange;
	rtn->stickers.array[023] = orange;

	// back
	rtn->stickers.array[024] = red;
	rtn->stickers.array[025] = red;
	rtn->stickers.array[026] = red;
	rtn->stickers.array[027] = red;

	rtn->f = NULL;
	rtn->g = NULL;
	rtn->r = NULL;
	rtn->s = NULL;
	rtn->t = NULL;
	rtn->u = NULL;

	return rtn;
}

// Returns 1 if the cube positions are exactly equal. Otherwise
// returns 0.
int check_cubes_equal(struct Cube* cube1, struct Cube* cube2) {
	// Assume the cubes are equal. Iterate through the stickers
	// checking equality, and if we find an inconsistency, mark
	// them unequal and break.
	int rtn = 1;
	int idx;
	for (idx = 0; idx < 24; idx++) {
		if (cube1->stickers.array[idx] != cube2->stickers.array[idx]) {
			rtn = 0;
			break;
		}
	}
	return rtn;
}

// Rotates the cube clockwise around the front face.
// This changes only the sticker value fields.
void apply_f(struct Cube* cube) {
	// First change the front stickers.
	enum Color f_lt = cube->stickers.names.f_lt;
	cube->stickers.names.f_lt = cube->stickers.names.f_dl;
	cube->stickers.names.f_dl = cube->stickers.names.f_rd;
	cube->stickers.names.f_rd = cube->stickers.names.f_tr;
	cube->stickers.names.f_tr = f_lt;

	// Change the sticker values on other faces.
	// l_tf -> t_fl -> t_rf -> r_ft -> r_df -> d_fr -> d_lf -> l_fd -> l_tf
	enum Color l_fd = cube->stickers.names.l_fd;
	enum Color l_tf = cube->stickers.names.l_tf;
	cube->stickers.names.l_tf = cube->stickers.names.d_lf;
	cube->stickers.names.l_fd = cube->stickers.names.d_fr;
	cube->stickers.names.d_lf = cube->stickers.names.r_df;
	cube->stickers.names.d_fr = cube->stickers.names.r_ft;
	cube->stickers.names.r_df = cube->stickers.names.t_rf;
	cube->stickers.names.r_ft = cube->stickers.names.t_fl;
	cube->stickers.names.t_rf = l_tf;
	cube->stickers.names.t_fl = l_fd;
}

// Rotates the cube anitclockwise about the front face.
void apply_g(struct Cube* cube) {
	// Just apply f 3 times.
	apply_f(cube);
	apply_f(cube);
	apply_f(cube);
}

// Rotates the cube clockwise around the right face.
void apply_r(struct Cube* cube) {
	// Just change the sticker values.
	// First change the right stickers.
	enum Color r_ft = cube->stickers.names.r_ft;
	cube->stickers.names.r_ft = cube->stickers.names.r_df;
	cube->stickers.names.r_df = cube->stickers.names.r_bd;
	cube->stickers.names.r_bd = cube->stickers.names.r_tb;
	cube->stickers.names.r_tb = r_ft;

	// Change the sticker values on other faces.
	// f_tr -> t_rf -> t_br -> b_rt -> b_dr -> d_rb -> d_fr -> f_rd -> f_tr
	enum Color f_rd = cube->stickers.names.f_rd;
	enum Color f_tr = cube->stickers.names.f_tr;
	cube->stickers.names.f_tr = cube->stickers.names.d_fr;
	cube->stickers.names.f_rd = cube->stickers.names.d_rb;
	cube->stickers.names.d_fr = cube->stickers.names.b_dr;
	cube->stickers.names.d_rb = cube->stickers.names.b_rt;
	cube->stickers.names.b_dr = cube->stickers.names.t_br;
	cube->stickers.names.b_rt = cube->stickers.names.t_rf;
	cube->stickers.names.t_br = f_tr;
	cube->stickers.names.t_rf = f_rd;
}

// Rotates the cube anticlockwise about the right face.
void apply_s(struct Cube* cube) {
	// Just apply r 3 times.
	apply_r(cube);
	apply_r(cube);
	apply_r(cube);
}

// Rotates the cube clockwise around the top face.
void apply_t(struct Cube* cube) {
	// Just change the sticker values.
	// First change the top stickers.
	enum Color t_lb = cube->stickers.names.t_lb;
	cube->stickers.names.t_lb = cube->stickers.names.t_fl;
	cube->stickers.names.t_fl = cube->stickers.names.t_rf;
	cube->stickers.names.t_rf = cube->stickers.names.t_br;
	cube->stickers.names.t_br = t_lb;

	// Change the sticker values on other faces.
	// top:   l_bt -> b_tl -> b_rt -> r_tb -> r_ft -> f_tr -> f_lt -> l_tf -> l_bt
	enum Color l_bt = cube->stickers.names.l_bt;
	enum Color l_tf = cube->stickers.names.l_tf;
	cube->stickers.names.l_bt = cube->stickers.names.f_lt;
	cube->stickers.names.l_tf = cube->stickers.names.f_tr;
	cube->stickers.names.f_lt = cube->stickers.names.r_ft;
	cube->stickers.names.f_tr = cube->stickers.names.r_tb;
	cube->stickers.names.r_ft = cube->stickers.names.b_rt;
	cube->stickers.names.r_tb = cube->stickers.names.b_tl;
	cube->stickers.names.b_rt = l_bt;
	cube->stickers.names.b_tl = l_tf;
}

// Rotates the cube anticlockwise about the top face.
void apply_u(struct Cube* cube) {
	// Just apply t 3 times.
	apply_t(cube);
	apply_t(cube);
	apply_t(cube);
}
