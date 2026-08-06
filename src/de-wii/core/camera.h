/**
 * @file camera.h
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
 * @brief structure representing the viewport and background color.
*/
typedef struct {
    i16 x;
    i16 y;
    i16 w;
    i16 h;
    color_t color;
} camera_t;

/**
 * @brief Creates a new camera with the specified color.
 * @param color The background color of the camera
 * @return A new camera instance
*/
camera_t camera_new(color_t color);
