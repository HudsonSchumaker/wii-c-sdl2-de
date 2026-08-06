/**
 * @file grid.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "grid.h"
#include "../gfx/gfx.h"

grid_t grid(short rows, short cols, short cell_width, short cell_height) {
    grid_t g;
    g.rows = rows;
    g.cols = cols;
    g.cell_width = cell_width;
    g.cell_height = cell_height;
    return g;
}

grid_t* grid_new(short rows, short cols, short cell_width, short cell_height) {
    grid_t* g = malloc(sizeof(grid_t));
    *g = grid(rows, cols, cell_width, cell_height);
    return g;
}

void grid_destroy(grid_t* grid) {
    free(grid);
}

void grid_render(grid_t* grid) {
    color_t white = color_white();
    short width = grid->cols * grid->cell_width;
    short height = grid->rows * grid->cell_height;

    for (short i = 0; i < grid->cols; i++) {
        short x = i * grid->cell_width;
        gfx_draw_line(x, 0, x, height, white);
    }

    for (short i = 0; i < grid->rows; i++) {
        short y = i * grid->cell_height;
        gfx_draw_line(0, y, width, y, white);
    }
}
