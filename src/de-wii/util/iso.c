/**
 * @file iso.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "iso.h"

iso_grid_t iso_grid(i32 tile_w, i32 tile_h) {
    iso_grid_t g;
    g.tile_w = tile_w;
    g.tile_h = tile_h;
    return g;
}

vec2_t iso_to_screen(iso_grid_t g, f32 col, f32 row) {
    f32 half_w = g.tile_w * DIV2;
    f32 half_h = g.tile_h * DIV2;

    return vec2_create(
        (col - row) * half_w,
        (col + row) * half_h
    );
}

vec2_t screen_to_iso(iso_grid_t g, f32 sx, f32 sy) {
    f32 half_w = g.tile_w * DIV2;
    f32 half_h = g.tile_h * DIV2;

    f32 u = sx / half_w;
    f32 v = sy / half_h;

    return vec2_create(
        (u + v) * DIV2,
        (v - u) * DIV2
    );
}
