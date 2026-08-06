/**
 * @file credit_screen.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../app.h"
#include "../de-wii/gfx/scene.h"

void credits_screen_init(void);
void credits_screen_load(void);
void credits_screen_input(void);
void credits_screen_update(void);
void credits_screen_render(void);
u8   credits_screen_run(void);
void credits_screen_unload(void);

scene_t* credits_screen_get_scene(void);
