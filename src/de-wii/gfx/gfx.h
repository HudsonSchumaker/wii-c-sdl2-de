/**
 * @file gfx.h
 * @author Hudson Schumaker
 * @version 1.1.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "color.h"
#include "../de.h"

typedef struct {
    i32 w;
    i32 h;
    SDL_Texture* texture;
} texture_t;

typedef struct {
    const u8* data;
    texture_t texture;
} texture_cache_entry_t;

/**
 * @brief Loads a texture from memory data.
 * @param data The pointer to the texture data in memory
 * @param size The size of the texture data in bytes
 * @return A pointer to the loaded SDL_Texture, or NULL on failure
*/
SDL_Texture* gfx_load_texture(const u8* data, const size_t size);

/**
 * @brief Loads a texture from memory data and returns a texture_t struct containing the texture and its dimensions.
 * @param data The pointer to the texture data in memory
 * @param size The size of the texture data in bytes
 * @return A texture_t struct containing the loaded texture and its dimensions, or a struct with NULL texture on failure
*/
texture_t gfx_load_texture_ex(const u8* data, const size_t size);

/**
 * @brief Loads a texture from memory data, reusing a previously loaded texture if the same data pointer was already loaded through this function.
 * Useful when many entities share one source asset (e.g. several enemies of the same sprite).
 * 
 * @param data The pointer to the texture data in memory, used as the cache key
 * @param size The size of the texture data in bytes
 * @return A texture_t struct containing the shared texture and its dimensions, or a struct with NULL texture on failure
*/
texture_t gfx_load_texture_cached(const u8* data, const size_t size);

/**
 * @brief Destroys every texture loaded through gfx_load_texture_cached and empties the cache.
 * Call this when unloading a scene that used the cache.
*/
void gfx_clear_texture_cache(void);

/**
 * @brief Creates a texture from text using a font loaded from memory.
 * @param data The pointer to the font data in memory
 * @param size The size of the font data in bytes
 * @param text The text to render
 * @param text_size The size of the text (font size)
 * @param color The color of the text
 * @return A pointer to the created SDL_Texture, or NULL on failure
*/
SDL_Texture* gfx_create_text(const u8* data, const size_t size, const char* text, u8 text_size, color_t color);

/**
 * @brief Gets the size of a texture as an SDL_Rect.
 * @param texture The texture to query
 * @return An SDL_Rect containing the width and height of the texture
*/
SDL_Rect gfx_get_texture_size(SDL_Texture* texture);

/**
 * @brief Gets the size of a texture as an SDL_FRect.
 * @param texture The texture to query
 * @return An SDL_FRect containing the width and height of the texture
*/    
SDL_FRect gfx_get_texture_fsize(SDL_Texture* texture);

/**
 * @brief Renders a texture at the specified position and size.
 * @param texture The texture to render
 * @param x The X coordinate of the top-left corner
 * @param y The Y coordinate of the top-left corner
 * @param w The width to render the texture
 * @param h The height to render the texture
*/
void gfx_render_texture(SDL_Texture* texture, i32 x, i32 y, i32 w, i32 h);

/**
 * @brief Renders a texture at the specified position and size with rotation.
 * @param texture The texture to render
 * @param x The X coordinate of the top-left corner
 * @param y The Y coordinate of the top-left corner
 * @param w The width to render the texture
 * @param h The height to render the texture
 * @param angle The rotation angle in degrees
*/
void gfx_render_texture_rotated(SDL_Texture* texture, i32 x, i32 y, i32 w, i32 h, double angle);

/**
 * @brief Draws a line between two points with the specified color.
 * @param x0 The X coordinate of the starting point
 * @param y0 The Y coordinate of the starting point
 * @param x1 The X coordinate of the ending point
 * @param y1 The Y coordinate of the ending point
 * @param color The color of the line 
*/
void gfx_draw_line(i32 x0, i32 y0, i32 x1, i32 y1, color_t color);

/**
 * @brief Draws a circle with the specified center, radius, and color.
 * @param cx The X coordinate of the center
 * @param cy The Y coordinate of the center
 * @param radius The radius of the circle
 * @param color The color of the circle
*/
void gfx_draw_circle(i32 cx, i32 cy, i32 radius, color_t color);

/**
 * @brief Draws a filled circle with the specified center, radius, and color.
 * @param cx The X coordinate of the center
 * @param cy The Y coordinate of the center
 * @param radius The radius of the circle
 * @param color The color of the circle
*/
void gfx_draw_fill_circle(i32 cx, i32 cy, i32 radius, color_t color);

/**
 * @brief Draws a dashed circle with the specified center, radius, dash length, and color.
 * @param cx The X coordinate of the center
 * @param cy The Y coordinate of the center
 * @param radius The radius of the circle
 * @param dash_length The length of each dash
 * @param color The color of the circle
*/
void gfx_draw_dashed_circle(i32 cx, i32 cy, i32 radius, i32 dash_length, color_t color);

/**
 * @brief Draws a rectangle with the specified dimensions and color.
 * @param rect The SDL_Rect defining the rectangle
 * @param color The color of the rectangle
*/
void gfx_draw_box(SDL_Rect rect, color_t color);

/**
 * @brief Draws a rectangle with floating-point dimensions and the specified color.
 * @param rect The SDL_FRect defining the rectangle
 * @param color The color of the rectangle
*/
void gfx_draw_fbox(SDL_FRect rect, color_t color);

/**
 * @brief Draws a filled rectangle with the specified dimensions and color.
 * @param rect The SDL_Rect defining the rectangle
 * @param color The color of the rectangle
 */
void gfx_draw_fill_box(SDL_Rect rect, color_t color);

/**
 * @brief Draws a filled rectangle with floating-point dimensions and the specified color.
 * @param rect The SDL_FRect defining the rectangle
 * @param color The color of the rectangle
*/
void gfx_draw_fill_fbox(SDL_FRect rect, color_t color);

/**
 * @brief Draws a triangle with the specified vertices and color.
 * @param x1 The X coordinate of the first vertex
 * @param y1 The Y coordinate of the first vertex
 * 
 * @param x2 The X coordinate of the second vertex
 * @param y2 The Y coordinate of the second vertex
 * 
 * @param x3 The X coordinate of the third vertex
 * @param y3 The Y coordinate of the third vertex
 * 
 * @param color The color of the triangle
*/
void gfx_draw_triangle(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, color_t color);
