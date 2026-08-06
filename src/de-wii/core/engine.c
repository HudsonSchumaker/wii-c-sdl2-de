/**
 * @file engine.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "engine.h"
#include "context.h"
#include "../math/math2d.h"

static f32 delta_time = 0.0f;
static texture_pool_t texture_pool;
static entity_manager_t entity_manager;
static transform_pool_t transform_pool;
static animation_controller_pool_t animation_controller_pool;

void engine_init(void) {
    if (ctx_init() != 0) {
        exit(EXIT_FAILURE);
    }

    PAD_Init();
    build_trigo_tables();
    entity_manager_init(&entity_manager);
    animation_controller_pool_init(&animation_controller_pool);
}

void engine_quit(void) {
    ctx_quit();
}

f32 engine_calculate_delta_time(void) {
    static u64 frequency = 0;
    static u64 last_counter = 0;
    static f32 smooth_dt = 0.0f;

    const f32 MAX_DT = 0.25f;
    const f32 SMOOTH_ALPHA = 0.08f;

    if (frequency == 0) {
        frequency = SDL_GetPerformanceFrequency();
    }
    u64 now = SDL_GetPerformanceCounter();

    if (last_counter == 0) {
        last_counter = now;
        return 0.0f;
    }

    f32 dt = (f32)(now - last_counter) / (f32)frequency;
    last_counter = now;

    if (dt < 0.0f) {
        dt = 0.0f;
    }

    if (dt > MAX_DT) {
        dt = MAX_DT;
    }

    if (smooth_dt == 0.0f) {
        smooth_dt = dt;
    } else {
        smooth_dt += SMOOTH_ALPHA * (dt - smooth_dt);
    }

    delta_time = smooth_dt;
    return delta_time;
}

f32 engine_get_delta_time(void) {
    return delta_time;
}

entity_manager_t* engine_get_entity_manager(void) {
    return &entity_manager;
}

transform_pool_t* engine_get_transform_pool(void) {
    return &transform_pool;
}

texture_pool_t* engine_get_texture_pool(void) {
    return &texture_pool;
}

animation_controller_pool_t* engine_get_animation_controller_pool(void) {
    return &animation_controller_pool;
}
