/**
 * @file animation.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "animation.h"

animation_t animation_create(i8 number_frames, i8 frame_speed_rate, bool is_loop) {
    animation_t animation = {0};
    animation.start_time = 0;
    animation.flip = false;
    animation.is_loop = is_loop;
    animation.is_fixed = false;
    animation.is_playing = false;
    animation.number_frames = number_frames;
    animation.current_frame = 0;
    animation.skip_frame_index = 0;
    animation.frame_speed_rate = frame_speed_rate;

    return animation;
}

animation_t* animation_create_new(i8 number_frames, i8 frame_speed_rate, bool is_loop) {
    animation_t* animation = (animation_t *)malloc(sizeof(animation_t));
    *animation = animation_create(number_frames, frame_speed_rate, is_loop);
    return animation;
}

void animation_play(animation_t* animation) {
    if (animation)
    {
        animation->is_playing = true;
        animation->start_time = 0;
    }
}

void animation_stop(animation_t* animation) {
    if (animation) {
        animation->is_playing = false;
    }
}

void animation_update(animation_t* animation) {
    if (!animation || !animation->is_playing || animation->is_fixed || animation->frame_speed_rate <= 0) {
        return;
    }

    u64 now = SDL_GetTicks();
    if (animation->start_time == 0) {
        animation->start_time = now;
    }

    i32 frame = (i32)((now - animation->start_time) / (u64)animation->frame_speed_rate);
    if (frame >= animation->number_frames) {
        if (animation->is_loop) {
            frame = frame % animation->number_frames;
        } else {
            frame = animation->number_frames - 1;
            animation->is_playing = false;
        }
    }
    animation->current_frame = (i8)frame;
}
