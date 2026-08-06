/**
 * @file texture_component.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#pragma once
#include "../de.h"

/**
 * @brief A texture pool that holds the textures and their dimensions for all entities.
 * @note src is the source rect sampled from texture; a zero-sized src means "use the whole texture".
 */
typedef struct {
    i32 w[MAX_ENTITIES];
    i32 h[MAX_ENTITIES];
    SDL_Texture* texture[MAX_ENTITIES];
    SDL_Rect src[MAX_ENTITIES];
    bool flip[MAX_ENTITIES];
} texture_pool_t;
