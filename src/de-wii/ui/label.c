/**
 * @file label.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
 */
#include "label.h"
#include "../gfx/gfx.h"
#include "../gfx/color.h"
#include "../core/context.h"

label_t label(i32 x, i32 y, const char* text) {
    label_t label;
    label.text = strdup(text);
    label.x = x;
    label.y = y;
    label.w = 0;
    label.h = 0;
    label.font_size = 16;
    label.texture = NULL;
    label.color = color_white();
    label.visible = true;
    return label;
}

label_t* label_new(i32 x, i32 y, const char* text) {
    label_t* heap_label = malloc(sizeof(label_t));
    *heap_label = label(x, y, text);
    return heap_label;
}

void label_destroy(label_t* lbl) {
    if (lbl->texture) {
        SDL_DestroyTexture(lbl->texture);
        lbl->texture = NULL;
    }
    free(lbl->text);
    lbl->text = NULL;
    free(lbl);
}

void label_set_color(label_t* lbl, color_t color) {
    lbl->color = color;
}

void label_set_font_size(label_t* lbl, u8 font_size, const u8* data, size_t size) {
    lbl->font_size = font_size;
    if (lbl->texture) {
        SDL_DestroyTexture(lbl->texture);
    }
    lbl->texture = gfx_create_text(data, size, lbl->text, font_size, lbl->color);
    SDL_QueryTexture(lbl->texture, NULL, NULL, &lbl->w, &lbl->h);
}

void label_render(const label_t* lbl) {
    if (lbl->visible && lbl->texture) {
        SDL_Rect rect = { lbl->x, lbl->y, lbl->w, lbl->h };
        SDL_RenderCopy(ctx_get_renderer(), lbl->texture, NULL, &rect);
    }
}

void label_set_on_center(label_t* lbl) {
    if (lbl->texture == NULL) {
        return; // Cannot center a label without a texture
    }

    SDL_Rect rect = gfx_get_texture_size(lbl->texture);
    lbl->x = (WINDOW_WIDTH - rect.w)  * DIV2;
    lbl->y = (WINDOW_HEIGHT - rect.h) * DIV2;
}

void label_set_horizontal_center(label_t* lbl) {
    if (lbl->texture == NULL) {
        return; // Cannot center a label without a texture
    }

    SDL_Rect rect = gfx_get_texture_size(lbl->texture);
    lbl->x = (WINDOW_WIDTH - rect.w) * DIV2;
}

void label_set_text(label_t* lbl, const char* text, const u8* data, size_t size) {
    free(lbl->text);
    lbl->text = strdup(text);
    label_set_font_size(lbl, lbl->font_size, data, size);
}

void label_release(label_t* lbl) {
    if (lbl->texture) {
        SDL_DestroyTexture(lbl->texture);
        lbl->texture = NULL;
    }

    if (lbl->text) {
        free(lbl->text);
        lbl->text = NULL;
    }
}
