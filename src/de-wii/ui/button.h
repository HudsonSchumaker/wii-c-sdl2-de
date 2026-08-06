/**
 * @file button.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../de.h"

/**
 * Represents a button with properties for position, size, visibility, associated gamepad button, texture, and an onclick callback function.
*/
typedef void (*button_onclick_callback_t)(void);
typedef struct {
    i32 x;
    i32 y;
    i32 w;
    i32 h;
    bool visible;
    u8 pad_button;
    SDL_Texture* texture;
    button_onclick_callback_t onclick;
} button_t;

/**
 * Creates a new button with the specified position. The button will be initialized with default properties such as size, visibility, and no associated gamepad button or onclick callback.
 * @param x The X coordinate of the button
 * @param y The Y coordinate of the button
 * @return A button_t struct initialized with the provided position and default properties
*/
button_t button(i32 x, i32 y);

/**
 * Creates a new button on the heap with the specified position. The button will be initialized with default properties such as size, visibility, and no associated gamepad button or onclick callback.
 * @param x The X coordinate of the button
 * @param y The Y coordinate of the button
 * @return A pointer to a newly allocated button_t struct initialized with the provided position and default properties
*/
button_t* button_new(i32 x, i32 y);

/**
 * Destroys a button created with button_new. This will destroy its texture (if set) and free the button itself.
 * @param btn Pointer to the heap-allocated button_t struct to destroy
*/
void button_destroy(button_t* btn);

/**
 * Sets the source texture of the button. This will update the button's texture with the provided data and also update its width and height based on the texture's dimensions.
 * @param btn Pointer to the button_t struct to modify
 * @param data Pointer to the texture data in memory
 * @param size Size of the texture data in bytes
*/
void button_set_source(button_t* btn, const u8* data, size_t size);

/**
 * Sets the onclick callback function of the button. This will be called when the button is clicked.
 * @param btn Pointer to the button_t struct to modify
 * @param callback The callback function to set for the button
*/
void button_set_onclick(button_t* btn, button_onclick_callback_t callback);

/**
 * Renders the button on the screen. This will draw the button using its current properties such as texture, size, and visibility.
 * @param btn Pointer to the button_t struct to render
*/
void button_render(const button_t* btn);
