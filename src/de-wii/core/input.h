/**
 * @file input.h
 * @author Hudson Schumaker
 * @brief Wraps the GameCube controller (PAD) subsystem into a simple per-frame input snapshot.
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../de.h"
#include "../math/math2d.h"

#define INPUT_MAX_PADS 4
#define INPUT_STICK_DEAD_ZONE 8

/**
 * @brief A snapshot of a single GameCube controller's state for the current frame.
*/
typedef struct {
    bool connected;
    u16  buttons_down;  // Buttons that transitioned from up to down this frame
    u16  buttons_up;    // Buttons that transitioned from down to up this frame
    u16  buttons_held;  // Buttons currently held down
    vec2_t stick;       // Main stick, normalized to [-1, 1] with dead zone applied
    vec2_t sub_stick;   // C-stick, normalized to [-1, 1] with dead zone applied
    f32  trigger_l;     // Left analog trigger, normalized to [0, 1]
    f32  trigger_r;     // Right analog trigger, normalized to [0, 1]
} pad_state_t;

/**
 * @brief Scans all controller ports and refreshes the per-frame pad state. Call this once per frame, before reading input.
*/
void input_update(void);

/**
 * @brief Gets the last-scanned state of a controller.
 * @param chan The controller port, in the range [0, INPUT_MAX_PADS)
 * @return A pointer to the pad state, or NULL if chan is out of range
*/
const pad_state_t* input_get_pad(u8 chan);

/**
 * @brief Checks if a button was pressed down this frame on a controller.
 * @param chan The controller port, in the range [0, INPUT_MAX_PADS)
 * @param button One of the PAD_BUTTON_ or PAD_TRIGGER_ masks from ogc/pad.h
 * @return true if the button transitioned from up to down this frame
*/
bool input_button_down(u8 chan, u16 button);

/**
 * @brief Checks if a button is currently held down on a controller.
 * @param chan The controller port, in the range [0, INPUT_MAX_PADS)
 * @param button One of the PAD_BUTTON_ or PAD_TRIGGER_ masks from ogc/pad.h
 * @return true if the button is currently held down
*/
bool input_button_held(u8 chan, u16 button);

/**
 * @brief Checks if a button was released this frame on a controller.
 * @param chan The controller port, in the range [0, INPUT_MAX_PADS)
 * @param button One of the PAD_BUTTON_ or PAD_TRIGGER_ masks from ogc/pad.h
 * @return true if the button transitioned from down to up this frame
*/
bool input_button_up(u8 chan, u16 button);
