/**
 * @file sfx.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "sfx.h"

Mix_Chunk* sfx_load_sound(const u8* data, const size_t size) {
    SDL_RWops* rw = SDL_RWFromMem((void*)data, size);
    Mix_Chunk* chunk = Mix_LoadWAV_RW(rw, 1);
    return chunk;
}

Mix_Music* sfx_load_music(const u8* data, const size_t size) {
    SDL_RWops* rw = SDL_RWFromMem((void*)data, size);
    Mix_Music* music = Mix_LoadMUS_RW(rw, 1);
    return music;
}

i32 sfx_play_sound(Mix_Chunk* sound) {
    return Mix_PlayChannel(-1, sound, 0);
}

i32 sfx_play_music(Mix_Music* music, i32 loops) {   
    return Mix_PlayMusic(music, loops);
}

void sfx_pause_music() {
    Mix_PauseMusic();
}

void sfx_unpause_music() {
    Mix_ResumeMusic();
}

void sfx_stop_music() {
    Mix_HaltMusic();
}
