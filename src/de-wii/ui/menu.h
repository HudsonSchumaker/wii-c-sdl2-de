/**
 * @file menu.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_MENU_H
#define DE_MENU_H

#include "../de.h"
#include "label.h"
#include "../gfx/color.h"

#define MENU_MAX_ITEMS 8
typedef void (*menu_callback_t)(void);

/**
 * @brief A vertical list of text items navigable with the GameCube D-pad.
 *
 * Call menu_add_item() for each entry, then drive it each frame with
 * menu_handle_input() (after input_update()) and menu_render().
 * Release resources with menu_release() when the screen unloads.
*/
typedef struct {
    label_t         items[MENU_MAX_ITEMS];
    menu_callback_t callbacks[MENU_MAX_ITEMS];
    i8              count;
    i8              selected;
    color_t         highlight;  // fill color of the selection rectangle
    u16             pad_up;
    u16             pad_down;
    u16             pad_confirm;
} menu_t;

/**
 * @brief Creates a menu with D-pad navigation wired to GameCube PAD button masks.
 * @param pad_up      PAD button mask to move selection up   (e.g. PAD_BUTTON_UP)
 * @param pad_down    PAD button mask to move selection down (e.g. PAD_BUTTON_DOWN)
 * @param pad_confirm PAD button mask to confirm selection   (e.g. PAD_BUTTON_A)
 * @return An initialized menu_t value
*/
menu_t menu_create(u16 pad_up, u16 pad_down, u16 pad_confirm);

/**
 * @brief Appends a labeled item to the menu.
 * @param m               Pointer to the menu
 * @param x               X coordinate of the label (use label_set_horizontal_center() after to center it)
 * @param y               Y coordinate of the label
 * @param text            Display text
 * @param font_size       Point size for the text
 * @param font_data       Pointer to the embedded TTF data
 * @param font_size_bytes Size of the TTF data in bytes
 * @param cb              Callback invoked when this item is confirmed; may be NULL
*/
void menu_add_item(menu_t* m, i32 x, i32 y, const char* text,
                   u8 font_size, const u8* font_data, size_t font_size_bytes,
                   menu_callback_t cb);

/**
 * @brief Reads input from port 0 and either moves the selection or fires the active callback.
 * @note  Call input_update() before this each frame.
 * @param m Pointer to the menu
*/
void menu_handle_input(menu_t* m);

/**
 * @brief Renders all items, drawing a semi-transparent highlight behind the selected one.
 * @param m Pointer to the menu
*/
void menu_render(menu_t* m);

/**
 * @brief Releases all textures owned by the menu's labels. Does not free the menu struct itself.
 * @param m Pointer to the menu
*/
void menu_release(menu_t* m);

#endif // DE_MENU_H
