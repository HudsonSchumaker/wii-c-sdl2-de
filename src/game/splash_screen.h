/**
* @file splash_screen.h
* @author Hudson Schumaker
* @version 1.0.0
*
* Dodoi-Engine is a game engine developed by Dodoi-Lab.
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../app.h"
#include "../de-wii/gfx/scene.h"

void splash_screen_init(void);
void splash_screen_load(void);
void splash_screen_input(void);
void splash_screen_update(void);
void splash_screen_render(void);
u8   splash_screen_run(void);
void splash_screen_unload(void);

scene_t* splash_screen_get_scene(void);
