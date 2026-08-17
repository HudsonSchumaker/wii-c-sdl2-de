/**
 * @file animation_controller.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#ifndef DE_ANIMATION_CONTROLLER_H
#define DE_ANIMATION_CONTROLLER_H

#include "../de.h"
#include "../gfx/animation.h"
#include "entity_manager.h"
#include "texture_component.h"

#define MAX_ANIMATIONS_PER_ENTITY 8
#define MAX_ANIMATION_NAME_LEN 16

/**
 * @brief A named animation clip: a horizontal sprite-strip texture sliced into equal frames.
 */
typedef struct {
    char name[MAX_ANIMATION_NAME_LEN];
    SDL_Texture *texture;
    i32 frame_w;
    i32 frame_h;
    i8 number_frames;
    i8 frame_speed_rate;
    bool is_loop;
} animation_clip_t;

/**
 * @brief An animation controller pool that holds the animation clips and playback state for all entities.
 */
typedef struct {
    animation_clip_t clips[MAX_ENTITIES][MAX_ANIMATIONS_PER_ENTITY];
    i8 clip_count[MAX_ENTITIES];
    i8 active_clip[MAX_ENTITIES]; // index into clips[e], or -1 if none
    animation_t state[MAX_ENTITIES];
} animation_controller_pool_t;

/**
 * @brief Initializes the animation controller pool, clearing all clips and playback state.
 * @param pool A pointer to the animation controller pool to initialize.
 */
void animation_controller_pool_init(animation_controller_pool_t* pool);

/**
 * @brief Creates a clip from a horizontal sprite-strip texture and adds it to an entity. The first clip added becomes the active one.
 * @param pool A pointer to the animation controller pool.
 * @param e The entity to add the clip to.
 * @param name The name used to look up the clip later.
 * @param data The pointer to the sprite-strip PNG data in memory.
 * @param size The size of the PNG data in bytes.
 * @param number_frames The number of equal-width frames in the strip.
 * @param frame_speed_rate The time in milliseconds each frame is shown.
 * @param is_loop Whether the animation should loop.
 * @return The clip index, or -1 on failure.
 */
i8 animation_controller_add(animation_controller_pool_t* pool, entity_t e, string_t name, const u8* data, size_t size, i8 number_frames, i8 frame_speed_rate, bool is_loop);

/**
 * @brief Plays the currently active clip for an entity from the start.
 */
void animation_controller_play(animation_controller_pool_t* pool, entity_t e);

/**
 * @brief Makes the named clip active and plays it from the start.
 */
void animation_controller_play_by_name(animation_controller_pool_t* pool, entity_t e, string_t name);

/**
 * @brief Makes the clip at the given index active and plays it from the start.
 */
void animation_controller_play_by_index(animation_controller_pool_t* pool, entity_t e, i8 index);

/**
 * @brief Stops the entity's active clip on its current frame.
 */
void animation_controller_stop(animation_controller_pool_t* pool, entity_t e);

/**
 * @brief Sets whether the entity's active clip is rendered horizontally flipped.
 */
void animation_controller_set_flip(animation_controller_pool_t* pool, entity_t e, bool flip);

/**
 * @brief Gets the name of the entity's active clip.
 * @return The clip name, or NULL if the entity has no active clip.
 */
string_t animation_controller_get_active_name(animation_controller_pool_t* pool, entity_t e);

/**
 * @brief Destroys all clip textures owned by an entity and resets its playback state. Call this when an entity or scene is unloaded.
 * @param pool A pointer to the animation controller pool.
 * @param e The entity to clear.
 */
void animation_controller_clear(animation_controller_pool_t* pool, entity_t e);

/**
 * @brief Advances playback for every entity with an active clip and syncs the result into the texture pool.
 * @param pool A pointer to the animation controller pool.
 * @param textures A pointer to the texture pool to update with the current frame's texture and source rect.
 */
void animation_system(animation_controller_pool_t* pool, texture_pool_t* textures);

#endif // DE_ANIMATION_CONTROLLER_H
