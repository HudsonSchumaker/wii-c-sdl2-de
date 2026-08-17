/**
 * @file image.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_IMAGE_H
#define DE_IMAGE_H

#include "../de.h"
#include "../gfx/color.h"

/**
 * Represents an image with properties for position, size, visibility, color tint, and texture.
*/
typedef struct {
    i32 x;
    i32 y;
    i32 w;
    i32 h;
    bool visible;
    color_t color;
    SDL_Texture* texture;
} image_t;

/**
 * Creates a new image with the specified position. The image will be initialized with default properties such as size, visibility, and color tint.
 * @param x The X coordinate of the image
 * @param y The Y coordinate of the image
 * @return An image_t struct initialized with the provided position and default properties
*/
image_t image(i32 x, i32 y);

/**
 * Creates a new image on the heap with the specified position. The image will be initialized with default properties such as size, visibility, and color tint.
 * @param x The X coordinate of the image
 * @param y The Y coordinate of the image
 * @return A pointer to a newly allocated image_t struct initialized with the provided position and default properties
*/
image_t* image_new(i32 x, i32 y);

/**
 * Destroys an image created with image_new. This will destroy its texture (if set) and free the image itself.
 * @param img Pointer to the heap-allocated image_t struct to destroy
*/
void image_destroy(image_t* img);

/**
 * Sets the source texture of the image. This will update the image's texture with the provided data.
 * @param img Pointer to the image_t struct to modify
 * @param data Pointer to the texture data in memory
 * @param size Size of the texture data in bytes
*/
void image_set_source(image_t* img, const u8* data, size_t size);

/**
 * Sets the color tint of the image. This will affect how the image is rendered on the screen.
 * @param img Pointer to the image_t struct to modify
 * @param color The new color tint to set for the image
*/
void image_set_tint(image_t* img, color_t color);

/**
 * Renders the image on the screen. This will draw the image using its current properties such as color tint, size, and visibility.
 * @param img Pointer to the image_t struct to render
*/
void image_render(const image_t* img);

#endif // DE_IMAGE_H
