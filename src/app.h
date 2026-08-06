/**
 * @file app.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "de-wii/de.h"

typedef enum {
    SCENE_EXIT = 0,
    SCENE_SPLASH,
    SCENE_GAME,
    SCENE_CREDITS
} scene_id_e;

/**
 * @brief Starts the application by initializing the engine, running the splash screen,
 * title screen, menu screen, and credits screen, and then quitting the engine.
*/
void app_start(void);
