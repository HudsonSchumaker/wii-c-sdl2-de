/**
 * @file menu_screen.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "menu_screen.h"
#include "../de-wii/gfx/gfx.h"
#include "../de-wii/core/engine.h"
#include "../de-wii/core/input.h"
#include "../de-wii/ui/menu.h"
#include "../de-wii/ui/image.h"
#include "HemiHead_ttf.h"
#include "ans_png.h"

static bool    running     = false;
static u8      next_screen = SCENE_EXIT;
static menu_t  m;
static image_t* a_button = NULL;

scene_t* menu_screen = NULL;

static void on_play(void)    { next_screen = SCENE_GAME;    running = false; }
static void on_credits(void) { next_screen = SCENE_CREDITS; running = false; }
static void on_quit(void)    { next_screen = SCENE_EXIT;    running = false; }

void menu_screen_init(void) {
    menu_screen = malloc(sizeof(scene_t));
    if (menu_screen == NULL) {
        exit(EXIT_FAILURE);
    }

    menu_screen->load   = menu_screen_load;
    menu_screen->input  = menu_screen_input;
    menu_screen->update = menu_screen_update;
    menu_screen->render = menu_screen_render;
    menu_screen->run    = menu_screen_run;
    menu_screen->unload = menu_screen_unload;
}

void menu_screen_load(void) {
    m = menu_create(PAD_BUTTON_UP, PAD_BUTTON_DOWN, PAD_BUTTON_A);

    menu_add_item(&m, 0, 180, "Play", 32, HemiHead_ttf, HemiHead_ttf_size, on_play);
    label_set_horizontal_center(&m.items[m.count - 1]);

    menu_add_item(&m, 0, 240, "Credits", 32, HemiHead_ttf, HemiHead_ttf_size, on_credits);
    label_set_horizontal_center(&m.items[m.count - 1]);

    menu_add_item(&m, 0, 300, "Quit", 32, HemiHead_ttf, HemiHead_ttf_size, on_quit);
    label_set_horizontal_center(&m.items[m.count - 1]);

    a_button = image_new(WINDOW_WIDTH - 48, WINDOW_HEIGHT - 48);
    image_set_source(a_button, ans_png, ans_png_size);

    running = true;
}

void menu_screen_input(void) {
    input_update();
    menu_handle_input(&m);
}

void menu_screen_update(void) {
    engine_calculate_delta_time();
}

void menu_screen_render(void) {
    scene_begin_render();
    {
        menu_render(&m);
        image_render(a_button);
    }
    scene_end_render();
}

u8 menu_screen_run(void) {
    while (running) {
        menu_screen_input();
        menu_screen_update();
        menu_screen_render();
    }
    return next_screen;
}

void menu_screen_unload(void) {
    menu_release(&m);
    image_destroy(a_button);
    a_button = NULL;

    free(menu_screen);
    menu_screen = NULL;
}

scene_t* menu_screen_get_scene(void) {
    return menu_screen;
}
