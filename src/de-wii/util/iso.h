/**
 * @file iso.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../de.h"
#include "../math/math2d.h"

/**
 * @brief Describes the pixel size of an isometric diamond tile (2:1 projection).
*/
typedef struct {
    i32 tile_w;
    i32 tile_h;
} iso_grid_t;

/**
 * @brief Creates an iso_grid_t with the specified diamond tile dimensions.
 * @param tile_w The full width of a tile diamond in pixels
 * @param tile_h The full height of a tile diamond in pixels
 * @return An iso_grid_t struct initialized with the provided dimensions
*/
iso_grid_t iso_grid(i32 tile_w, i32 tile_h);

/**
 * @brief Converts a fractional grid (col, row) coordinate to a screen-space pixel position using a 2:1 isometric diamond projection.
 * @param g The iso_grid_t describing the tile dimensions
 * @param col The column coordinate on the grid
 * @param row The row coordinate on the grid
 * @return A vec2_t with the screen-space pixel position
*/
vec2_t iso_to_screen(iso_grid_t g, f32 col, f32 row);

/**
 * @brief Converts a screen-space pixel position back to a fractional grid (col, row) coordinate. Callers should floor the result to get the integer tile, e.g. for cursor/tile picking.
 * @param g The iso_grid_t describing the tile dimensions
 * @param sx The screen-space X pixel position
 * @param sy The screen-space Y pixel position
 * @return A vec2_t with the fractional (col, row) grid coordinate
*/
vec2_t screen_to_iso(iso_grid_t g, f32 sx, f32 sy);
