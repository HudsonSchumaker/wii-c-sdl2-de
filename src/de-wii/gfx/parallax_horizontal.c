/**
 * @file parallax_horizontal.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "gfx.h"
#include "parallax.h"
#include "../core/context.h"

parallax_horizontal_t parallax_horizontal_simple(const u8* parallax_data, const size_t parallax_size) {
    parallax_horizontal_t parallax;
    parallax.background = NULL;
    parallax.bg_rect = (SDL_Rect){ 0, 0, 0, 0 };
    parallax.texture = gfx_load_texture(parallax_data, parallax_size);
    SDL_QueryTexture(parallax.texture, NULL, NULL, &parallax.size.x, &parallax.size.y);

    parallax.rect_a = (SDL_Rect){ 0, 0, parallax.size.x, parallax.size.y };
    parallax.rect_b = (SDL_Rect){ -parallax.size.x, 0, parallax.size.x, parallax.size.y };
    parallax.direction = 1; // Default direction is right
    
    return parallax;
}

parallax_horizontal_t parallax_horizontal_double(const u8* bg_data, const size_t bg_size, const u8* parallax_data, const size_t parallax_size) {
    parallax_horizontal_t parallax;
    parallax.background = gfx_load_texture(bg_data, bg_size);
    parallax.bg_rect = gfx_get_texture_size(parallax.background);
    
    parallax.texture = gfx_load_texture(parallax_data, parallax_size);
    SDL_QueryTexture(parallax.texture, NULL, NULL, &parallax.size.x, &parallax.size.y);
    
    parallax.rect_a = (SDL_Rect){ 0, 0, parallax.size.x, parallax.size.y };
    parallax.rect_b = (SDL_Rect){ -parallax.size.x, 0, parallax.size.x, parallax.size.y };
    parallax.direction = 1; // Default direction is right
    
    return parallax;
}

parallax_horizontal_t* parallax_horizontal_simple_new(const u8* parallax_data, const size_t parallax_size) {
    parallax_horizontal_t* parallax = malloc(sizeof(parallax_horizontal_t));
    *parallax = parallax_horizontal_simple(parallax_data, parallax_size);
    return parallax;
}

parallax_horizontal_t* parallax_horizontal_double_new(const u8* bg_data, const size_t bg_size, const u8* parallax_data, const size_t parallax_size) {
    parallax_horizontal_t* parallax = malloc(sizeof(parallax_horizontal_t));
    *parallax = parallax_horizontal_double(bg_data, bg_size, parallax_data, parallax_size);
    return parallax;
}

void parallax_horizontal_update(parallax_horizontal_t* parallax) {    
    if (parallax->rect_a.x >= parallax->size.x) {
        parallax->rect_a.x = 0;
        parallax->rect_a.w = parallax->size.x;
        parallax->rect_a.h = parallax->size.y;
        
        parallax->rect_b.x = -parallax->size.x;
        parallax->rect_b.w = parallax->size.x;
        parallax->rect_b.h = parallax->size.y;
    }
    parallax->rect_a.x += parallax->direction;
    parallax->rect_b.x += parallax->direction;
}

void parallax_horizontal_render(const parallax_horizontal_t* parallax) {
    if (parallax->background) {
        SDL_RenderCopy(ctx_get_renderer(), parallax->background, NULL, &parallax->bg_rect);
    }
    
    SDL_RenderCopy(ctx_get_renderer(), parallax->texture, NULL, &parallax->rect_a);
    SDL_RenderCopy(ctx_get_renderer(), parallax->texture, NULL, &parallax->rect_b);
}

void parallax_horizontal_destroy(parallax_horizontal_t* parallax) {
    if (parallax->background) {
        SDL_DestroyTexture(parallax->background);
        parallax->background = NULL;
    }
    SDL_DestroyTexture(parallax->texture);
    parallax->texture = NULL;
    free(parallax);
}
