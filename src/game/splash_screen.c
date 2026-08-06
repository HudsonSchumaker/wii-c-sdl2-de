/**
* @file splash_screen.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "splash_screen.h"
#include "../de-wii/gfx/gfx.h"
#include "../de-wii/core/engine.h"
#include "../de-wii/core/context.h"
#include "logo_png.h"
#include "de-128_png.h"

static bool running = false;
scene_t* splash_screen = NULL;
static SDL_Texture* logo_texture = NULL;
static SDL_Texture* dodoi_texture = NULL;
static SDL_Rect logo_rect = {0};
static SDL_Rect dodoi_rect = {0};

void splash_screen_init(void) {
    splash_screen = malloc(sizeof(scene_t));
    if (splash_screen == NULL) {
        exit(EXIT_FAILURE);
    }

    splash_screen->load   = splash_screen_load;
    splash_screen->input  = splash_screen_input;
    splash_screen->update = splash_screen_update;
    splash_screen->render = splash_screen_render;
    splash_screen->run    = splash_screen_run;
    splash_screen->unload = splash_screen_unload;

    splash_screen->camera.color.r = 0;
    splash_screen->camera.color.g = 0;
    splash_screen->camera.color.b = 0;
    splash_screen->camera.color.a = 255;
}

void splash_screen_load(void) {
    logo_texture = gfx_load_texture(logo_png, logo_png_size);  

    SDL_QueryTexture(logo_texture, NULL, NULL, &logo_rect.w, &logo_rect.h);
    logo_rect.x = (WINDOW_WIDTH - logo_rect.w) * DIV2;
    logo_rect.y = (WINDOW_HEIGHT - logo_rect.h) * DIV2;

    dodoi_texture = gfx_load_texture(de_128_png, de_128_png_size);
    dodoi_rect.w = 64;
    dodoi_rect.h = 64;

    dodoi_rect.x = 0;
    dodoi_rect.y = (WINDOW_HEIGHT - dodoi_rect.h);

    running = true;
}

void splash_screen_input(void) {}

void splash_screen_update(void) {
    static f32 timer = 0.0f;
    timer += engine_calculate_delta_time();

    if (timer > 2.99f) {
        timer = 0.0f;
        running = false;
    }
}

void splash_screen_render(void) {
    scene_begin_render();
    {
        SDL_Renderer* renderer = ctx_get_renderer();
        SDL_RenderCopy(renderer, logo_texture, NULL, &logo_rect);
        SDL_RenderCopy(renderer, dodoi_texture, NULL, &dodoi_rect);
    }
    scene_end_render();
}

u8 splash_screen_run(void) {
    while (running) {
        splash_screen_input();
        splash_screen_update();
        splash_screen_render();
    }
    return SCENE_GAME;
}

void splash_screen_unload(void) {
    SDL_DestroyTexture(logo_texture);
    logo_texture = NULL;

    SDL_DestroyTexture(dodoi_texture);
    dodoi_texture = NULL;

    free(splash_screen);
    splash_screen = NULL;
}

scene_t* splash_screen_get_scene(void) {
    return splash_screen;
}
