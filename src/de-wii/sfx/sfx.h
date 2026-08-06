/**
 * @file sfx.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../de.h"

/**
 * @brief Loads a sound effect from memory data.
 * @param data Pointer to the sound data in memory
 * @param size Size of the sound data in bytes
 * @return A pointer to the loaded Mix_Chunk, or NULL on failure
*/
Mix_Chunk* sfx_load_sound(const u8* data, const size_t size);

/**
 * @brief Loads music from memory data.
 * @param data Pointer to the music data in memory
 * @param size Size of the music data in bytes
 * @return A pointer to the loaded Mix_Music, or NULL on failure
*/
Mix_Music* sfx_load_music(const u8* data, const size_t size);

/**
 * @brief Plays a sound effect.
 * @param sound Pointer to the Mix_Chunk to play
 * @return The channel on which the sound is played, or -1 on failure
*/
i32 sfx_play_sound(Mix_Chunk* sound);

/**
 * @brief Plays music.
 * @param music Pointer to the Mix_Music to play
 * @param loops Number of times to loop the music (-1 for infinite)
 * @return 0 on success, -1 on failure
*/
i32 sfx_play_music(Mix_Music* music, i32 loops);

/**
 * @brief Pauses the currently playing music.
*/
void sfx_pause_music();

/**
 * @brief Unpauses the currently paused music.
*/
void sfx_unpause_music();

/**
 * @brief Stops the currently playing music.
*/
void sfx_stop_music();
