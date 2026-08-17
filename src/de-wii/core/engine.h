/**
 * @file engine.h
 * @author Hudson Schumaker
 * @brief Implements the core engine functions, including initialization, quitting, and delta time calculation.
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#ifndef DE_ENGINE_H
#define DE_ENGINE_H

#include "../de.h"
#include "../ecs/entity_manager.h"
#include "../ecs/texture_component.h"
#include "../ecs/transform_component.h"
#include "../ecs/animation_controller.h"

/**
 * @brief Initializes the engine and its subsystems.
 */
void engine_init(void);

/**
 * @brief Quits the engine and cleans up resources.
 */
void engine_quit(void);

/**
 * @brief Gets the time elapsed since the last frame in seconds.
 * @return The delta time in seconds
 */
f32 engine_get_delta_time(void);

/**
 * @brief Calculates the time elapsed since the last frame and updates the delta time.
 * @return The calculated delta time in seconds
 */
f32 engine_calculate_delta_time(void);

/**
 * @brief Gets the entity manager instance.
 * @return A pointer to the entity manager
 */
entity_manager_t* engine_get_entity_manager(void);

/**
 * @brief Gets the transform pool instance.
 * @return A pointer to the transform pool
 */
transform_pool_t* engine_get_transform_pool(void);

/**
 * @brief Gets the texture pool instance.
 * @return A pointer to the texture pool
 */
texture_pool_t* engine_get_texture_pool(void);

/**
 * @brief Gets the animation controller pool instance.
 * @return A pointer to the animation controller pool
 */
animation_controller_pool_t* engine_get_animation_controller_pool(void);

#endif // DE_ENGINE_H
