/**
 * @file render_system.h
 * @author Hudson Schumaker
 * @version 1.0.0
 * 
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_RENDER_SYSTEM_H
#define DE_RENDER_SYSTEM_H

#include "../de.h"
#include "../core/camera.h"
#include "texture_component.h"
#include "transform_component.h"

/**
 * @brief Renders entities with transform and texture components.
 * @param t A pointer to the transform pool
 * @param r A pointer to the texture pool
 * @param c A pointer to the camera
*/
void render_system(transform_pool_t* t, texture_pool_t* r, camera_t* c);

#endif // DE_RENDER_SYSTEM_H
