/**
 * @file animation_controller.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "animation_controller.h"
#include "../core/engine.h"
#include "../gfx/gfx.h"
#include <string.h>

void animation_controller_pool_init(animation_controller_pool_t* pool) {
    memset(pool, 0, sizeof(animation_controller_pool_t));
    for (entity_t e = 0; e < MAX_ENTITIES; e++) {
        pool->active_clip[e] = -1;
    }
}

i8 animation_controller_add(animation_controller_pool_t* pool, entity_t e, const char* name, const u8* data, size_t size, i8 number_frames, i8 frame_speed_rate, bool is_loop) {
    if (e >= MAX_ENTITIES || number_frames <= 0 || pool->clip_count[e] >= MAX_ANIMATIONS_PER_ENTITY) {
        return -1;
    }

    texture_t texture = gfx_load_texture_ex(data, size);
    if (!texture.texture) {
        return -1;
    }

    i8 index = pool->clip_count[e];
    animation_clip_t *clip = &pool->clips[e][index];
    strncpy(clip->name, name, MAX_ANIMATION_NAME_LEN - 1);
    clip->name[MAX_ANIMATION_NAME_LEN - 1] = '\0';
    clip->texture = texture.texture;
    clip->number_frames = number_frames;
    clip->frame_w = texture.w / number_frames;
    clip->frame_h = texture.h;
    clip->frame_speed_rate = frame_speed_rate;
    clip->is_loop = is_loop;

    pool->clip_count[e] = index + 1;
    if (pool->active_clip[e] < 0) {
        pool->active_clip[e] = index;
    }
    return index;
}

static void animation_controller_sync_texture(animation_controller_pool_t* pool, texture_pool_t* textures, entity_t e) {
    i8 index = pool->active_clip[e];
    if (index < 0) {
        return;
    }

    animation_clip_t* clip = &pool->clips[e][index];
    animation_t* state = &pool->state[e];

    textures->texture[e] = clip->texture;
    textures->w[e] = clip->frame_w;
    textures->h[e] = clip->frame_h;
    textures->src[e] = (SDL_Rect){state->current_frame * clip->frame_w, 0, clip->frame_w, clip->frame_h};
}

void animation_controller_play(animation_controller_pool_t* pool, entity_t e) {
    if (e < MAX_ENTITIES && pool->active_clip[e] > -1) {
        animation_controller_play_by_index(pool, e, pool->active_clip[e]);
    }
}

void animation_controller_play_by_name(animation_controller_pool_t* pool, entity_t e, const char* name) {
    if (e >= MAX_ENTITIES) {
        return;
    }

    for (i8 i = 0; i < pool->clip_count[e]; i++) {
        if (strncmp(pool->clips[e][i].name, name, MAX_ANIMATION_NAME_LEN) == 0) {
            animation_controller_play_by_index(pool, e, i);
            return;
        }
    }
}

void animation_controller_play_by_index(animation_controller_pool_t* pool, entity_t e, i8 index) {
    if (e >= MAX_ENTITIES || index < 0 || index >= pool->clip_count[e]) {
        return;
    }

    animation_clip_t* clip = &pool->clips[e][index];
    pool->active_clip[e] = index;
    pool->state[e] = animation_create(clip->number_frames, clip->frame_speed_rate, clip->is_loop);
    animation_play(&pool->state[e]);
}

void animation_controller_stop(animation_controller_pool_t* pool, entity_t e) {
    if (e < MAX_ENTITIES) {
        animation_stop(&pool->state[e]);
    }
}

void animation_controller_set_flip(animation_controller_pool_t* pool, entity_t e, bool flip) {
    if (e < MAX_ENTITIES) {
        pool->state[e].flip = flip;
    }
}

const char* animation_controller_get_active_name(animation_controller_pool_t* pool, entity_t e) {
    if (e >= MAX_ENTITIES || pool->active_clip[e] < 0) {
        return NULL;
    }
    return pool->clips[e][pool->active_clip[e]].name;
}

void animation_controller_clear(animation_controller_pool_t* pool, entity_t e) {
    if (e >= MAX_ENTITIES) {
        return;
    }

    for (i8 i = 0; i < pool->clip_count[e]; i++) {
        if (pool->clips[e][i].texture) {
            SDL_DestroyTexture(pool->clips[e][i].texture);
        }
    }

    memset(&pool->clips[e], 0, sizeof(pool->clips[e]));
    memset(&pool->state[e], 0, sizeof(pool->state[e]));
    pool->clip_count[e] = 0;
    pool->active_clip[e] = -1;
}

void animation_system(animation_controller_pool_t* pool, texture_pool_t* textures) {
    entity_manager_t* em = engine_get_entity_manager();

    for (entity_t e = 0; e < MAX_ENTITIES; e++) {
        if (em->alive[e] && pool->active_clip[e] > -1) {
            animation_update(&pool->state[e]);
            textures->flip[e] = pool->state[e].flip;
            animation_controller_sync_texture(pool, textures, e);
        }
    }
}
