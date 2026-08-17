/**
 * @file primitives.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "gfx.h"
#include "../core/context.h"

void gfx_draw_line(i32 x0, i32 y0, i32 x1, i32 y1, color_t color) {
    u8 prev_r, prev_g, prev_b, prev_a;
    SDL_GetRenderDrawColor(ctx_get_renderer(), &prev_r, &prev_g, &prev_b, &prev_a);

    SDL_SetRenderDrawColor(ctx_get_renderer(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(ctx_get_renderer(), x0, y0, x1, y1);
    
    SDL_SetRenderDrawColor(ctx_get_renderer(), prev_r, prev_g, prev_b, prev_a);
}

void gfx_draw_dashed_line(i32 x0, i32 y0, i32 x1, i32 y1, i16 dash_length, color_t color) {
    if (dash_length <= 0) {
        return;
    }

    const i32 dx = x1 - x0;
    const i32 dy = y1 - y0;
    const f32 length = sqrtf((f32)(dx * dx) + (f32)(dy * dy));

    if (length <= 0.0f) {
        return;
    }

    const i32 segment_length = dash_length * 2;
    const i32 segments = (i32)(length / segment_length) + 1;

    const f32 step_x = (f32)dx / length;
    const f32 step_y = (f32)dy / length;

    for (i32 i = 0; i < segments; ++i) {
        const f32 start = (f32)(i * segment_length);
        const f32 end = start + dash_length;

        if (start >= length) {
            break;
        }

        const f32 dash_end = end < length ? end : length;
        if ((i & 1) == 0) {
            const i32 sx = x0 + (i32)(step_x * start);
            const i32 sy = y0 + (i32)(step_y * start);

            const i32 ex = x0 + (i32)(step_x * dash_end);
            const i32 ey = y0 + (i32)(step_y * dash_end);

            gfx_draw_line(sx, sy, ex, ey, color);
        }
    }
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
