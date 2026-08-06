/**
 * @file color.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../de.h"

/**
 * @brief color structure representing RGBA values.
*/
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} color_t;

/**
 * @brief Creates a color with the specified RGBA values.
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @param a Alpha component (0-255)
 * @return A color_t struct with the specified RGBA values
*/
color_t color(u8 r, u8 g, u8 b, u8 a);

/**
 * @brief Creates a new color with the specified RGBA values.
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @param a Alpha component (0-255)
 * @return A pointer to a new color_t struct with the specified RGBA values
*/
color_t* color_new(u8 r, u8 g, u8 b, u8 a);

/**
 * @brief Frees a color_t previously created with color_new.
 * @param color Pointer to the heap-allocated color_t to destroy
*/
void color_destroy(color_t* color);

/**
 * @brief Converts a color_t to an SDL_Color.
 * @param color The color_t to convert
 * @return The corresponding SDL_Color
*/
SDL_Color color_to_sdl_color(const color_t color);

/**
 * @brief Converts a color_t to a hexadecimal RGBA value.
 * @param color The color_t to convert
 * @return The hexadecimal representation of the color
*/
u32 color_to_rgba_hex(const color_t color);

/**
 * @brief Converts a color_t to a hexadecimal ARGB value.
 * @param color The color_t to convert
 * @return The hexadecimal representation of the color
*/
u32 color_to_argb_hex(const color_t color);

/**
 * @brief Returns a red color.
 * @return A color_t struct representing red
*/
color_t color_red(void);

/**
 * @brief Returns a green color.
 * @return A color_t struct representing green
*/
color_t color_green(void);

/**
 * @brief Returns a blue color.
 * @return A color_t struct representing blue
*/
color_t color_blue(void);

/**
 * @brief Returns a white color.
 * @return A color_t struct representing white
*/
color_t color_white(void);

/**
 * @brief Returns a black color.
 * @return A color_t struct representing black
*/
color_t color_black(void);

/**
 * @brief Returns a silver color.
 * @return A color_t struct representing silver
*/
color_t color_silver(void);

/**
 * @brief Returns a gray color.
 * @return A color_t struct representing gray
*/
color_t color_gray(void);

/**
 * @brief Returns a yellow color.
 * @return A color_t struct representing yellow
*/
color_t color_yellow(void);
