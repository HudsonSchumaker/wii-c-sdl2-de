/**
 * @file map.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_MAP_H
#define DE_MAP_H

#include "../de.h"

typedef enum {
    TILE_PATH,
    TILE_GROUND
} map_tile_type_e;

typedef struct {
    map_tile_type_e type;
    short texture_id;
} map_tile_t;

typedef struct {
    SDL_Texture* textures[8];
    map_tile_t tiles[MAP_HEIGHT][MAP_WIDTH];
} map_t;

/**
 * Loads a map from the provided data array. Each element in the array represents a tile, with the first character indicating the tile type and the remaining characters representing the texture ID.
 * @param map A pointer to the map_t struct to load the data into
 * @param data A 2D array of strings representing the map data
*/
void map_load(map_t* map, const char* data[MAP_HEIGHT][MAP_WIDTH]);

/**
 * Renders the map on the screen.
 * @param map A pointer to the map_t struct to render
*/
void map_render(const map_t* map);

/**
 * Gets the type of a tile at the specified coordinates.
 * @param map A pointer to the map_t struct
 * @param x The x-coordinate of the tile
 * @param y The y-coordinate of the tile
 * @return The type of the tile at the specified coordinates
*/
map_tile_type_e map_get_tile_type(const map_t* map, short x, short y);

#endif // DE_MAP_H
