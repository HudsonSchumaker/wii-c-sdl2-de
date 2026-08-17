/**
 * @file transform_component.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_TRANSFORM_COMPONENT_H
#define DE_TRANSFORM_COMPONENT_H

#include "../de.h"

/**
 * @brief A transform pool that holds the position, scale, and rotation for all entities.
*/
typedef struct {
    f32 px[MAX_ENTITIES];
    f32 py[MAX_ENTITIES];
    f32 sx[MAX_ENTITIES];
    f32 sy[MAX_ENTITIES];
    i32 ra[MAX_ENTITIES];
    i8  zi[MAX_ENTITIES]; 
} transform_pool_t;

#endif // DE_TRANSFORM_COMPONENT_H
