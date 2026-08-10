/**
 * @file menu_screen.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../app.h"
#include "../de-wii/gfx/scene.h"

void     menu_screen_init(void);
void     menu_screen_load(void);
void     menu_screen_input(void);
void     menu_screen_update(void);
void     menu_screen_render(void);
u8       menu_screen_run(void);
void     menu_screen_unload(void);
scene_t* menu_screen_get_scene(void);
