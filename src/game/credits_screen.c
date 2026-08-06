/**
 * @file credits_screen.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "credits_screen.h"
#include "../de-wii/gfx/gfx.h"
#include "../de-wii/core/engine.h"
#include "../de-wii/core/context.h"
#include "bns_png.h"
#include "HemiHead_ttf.h"

static bool running = false;
static u8 next_screen = SCENE_SPLASH;

scene_t* credits_screen = NULL;
static SDL_Texture* title_texture = NULL;
static SDL_Rect title_rect = {0};
static SDL_Texture* gabriel_texture = NULL;
static SDL_Rect gabriel_rect = {0};
static SDL_Texture* hudson_texture = NULL;
static SDL_Rect hudson_rect = {0};
static SDL_Texture* b_b_texture = NULL;
static SDL_Rect b_b_rect = {0};

void credits_screen_init(void) {
    credits_screen = malloc(sizeof(scene_t));
    if (credits_screen == NULL) {
        exit(EXIT_FAILURE);
    }

    credits_screen->load   = credits_screen_load;
    credits_screen->input  = credits_screen_input;
    credits_screen->update = credits_screen_update;
    credits_screen->render = credits_screen_render;
    credits_screen->run    = credits_screen_run;
    credits_screen->unload = credits_screen_unload;
}

void credits_screen_load(void) {
    // Title
    title_texture = gfx_create_text(HemiHead_ttf, HemiHead_ttf_size, "Card Story", 48, color_red());
    SDL_QueryTexture(title_texture, NULL, NULL, &title_rect.w, &title_rect.h);
    title_rect.x = (WINDOW_WIDTH - title_rect.w) * DIV2;
    title_rect.y = (WINDOW_HEIGHT - title_rect.h) * DIV8;

    gabriel_texture = gfx_create_text(HemiHead_ttf, HemiHead_ttf_size, "Gabriel Schumaker - Pixel Artist", 24, color_white());
    SDL_QueryTexture(gabriel_texture, NULL, NULL, &gabriel_rect.w, &gabriel_rect.h);
    gabriel_rect.x = (WINDOW_WIDTH - gabriel_rect.w) * DIV2;
    gabriel_rect.y = (WINDOW_HEIGHT - gabriel_rect.h) * DIV4;

    hudson_texture = gfx_create_text(HemiHead_ttf, HemiHead_ttf_size, "Hudson Schumaker - Programmer", 24, color_white());
    SDL_QueryTexture(hudson_texture, NULL, NULL, &hudson_rect.w, &hudson_rect.h);
    hudson_rect.x = (WINDOW_WIDTH - hudson_rect.w) * DIV2;
    hudson_rect.y = (WINDOW_HEIGHT - hudson_rect.h) * DIV4 + 32;

    // Button B
    b_b_texture = gfx_load_texture(bns_png, bns_png_size);
    SDL_QueryTexture(b_b_texture, NULL, NULL, &b_b_rect.w, &b_b_rect.h);
    b_b_rect.x = (WINDOW_WIDTH - b_b_rect.w) - 16;
    b_b_rect.y = (WINDOW_HEIGHT - b_b_rect.h) - 16;

    running = true;
}

void credits_screen_input(void) {
    PAD_ScanPads();
    u16 buttonsDown = PAD_ButtonsDown(0);
    if (buttonsDown & PAD_BUTTON_B) {
        next_screen = SCENE_SPLASH;
        running = false;
    }
}

void credits_screen_update(void) {
    engine_calculate_delta_time();
}

void credits_screen_render(void) {
    scene_begin_render();
    {
        SDL_Renderer* renderer = ctx_get_renderer();
        SDL_RenderCopy(renderer, title_texture, NULL, &title_rect);

        // Credits
        SDL_RenderCopy(renderer, gabriel_texture, NULL, &gabriel_rect);
        SDL_RenderCopy(renderer, hudson_texture, NULL, &hudson_rect);

        // Button B
        SDL_RenderCopy(renderer, b_b_texture, NULL, &b_b_rect);
    }
    scene_end_render();
}

u8 credits_screen_run(void) {
    while (running) {
        credits_screen_input();
        credits_screen_update();
        credits_screen_render();
    }
    return next_screen;
}

void credits_screen_unload(void) {
    SDL_DestroyTexture(title_texture);
    title_texture = NULL;

    SDL_DestroyTexture(gabriel_texture);
    gabriel_texture = NULL;

    SDL_DestroyTexture(hudson_texture);
    hudson_texture = NULL;

    SDL_DestroyTexture(b_b_texture);
    b_b_texture = NULL;

    free(credits_screen);
    credits_screen = NULL;
}

scene_t* credits_screen_get_scene(void) {
    return credits_screen;
}
