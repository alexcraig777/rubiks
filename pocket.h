#ifndef POCKET_H
#define POCKET_H

enum Color {red, white, blue, green, yellow, orange};

// Top           = t
// Deck (bottom) = d
// Left          = l
// Right         = r
// Front         = f
// Back          = b

// If we leave fixed the lower back left corner, then the
// only actions we need to consider are:
// - front = f (clockwise from front)
//   - inv = g
// - right = r (clockwise from right)
//   - inv = s
// - top   = t (clockwise from top)
//   - inv = u

struct StickerNames {
	enum Color t_lb;
	enum Color t_br;
	enum Color t_rf;
	enum Color t_fl;

	enum Color d_lf;
	enum Color d_fr;
	enum Color d_rb;
	enum Color d_bl;

	enum Color l_bt;
	enum Color l_tf;
	enum Color l_fd;
	enum Color l_db;

	enum Color r_ft;
	enum Color r_tb;
	enum Color r_bd;
	enum Color r_df;

	enum Color f_lt;
	enum Color f_tr;
	enum Color f_rd;
	enum Color f_dl;

	enum Color b_rt;
	enum Color b_tl;
	enum Color b_ld;
	enum Color b_dr;
};

union Stickers {
	struct StickerNames names;
	enum Color array[24];
};

struct Cube {
    // The array of sticker colors. We put this in an array to make
    // it easier to process in many functions. The order of stickers
    // is as follows:
    // - top face:    t_lb, t_br, t_rf, t_fl
    // - bottom face: d_lf, d_fr, d_rb, d_bl
    // - left face:   l_bt, l_tf, l_fd, l_db
    // - right face:  r_ft, r_tb, r_bd, r_df
    // - front face:  f_lt, f_tr, f_rd, f_dl
    // - back frace:  b_rt, b_tl, b_ld, b_dr
    union Stickers stickers;

    // front: l_tf -> t_fl -> t_rf -> r_ft -> r_df -> d_fr -> d_lf -> l_fd -> l_tf
    // right: f_tr -> t_rf -> t_br -> b_rt -> b_dr -> d_rb -> d_fr -> f_rd -> f_tr
    // top:   l_bt -> b_tl -> b_rt -> r_tb -> r_ft -> f_tr -> f_lt -> l_tf -> l_bt
    // 8 -> 21 -> 20 -> 13 -> 12 -> 17 -> 16 -> 9 -> 8

    // Pointers to the positions obtained by applying the generators
    // to this position.
    struct Cube* f;
    struct Cube* g;
    struct Cube* r;
    struct Cube* s;
    struct Cube* t;
    struct Cube* u;
};

void print_cube(struct Cube* cube);

struct Cube* identity_cube();

int check_cubes_equal(struct Cube* cube1, struct Cube* cube2);

void apply_f(struct Cube* cube);
void apply_g(struct Cube* cube);
void apply_r(struct Cube* cube);
void apply_s(struct Cube* cube);
void apply_t(struct Cube* cube);
void apply_u(struct Cube* cube);

#endif
