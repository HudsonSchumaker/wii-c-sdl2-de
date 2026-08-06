/**
 * @file color.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "color.h"

color_t color(u8 r, u8 g, u8 b, u8 a) {
    color_t color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

color_t* color_new(u8 r, u8 g, u8 b, u8 a) {
    color_t* heap_color = malloc(sizeof(color_t));
    *heap_color = color(r, g, b, a);
    return heap_color;
}

void color_destroy(color_t* color) {
    free(color);
}

SDL_Color color_to_sdl_color(const color_t color) {
    SDL_Color sdl_color;
    sdl_color.r = color.r;
    sdl_color.g = color.g;
    sdl_color.b = color.b;
    sdl_color.a = color.a;
    return sdl_color;
}

u32 color_to_rgba_hex(const color_t color) {
    return (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

u32 color_to_argb_hex(const color_t color) {
    return (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
}

color_t color_red(void) {
    return color(255, 0, 0, 255);
}

color_t color_green(void) {
    return color(0, 255, 0, 255);
}

color_t color_blue(void) {
    return color(0, 0, 255, 255);
}

color_t color_silver(void) {
    return color(192, 192, 192, 255);
}

color_t color_gray(void) {
    return color(128, 128, 128, 255);
}

color_t color_yellow(void) {
    return color(0, 255, 255, 255);
}

color_t color_white(void) {
    return color(255, 255, 255, 255);
}

color_t color_black(void) {
    return color(0, 0, 0, 255);
}
