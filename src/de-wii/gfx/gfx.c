/**
 * @file gfx.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "gfx.h"
#include "../core/context.h"
#define GFX_TEXTURE_CACHE_SIZE 32

static texture_cache_entry_t texture_cache[GFX_TEXTURE_CACHE_SIZE];
static i32 texture_cache_count = 0;

SDL_Texture* gfx_load_texture(const u8* data, const size_t size) {
    SDL_RWops* rw = SDL_RWFromMem((void*)data, size);
    SDL_Texture* texture = IMG_LoadTexture_RW(ctx_get_renderer(), rw, 1);
    return texture;
}

texture_t gfx_load_texture_ex(const u8* data, const size_t size) {
    SDL_Texture* texture = gfx_load_texture(data, size);
    if (texture == NULL) {
        return (texture_t){ 0, 0, NULL };
    }

    SDL_Rect rect = gfx_get_texture_size(texture);
    return (texture_t){ rect.w, rect.h, texture };
}

texture_t gfx_load_texture_cached(const u8* data, const size_t size) {
    for (i32 i = 0; i < texture_cache_count; i++) {
        if (texture_cache[i].data == data) {
            return texture_cache[i].texture;
        }
    }

    texture_t texture = gfx_load_texture_ex(data, size);
    if (texture.texture != NULL && texture_cache_count < GFX_TEXTURE_CACHE_SIZE) {
        texture_cache[texture_cache_count].data = data;
        texture_cache[texture_cache_count].texture = texture;
        texture_cache_count++;
    }
    return texture;
}

void gfx_clear_texture_cache(void) {
    for (i32 i = 0; i < texture_cache_count; i++) {
        if (texture_cache[i].texture.texture != NULL) {
            SDL_DestroyTexture(texture_cache[i].texture.texture);
        }
    }
    texture_cache_count = 0;
}

SDL_Texture* gfx_create_text(const u8* data, const size_t size, const char* text, u8 text_size, color_t color) {
    SDL_RWops* rw = SDL_RWFromMem((void*)data, size);
    TTF_Font* font = TTF_OpenFontRW(rw, 1, text_size);

    SDL_Color sdl_color = color_to_sdl_color(color);

    SDL_Surface* surface = TTF_RenderText_Blended(font, text, sdl_color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx_get_renderer(), surface);
    
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;
}

SDL_Rect gfx_get_texture_size(SDL_Texture* texture) {
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = 0;
    rect.y = 0;
    return rect;
}

SDL_FRect gfx_get_texture_fsize(SDL_Texture* texture) {
    SDL_FRect rect;
    SDL_QueryTexture(texture, NULL, NULL, (int*)&rect.w, (int*)&rect.h);
    rect.x = 0.0f;
    rect.y = 0.0f;
    return rect;
}

void gfx_render_texture(SDL_Texture* texture, i32 x, i32 y, i32 w, i32 h) {
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(ctx_get_renderer(), texture, NULL, &dest);
}

void gfx_render_texture_rotated(SDL_Texture* texture, i32 x, i32 y, i32 w, i32 h, double angle) {
    SDL_Rect dest = { x, y, w, h };
    SDL_Point center = { w >> 1, h >> 1 };
    SDL_RenderCopyEx(ctx_get_renderer(), texture, NULL, &dest, angle, &center, SDL_FLIP_NONE);
}
