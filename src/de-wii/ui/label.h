/**
 * @file label.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#pragma once
#include "../de.h"
#include "../gfx/color.h"

/**
 * Represents a text label with properties for position, size, visibility, color, font size, and texture.
 */
typedef struct {
    char *text;
    i32 x;
    i32 y;
    i32 w;
    i32 h;
    bool visible;
    color_t color;
    u8 font_size;
    SDL_Texture* texture;
} label_t;

/**
 * Creates a new label with the specified position and text. The label will be initialized with default properties such as font size, color, and visibility.
 * @param x The X coordinate of the label
 * @param y The Y coordinate of the label
 * @param text The text to display on the label
 * @return A label_t struct initialized with the provided position and text, and default properties
 */
label_t label(i32 x, i32 y, const char* text);

/**
 * Creates a new label on the heap with the specified position and text. The label will be initialized with default properties such as font size, color, and visibility.
 * @param x The X coordinate of the label
 * @param y The Y coordinate of the label
 * @param text The text to display on the label
 * @return A pointer to a newly allocated label_t struct initialized with the provided position and text, and default properties
 */
label_t* label_new(i32 x, i32 y, const char* text);

/**
 * Destroys a label created with label_new. This will destroy its texture (if set), free its text, and free the label itself.
 * @param lbl Pointer to the heap-allocated label_t struct to destroy
 */
void label_destroy(label_t* lbl);

/**
 * Sets the color of the label's text. This will affect how the label is rendered on the screen.
 * @param lbl Pointer to the label_t struct to modify
 * @param color The new color to set for the label's text
 */
void label_set_color(label_t* lbl, color_t color);

/**
 * Sets the font size of the label and updates its texture accordingly. This will change how the label's text is rendered on the screen.
 * @param lbl Pointer to the label_t struct to modify
 * @param font_size The new font size to set for the label
 * @param data Pointer to the font data in memory
 * @param size Size of the font data in bytes
 */
void label_set_font_size(label_t* lbl, u8 font_size, const u8* data, size_t size);

/**
 * Renders the label on the screen. This will draw the label's text using its current properties such as color, font size, and visibility.
 * @param lbl Pointer to the label_t struct to render
 */
void label_render(const label_t* lbl);

/**
 * Centers the label on the screen. This will adjust the label's position so that it is centered both horizontally and vertically.
 * @param lbl Pointer to the label_t struct to modify
 */
void label_set_on_center(label_t* lbl);

/**
 * Centers the label horizontally on the screen. This will adjust the label's X position so that it is centered horizontally.
 * @param lbl Pointer to the label_t struct to modify
 */
void label_set_horizontal_center(label_t* lbl);

/**
 * Updates the text of a label and regenerates its texture using the label's current font size.
 * @param lbl Pointer to the label_t struct to modify
 * @param text The new text to display on the label
 * @param data Pointer to the font data in memory
 * @param size Size of the font data in bytes
 */
void label_set_text(label_t* lbl, const char* text, const u8* data, size_t size);

/**
 * Releases the texture and text owned by a label without freeing the label struct itself. Use this for stack or statically allocated labels created with label(), as opposed to label_destroy() which is for labels created with label_new().
 * @param lbl Pointer to the label_t struct to release
 */
void label_release(label_t* lbl);
