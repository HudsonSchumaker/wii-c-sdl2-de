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

void gfx_draw_line(i32 x0, i32 y0, i32 x1, i32 y1, color_t color) {
    u8 prev_r, prev_g, prev_b, prev_a;
    SDL_GetRenderDrawColor(ctx_get_renderer(), &prev_r, &prev_g, &prev_b, &prev_a);

    SDL_SetRenderDrawColor(ctx_get_renderer(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(ctx_get_renderer(), x0, y0, x1, y1);
    
    SDL_SetRenderDrawColor(ctx_get_renderer(), prev_r, prev_g, prev_b, prev_a);
}

void gfx_draw_circle(i32 cx, i32 cy, i32 radius, color_t color) {
    u8 prev_r, prev_g, prev_b, prev_a;
    SDL_GetRenderDrawColor(ctx_get_renderer(), &prev_r, &prev_g, &prev_b, &prev_a);
    SDL_SetRenderDrawColor(ctx_get_renderer(), color.r, color.g, color.b, color.a);
    
    // Draw
    i32 x = radius - 1;
    i32 y = 0;
    i32 dx = 1;
    i32 dy = 1;
    i32 err = dx - (radius << 1);

    while (x >= y) {
        SDL_RenderDrawPoint(ctx_get_renderer(), cx + x, cy + y);
        SDL_RenderDrawPoint(ctx_get_renderer(), cx + y, cy + x);
        SDL_RenderDrawPoint(ctx_get_renderer(), cx - y, cy + x);
        SDL_RenderDrawPoint(ctx_get_renderer(), cx - x, cy + y);
        SDL_RenderDrawPoint(ctx_get_renderer(), cx - x, cy - y);
        SDL_RenderDrawPoint(ctx_get_renderer(), cx - y, cy - x);
        SDL_RenderDrawPoint(ctx_get_renderer(), cx + y, cy - x);
        SDL_RenderDrawPoint(ctx_get_renderer(), cx + x, cy - y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }

    SDL_SetRenderDrawColor(ctx_get_renderer(), prev_r, prev_g, prev_b, prev_a);
}

void gfx_draw_fill_circle(i32 cx, i32 cy, i32 radius, color_t color) {
    u8 prev_r, prev_g, prev_b, prev_a;
    SDL_GetRenderDrawColor(ctx_get_renderer(), &prev_r, &prev_g, &prev_b, &prev_a);
    SDL_SetRenderDrawColor(ctx_get_renderer(), color.r, color.g, color.b, color.a);
    
    for (i32 y = -radius; y <= radius; y++) {
        for (i32 x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(ctx_get_renderer(), cx + x, cy + y);
            }
        }
    }

    SDL_SetRenderDrawColor(ctx_get_renderer(), prev_r, prev_g, prev_b, prev_a);
}

void gfx_draw_dashed_circle(const i32 cx, const i32 cy, const i32 radius, const i32 dash_length, const color_t color) {
    u8 prev_r, prev_g, prev_b, prev_a;
    SDL_GetRenderDrawColor(ctx_get_renderer(), &prev_r, &prev_g, &prev_b, &prev_a);
    SDL_SetRenderDrawColor(ctx_get_renderer(), color.r, color.g, color.b, color.a);
    
    const i32 total_segments = (i32)(radius * PI_F / dash_length);
    const float angle_increment = PI_F / total_segments;

     for (i32 i = 0; i < total_segments; ++i) {
        float angle = angle_increment * i;

        i32 x1 = (i32)(cx + radius * cosf(angle));
        i32 y1 = (i32)(cy + radius * sinf(angle));

        angle = angle_increment * (i + 1);

        i32 x2 = (i32)(cx + radius * cosf(angle));
        i32 y2 = (i32)(cy + radius * sinf(angle));

        if (i % 2 == 0) {
            SDL_RenderDrawLine(ctx_get_renderer(), x1, y1, x2, y2);
        }
    }

    SDL_SetRenderDrawColor(ctx_get_renderer(), prev_r, prev_g, prev_b, prev_a);
}

void gfx_draw_box(SDL_Rect rect, color_t color) {
    u8 prev_r, prev_g, prev_b, prev_a;
    SDL_GetRenderDrawColor(ctx_get_renderer(), &prev_r, &prev_g, &prev_b, &prev_a);
    SDL_SetRenderDrawColor(ctx_get_renderer(), color.r, color.g, color.b, color.a);
    
    SDL_RenderDrawRect(ctx_get_renderer(), &rect);
    SDL_SetRenderDrawColor(ctx_get_renderer(), prev_r, prev_g, prev_b, prev_a);
}

void gfx_draw_fbox(SDL_FRect rect, color_t color) {
    u8 prev_r, prev_g, prev_b, prev_a;
    SDL_GetRenderDrawColor(ctx_get_renderer(), &prev_r, &prev_g, &prev_b, &prev_a);
    SDL_SetRenderDrawColor(ctx_get_renderer(), color.r, color.g, color.b, color.a);
    
    SDL_RenderDrawRectF(ctx_get_renderer(), &rect);
    SDL_SetRenderDrawColor(ctx_get_renderer(), prev_r, prev_g, prev_b, prev_a);
}

void gfx_draw_fill_box(SDL_Rect rect, color_t color) {
    u8 prev_r, prev_g, prev_b, prev_a;
    SDL_GetRenderDrawColor(ctx_get_renderer(), &prev_r, &prev_g, &prev_b, &prev_a);
    SDL_SetRenderDrawColor(ctx_get_renderer(), color.r, color.g, color.b, color.a);
    
    SDL_RenderFillRect(ctx_get_renderer(), &rect);
    SDL_SetRenderDrawColor(ctx_get_renderer(), prev_r, prev_g, prev_b, prev_a);
}

void gfx_draw_fill_fbox(SDL_FRect rect, color_t color) {
    u8 prev_r, prev_g, prev_b, prev_a;
    SDL_GetRenderDrawColor(ctx_get_renderer(), &prev_r, &prev_g, &prev_b, &prev_a);
    SDL_SetRenderDrawColor(ctx_get_renderer(), color.r, color.g, color.b, color.a);
    
    SDL_RenderFillRectF(ctx_get_renderer(), &rect);
    SDL_SetRenderDrawColor(ctx_get_renderer(), prev_r, prev_g, prev_b, prev_a);
}

void gfx_draw_triangle(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, color_t color) {
    gfx_draw_line(x1, y1, x2, y2, color);
    gfx_draw_line(x2, y2, x3, y3, color);
    gfx_draw_line(x3, y3, x1, y1, color);
}
