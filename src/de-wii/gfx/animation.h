/**
 * @file animation.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#ifndef DE_ANIMATION_H
#define DE_ANIMATION_H

#include "../de.h"

typedef struct {
    u64 start_time;
    bool flip;
    bool is_loop;
    bool is_fixed;
    bool is_playing;
    i8 number_frames;
    i8 current_frame;
    i8 skip_frame_index;
    i8 frame_speed_rate;
} animation_t;

animation_t animation_create(i8 number_frames, i8 frame_speed_rate, bool is_loop);
animation_t *animation_create_new(i8 number_frames, i8 frame_speed_rate, bool is_loop);

void animation_play(animation_t *animation);
void animation_stop(animation_t *animation);

/**
 * @brief Advances current_frame based on elapsed ticks since the animation started playing.
 * Stops the animation on the last frame when is_loop is false.
 * @param animation A pointer to the animation to update.
 */
void animation_update(animation_t* animation);

#endif // DE_ANIMATION_H
