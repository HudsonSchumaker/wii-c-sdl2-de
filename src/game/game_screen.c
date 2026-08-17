/**
 * @file game_screen.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "game_screen.h"
#include "../de-wii/gfx/gfx.h"
#include "../de-wii/core/engine.h"
#include "../de-wii/core/camera.h"
#include "../de-wii/core/context.h"
#include "../de-wii/ecs/entity_manager.h"
#include "../de-wii/ecs/render_system.h"
#include "logo_png.h"
#include "de-128_png.h"
#include "hoshi-move-right_png.h"

static bool running = false;
static scene_t* game_screen = NULL;
static u8 next_screen = SCENE_CREDITS;
static entity_t hoshi;

void game_screen_init(void) {
    game_screen = scene_init();

    game_screen->load = game_screen_load;
    game_screen->input = game_screen_input;
    game_screen->update = game_screen_update;
    game_screen->render = game_screen_render;
    game_screen->run = game_screen_run;
    game_screen->unload = game_screen_unload;
}

void game_screen_load(void) {
    game_screen->camera.color = color_white();

    entity_manager_t* em = engine_get_entity_manager();
    hoshi = entity_create(em);

    transform_pool_t* transform_pool = engine_get_transform_pool();
    transform_pool->px[hoshi] = H_WINDOW_WIDTH - 16.0f;
    transform_pool->py[hoshi] = H_WINDOW_HEIGHT - 16.0f;
    transform_pool->sx[hoshi] = 1.0f;
    transform_pool->sy[hoshi] = 1.0f;
    transform_pool->ra[hoshi] = 0.0f;
    transform_pool->zi[hoshi] = 1;

    animation_controller_pool_t* anim = engine_get_animation_controller_pool();
    animation_controller_add(anim, hoshi, "move-right", hoshi_move_right_png, hoshi_move_right_png_size, 8, 100, true);
    animation_controller_play(anim, hoshi);

    running = true;
}

void game_screen_input(void) {
    PAD_ScanPads();
    u16 down = PAD_ButtonsDown(0);

    if (down & PAD_BUTTON_A) {
        next_screen = SCENE_CREDITS;
        running = false;
        return;
    }
}

void game_screen_update(void) {
    engine_calculate_delta_time();
    animation_system(engine_get_animation_controller_pool(), engine_get_texture_pool());
}

void game_screen_render(void) {
    scene_begin_render();
    {
        render_system(engine_get_transform_pool(), engine_get_texture_pool(), &game_screen->camera);
    }
    scene_end_render();
}

u8 game_screen_run(void) {
    while (running) {
        game_screen_input();
        game_screen_update();
        game_screen_render();
    }
    return next_screen;
}

void game_screen_unload(void) {
    animation_controller_clear(engine_get_animation_controller_pool(), hoshi);
    entity_destroy(engine_get_entity_manager(), hoshi);

    free(game_screen);
    game_screen = NULL;
}

scene_t* game_screen_get_scene(void) {
    return game_screen;
}
