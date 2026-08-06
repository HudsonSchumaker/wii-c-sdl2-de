/**
 * @file scene.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../de.h"
#include "../core/camera.h"

/**
 * @brief Represents a game scene with function pointers for loading, input handling, updating, rendering, running, and unloading the scene.
*/
typedef struct {
    void (*load)(void);    // Load the scene
    void (*input)(void);   // Handle input
    void (*update)(void);  // Update the scene
    void (*render)(void);  // Render the scene
	u8   (*run)(void);     // Game Loop for the scene
    void (*unload)(void);  // Unload the scene
    camera_t camera;       // Camera associated with the scene
} scene_t;

/**
 * @brief Initializes the scene, setting the camera of the scene.
 * @param scene Pointer to the scene to initialize.
*/
void scene_init(scene_t* scene);

/**
 * @brief Sets the current active scene. If there is an existing scene, it will be unloaded before the new scene is loaded and run.
 * @param scene Pointer to the new scene to set as active
 * @return Status code returned by the run function of the new scene, or 0 if no scene is set
*/
u8 scene_set_scene(scene_t* scene);

/**
 * @brief Begins the rendering process for the current scene.
*/
void scene_begin_render(void);

/**
 * @brief Ends the rendering process for the current scene.
*/
void scene_end_render(void);
