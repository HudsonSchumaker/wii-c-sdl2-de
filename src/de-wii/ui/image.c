/**
 * @file image.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "image.h"
#include "../gfx/gfx.h"
#include "../gfx/color.h"
#include "../core/context.h"

image_t image(i32 x, i32 y) {
    image_t image;
    image.x = x;
    image.y = y;
    image.w = 0;
    image.h = 0;
    image.texture = NULL;
    image.color = color_white();
    image.visible = true;
    return image;
}

image_t* image_new(i32 x, i32 y) {
    image_t* heap_image = malloc(sizeof(image_t));
    *heap_image = image(x, y);
    return heap_image;
}

void image_destroy(image_t* img) {
    if (img->texture) {
        SDL_DestroyTexture(img->texture);
        img->texture = NULL;
    }
    free(img);
}
    
void image_set_source(image_t* img, const u8* data, size_t size) {
    img->texture = gfx_load_texture(data, size);
    SDL_QueryTexture(img->texture, NULL, NULL, &img->w, &img->h);
}

void image_set_tint(image_t* img, color_t color) {
    img->color = color;
}

void image_render(const image_t* img) {
    if (img->visible) {
        SDL_SetTextureColorMod(img->texture, img->color.r, img->color.g, img->color.b);
        SDL_SetTextureAlphaMod(img->texture, img->color.a);
        
        SDL_Rect rect = { img->x, img->y, img->w, img->h };
        SDL_RenderCopy(ctx_get_renderer(), img->texture, NULL, &rect);
    }
}
