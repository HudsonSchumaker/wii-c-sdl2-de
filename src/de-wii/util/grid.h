/**
 * @file grid.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_GRID_H
#define DE_GRID_H

#include "../de.h"

typedef struct {
    short rows;
    short cols;
    short cell_width;
    short cell_height;
} grid_t;

/**
 * Creates a grid with the specified number of rows, columns, and cell dimensions. The grid is represented as a struct containing these properties.
 * @param rows The number of rows in the grid
 * @param cols The number of columns in the grid
 * @param cell_width The width of each cell in pixels
 * @param cell_height The height of each cell in pixels
 * @return A grid_t struct initialized with the provided properties
*/
grid_t grid(short rows, short cols, short cell_width, short cell_height);

/**
 * Creates a new grid with the specified number of rows, columns, and cell dimensions. The grid is allocated on the heap and should be freed when no longer needed.
 * @param rows The number of rows in the grid
 * @param cols The number of columns in the grid
 * @param cell_width The width of each cell in pixels
 * @param cell_height The height of each cell in pixels
 * @return A pointer to a grid_t struct initialized with the provided properties
*/
grid_t* grid_new(short rows, short cols, short cell_width, short cell_height);

/**
 * Frees a grid_t previously created with grid_new. This function should be called to avoid memory leaks.
 * @param grid Pointer to the heap-allocated grid_t to destroy
*/
void grid_destroy(grid_t* grid);

/**
 * Renders the grid on the screen.
 * @param grid A pointer to the grid_t struct to render
*/
void grid_render(grid_t* grid);

#endif // DE_GRID_H
