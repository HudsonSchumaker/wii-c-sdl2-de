/**
 * @file scene.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "scene.h"
#include "../core/context.h"
static scene_t* current_scene = NULL;

scene_t* scene_init() {
    scene_t* scene = malloc(sizeof(scene_t));
    if (scene == NULL) {
        exit(EXIT_FAILURE);
    }

    scene->camera = camera_new(color_black());
    return scene;
}

u8 scene_set_scene(scene_t* scene) {
    u8 status = 0;
    if (current_scene != NULL) {
        current_scene->unload();
    }

    current_scene = scene;
    if (current_scene != NULL) {
        current_scene->load();
        status = current_scene->run();
    }

    return status;
}

void scene_begin_render(void) {
    SDL_Renderer* renderer = ctx_get_renderer();
    SDL_SetRenderDrawColor(
        renderer,
        current_scene->camera.color.r,
        current_scene->camera.color.g,  
        current_scene->camera.color.b, 
        current_scene->camera.color.a
    );
    SDL_RenderClear(renderer);
}

void scene_end_render(void) {
    SDL_Renderer* renderer = ctx_get_renderer();
    SDL_RenderPresent(renderer);
}
