/**
 * @file context.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../de.h"

/**
 * @brief the context.
 * @return 0 on success, non-zero on failure
*/
int ctx_init(void);

/**
 * @brief Gets the SDL window.
 * @return The SDL window
*/
SDL_Window* ctx_get_window(void);

/**
 * @brief Gets the SDL renderer.
 * @return The SDL renderer
*/
SDL_Renderer* ctx_get_renderer(void);

/**
 * @brief Checks if the context is initialized.
 * @return 1 if initialized, 0 otherwise
*/
u8 ctx_is_initialized(void);

/**
 * @brief Checks if the video subsystem is initialized.
 * @return 1 if initialized, 0 otherwise
*/
u8 ctx_is_video_initialized(void);

/**
 * @brief Checks if the pad subsystem is initialized.
 * @return 1 if initialized, 0 otherwise
*/
u8 ctx_is_pad_initialized(void);

/**
 * @brief Checks if the window is initialized.
 * @return 1 if initialized, 0 otherwise
*/
u8 ctx_is_window_initialized(void);

/**
 * @brief Checks if the renderer is initialized.
 * @return 1 if initialized, 0 otherwise
*/
u8 ctx_is_renderer_initialized(void);

/**
 * @brief Checks if the image subsystem is initialized.
 * @return 1 if initialized, 0 otherwise
*/
u8 ctx_is_image_initialized(void);

/**
 * @brief Checks if the audio subsystem is initialized.
 * @return 1 if initialized, 0 otherwise
*/
u8 ctx_is_audio_initialized(void);

/**
 * @brief Checks if the TTF subsystem is initialized.
 * @return 1 if initialized, 0 otherwise
*/
u8 ctx_is_ttf_initialized(void);

/**
 * @brief Quits the context and cleans up resources.
*/
void ctx_quit(void);
