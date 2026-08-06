/**
 * @file game_screen.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../app.h"
#include "../de-wii/gfx/scene.h"

void game_screen_init(void);
void game_screen_load(void);
void game_screen_input(void);
void game_screen_update(void);
void game_screen_render(void);
u8   game_screen_run(void);
void game_screen_unload(void);

scene_t* game_screen_get_scene(void);
