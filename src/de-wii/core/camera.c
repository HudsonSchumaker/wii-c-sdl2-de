/**
 * @file camera.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "camera.h"

camera_t camera_new(color_t color) {
    camera_t camera;
    camera.x = 0;
    camera.y = 0;
    camera.w = WINDOW_WIDTH;
    camera.h = WINDOW_HEIGHT;
    camera.color = color;
    return camera;
}
