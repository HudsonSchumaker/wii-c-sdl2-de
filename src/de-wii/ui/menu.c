/**
 * @file menu.c
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "menu.h"
#include "../core/input.h"
#include "../core/context.h"

menu_t menu_create(u16 pad_up, u16 pad_down, u16 pad_confirm) {
    menu_t m    = {0};
    m.highlight   = color_yellow();
    m.pad_up      = pad_up;
    m.pad_down    = pad_down;
    m.pad_confirm = pad_confirm;
    return m;
}

void menu_add_item(menu_t* m, i32 x, i32 y, const char* text,
                   u8 font_size, const u8* font_data, size_t font_size_bytes,
                   menu_callback_t cb) {
    if (m->count >= MENU_MAX_ITEMS) return;

    i32 i        = m->count;
    m->items[i]  = label(x, y, text);
    label_set_font_size(&m->items[i], font_size, font_data, font_size_bytes);
    m->callbacks[i] = cb;
    m->count++;
}

void menu_handle_input(menu_t* m) {
    if (m->count == 0) return;

    if (input_button_down(0, m->pad_up)) {
        m->selected = (m->selected - 1 + m->count) % m->count;
    }
    if (input_button_down(0, m->pad_down)) {
        m->selected = (m->selected + 1) % m->count;
    }
    if (input_button_down(0, m->pad_confirm)) {
        if (m->callbacks[m->selected]) {
            m->callbacks[m->selected]();
        }
    }
}

void menu_render(menu_t* m) {
    SDL_Renderer* renderer = ctx_get_renderer();

    for (i8 i = 0; i < m->count; i++) {
        if (i == m->selected) {
            label_t* lbl = &m->items[i];
            SDL_Rect sel = { lbl->x - 8, lbl->y - 4, lbl->w + 16, lbl->h + 8 };
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, m->highlight.r, m->highlight.g, m->highlight.b, 80);
            SDL_RenderFillRect(renderer, &sel);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
        }
        label_render(&m->items[i]);
    }
}

void menu_release(menu_t* m) {
    for (i8 i = 0; i < m->count; i++) {
        label_release(&m->items[i]);
    }
    m->count    = 0;
    m->selected = 0;
}
