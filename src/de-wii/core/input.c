/**
 * @file input.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "input.h"
static pad_state_t pads[INPUT_MAX_PADS];

static f32 normalize_stick_axis(s8 raw) {
    if (raw > -INPUT_STICK_DEAD_ZONE && raw < INPUT_STICK_DEAD_ZONE) {
        return 0.0f;
    }
    return clampf((f32)raw * DIV128, -1.0f, 1.0f);
}

static f32 normalize_trigger(u8 raw) {
    return clampf((f32)raw / 255.0f, 0.0f, 1.0f);
}

void input_update(void) {
    u32 connected_mask = PAD_ScanPads();

    for (u8 chan = 0; chan < INPUT_MAX_PADS; chan++) {
        pad_state_t* pad = &pads[chan];

        u16 held = PAD_ButtonsHeld(chan);
        pad->connected    = (connected_mask & (PAD_CHAN0_BIT >> chan)) != 0;
        pad->buttons_down = PAD_ButtonsDown(chan);
        pad->buttons_up   = PAD_ButtonsUp(chan);
        pad->buttons_held = held;

        pad->stick.x = normalize_stick_axis(PAD_StickX(chan));
        pad->stick.y = normalize_stick_axis(PAD_StickY(chan));
        pad->sub_stick.x = normalize_stick_axis(PAD_SubStickX(chan));
        pad->sub_stick.y = normalize_stick_axis(PAD_SubStickY(chan));

        pad->trigger_l = normalize_trigger(PAD_TriggerL(chan));
        pad->trigger_r = normalize_trigger(PAD_TriggerR(chan));
    }
}

const pad_state_t* input_get_pad(u8 chan) {
    if (chan >= INPUT_MAX_PADS) {
        return NULL;
    }
    return &pads[chan];
}

bool input_button_down(u8 chan, u16 button) {
    if (chan >= INPUT_MAX_PADS) {
        return false;
    }
    return (pads[chan].buttons_down & button) != 0;
}

bool input_button_held(u8 chan, u16 button) {
    if (chan >= INPUT_MAX_PADS) {
        return false;
    }
    return (pads[chan].buttons_held & button) != 0;
}

bool input_button_up(u8 chan, u16 button) {
    if (chan >= INPUT_MAX_PADS) {
        return false;
    }
    return (pads[chan].buttons_up & button) != 0;
}
