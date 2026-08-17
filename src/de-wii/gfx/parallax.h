/**
 * @file parallax.h 
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_PARALLAX_H
#define DE_PARALLAX_H

#include "../de.h"

/**
 * @brief Represents a vertical parallax effect with background and foreground layers.
*/
typedef struct {
	SDL_Texture* background;
	SDL_Texture* texture;
	SDL_Rect bg_rect;
	SDL_Rect rect_a;
	SDL_Rect rect_b;
	SDL_Point size;
	i8 direction; // 1 for down, -1 for up
} parallax_vertical_t;

/**
 * @brief Represents a horizontal parallax effect with background and foreground layers.
*/
typedef struct {
	SDL_Texture* background;
	SDL_Texture* texture;
	SDL_Rect bg_rect;
	SDL_Rect rect_a;
	SDL_Rect rect_b;
	SDL_Point size;
	i8 direction; // 1 for right, -1 for left
} parallax_horizontal_t;

/**
 * @brief Creates a simple vertical parallax effect using the provided parallax texture data.
 * @param parallax_data Pointer to the parallax texture data in memory
 * @param parallax_size Size of the parallax texture data in bytes
 * @return A parallax_vertical_t struct initialized with the loaded texture and rectangles
*/
parallax_vertical_t parallax_vertical_simple(const u8* parallax_data, const size_t parallax_size);

/**
 * @brief Creates a vertical parallax effect with a background layer and a foreground layer using the provided texture data.
 * @param bg_data Pointer to the background texture data in memory
 * @param bg_size Size of the background texture data in bytes
 * @param parallax_data Pointer to the parallax texture data in memory
 * @param parallax_size Size of the parallax texture data in bytes
 * @return A parallax_vertical_t struct initialized with the loaded textures and rectangles
*/
parallax_vertical_t parallax_vertical_double(const u8* bg_data, const size_t bg_size, const u8* parallax_data, const size_t parallax_size);

/**
 * @brief Creates a new parallax_vertical_t struct on the heap using the simple parallax effect.
 * @param parallax_data Pointer to the parallax texture data in memory
 * @param parallax_size Size of the parallax texture data in bytes
 * @return A pointer to a newly allocated parallax_vertical_t struct initialized with the loaded texture and rectangles
*/
parallax_vertical_t* parallax_vertical_simple_new(const u8* parallax_data, const size_t parallax_size);

/**
 * @brief Creates a new parallax_vertical_t struct on the heap using the double parallax effect.
 * @param bg_data Pointer to the background texture data in memory
 * @param bg_size Size of the background texture data in bytes
 * @param parallax_data Pointer to the parallax texture data in memory
 * @param parallax_size Size of the parallax texture data in bytes
 * @return A pointer to a newly allocated parallax_vertical_t struct initialized with the loaded textures and rectangles
*/
parallax_vertical_t* parallax_vertical_double_new(const u8* bg_data, const size_t bg_size, const u8* parallax_data, const size_t parallax_size);

/**
 * @brief Updates the vertical parallax effect by moving the foreground rectangles and resetting their positions when they move off-screen.
 * @param parallax Pointer to the parallax_vertical_t struct to update
*/
void parallax_vertical_update(parallax_vertical_t* parallax);

/**
 * @brief Renders the vertical parallax effect by drawing the background and foreground layers to the screen.
 * @param parallax Pointer to the parallax_vertical_t struct to render
*/
void parallax_vertical_render(const parallax_vertical_t* parallax);

/**
 * @brief Creates a simple horizontal parallax effect using the provided parallax texture data.
 * @param parallax_data Pointer to the parallax texture data in memory
 * @param parallax_size Size of the parallax texture data in bytes
 * @return A parallax_horizontal_t struct initialized with the loaded texture and rectangles
*/
parallax_horizontal_t parallax_horizontal_simple(const u8* parallax_data, const size_t parallax_size);

/**
 * @brief Creates a horizontal parallax effect with a background layer and a foreground layer using the provided texture data.
 * @param bg_data Pointer to the background texture data in memory
 * @param bg_size Size of the background texture data in bytes
 * @param parallax_data Pointer to the parallax texture data in memory
 * @param parallax_size Size of the parallax texture data in bytes
 * @return A parallax_horizontal_t struct initialized with the loaded textures and rectangles
*/
parallax_horizontal_t parallax_horizontal_double(const u8* bg_data, const size_t bg_size, const u8* parallax_data, const size_t parallax_size);

/**
 * @brief Creates a new parallax_horizontal_t struct on the heap using the simple parallax effect.
 * @param parallax_data Pointer to the parallax texture data in memory
 * @param parallax_size Size of the parallax texture data in bytes
 * @return A pointer to a newly allocated parallax_horizontal_t struct initialized with the loaded texture and rectangles
*/
parallax_horizontal_t* parallax_horizontal_simple_new(const u8* parallax_data, const size_t parallax_size);

/**
 * @brief Creates a new parallax_horizontal_t struct on the heap using the double parallax effect.
 * @param bg_data Pointer to the background texture data in memory
 * @param bg_size Size of the background texture data in bytes
 * @param parallax_data Pointer to the parallax texture data in memory
 * @param parallax_size Size of the parallax texture data in bytes
 * @return A pointer to a newly allocated parallax_horizontal_t struct initialized with the loaded textures and rectangles
*/
parallax_horizontal_t* parallax_horizontal_double_new(const u8* bg_data, const size_t bg_size, const u8* parallax_data, const size_t parallax_size);

/**
 * @brief Updates the horizontal parallax effect by moving the foreground rectangles and resetting their positions when they move off-screen.
 * @param parallax Pointer to the parallax_horizontal_t struct to update
*/
void parallax_horizontal_update(parallax_horizontal_t* parallax);

/**
 * @brief Renders the horizontal parallax effect by drawing the background and foreground layers to the screen.
 * @param parallax Pointer to the parallax_horizontal_t struct to render
*/
void parallax_horizontal_render(const parallax_horizontal_t* parallax);

/**
 * @brief Destroys the parallax_vertical_t struct by freeing the associated textures and memory.
 * @param parallax Pointer to the parallax_vertical_t struct to destroy
*/
void parallax_vertical_destroy(parallax_vertical_t* parallax);

/**
 * @brief Destroys the parallax_horizontal_t struct by freeing the associated textures and memory.
 * @param parallax Pointer to the parallax_horizontal_t struct to destroy
*/
void parallax_horizontal_destroy(parallax_horizontal_t* parallax);

#endif // DE_PARALLAX_H
