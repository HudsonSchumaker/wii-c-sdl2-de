/**
 * @file entity_manager.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_ENTITY_MANAGER_H
#define DE_ENTITY_MANAGER_H

#include "../de.h"

typedef enum {
    TAG_NONE = 0,
    TAG_PLAYER = 1,
    TAG_ENEMY = 2,
    TAG_PROJECTILE = 3,
    TAG_POWERUP = 4,
    TAG_TOWER = 5
} tag_e;

typedef struct {
    bool alive[MAX_ENTITIES];
    tag_e tag[MAX_ENTITIES];
    u16 next;
} entity_manager_t;

/**
 * @brief Initializes the entity manager by setting all entities to not alive and resetting the next available entity index.
 * @param em A pointer to the entity manager to initialize.
*/
static inline void entity_manager_init(entity_manager_t* em) {
    em->next = 0;
    for (u16 e = 0; e < MAX_ENTITIES; e++) {
        em->tag[e] = TAG_NONE;
        em->alive[e] = false;
    }
}

/**
 * @brief Creates a new entity by finding the next available slot in the entity manager.
 * @param em A pointer to the entity manager.
 * @return The ID of the newly created entity, or UINT16_MAX if no available slots.
*/
static inline entity_t entity_create(entity_manager_t* em) {
    for (u16 e = em->next; e < MAX_ENTITIES; e++) {
        if (!em->alive[e]) {
            em->alive[e] = true;
            em->tag[e] = TAG_NONE;
            em->next = e + 1;
            return e;
        }
    }
    return UINT16_MAX;
}

/**
 * @brief Creates a new entity by finding the next available slot in the entity manager.
 * @param em A pointer to the entity manager.
 * @param tag The tag to assign to the newly created entity.
 * @return The ID of the newly created entity, or UINT16_MAX if no available slots.
*/
static inline entity_t entity_create_w_tag(entity_manager_t* em, tag_e tag) {
    for (u16 e = em->next; e < MAX_ENTITIES; e++) {
        if (!em->alive[e]) {
            em->alive[e] = true;
            em->tag[e] = tag;
            em->next = e + 1;
            return e;
        }
    }
    return UINT16_MAX;
}

/**
 * @brief Sets the tag of an entity if it is alive.
 * @param em A pointer to the entity manager.
 * @param e The ID of the entity to set the tag for.
 * @param tag The tag to assign to the entity.
*/
static inline void entity_set_tag(entity_manager_t* em, entity_t e, tag_e tag) {
    if (e < MAX_ENTITIES && em->alive[e]) {
        em->tag[e] = tag;
    }
}

/**
 * @brief Gets the tag of an entity if it is alive.
 * @param em A pointer to the entity manager.
 * @param e The ID of the entity to get the tag for.
 * @return The tag of the entity, or TAG_NONE if the entity is not alive or the ID is out of bounds.
*/
static inline tag_e entity_get_tag(entity_manager_t* em, entity_t e) {
    if (e < MAX_ENTITIES && em->alive[e]) {
        return em->tag[e];
    }
    return TAG_NONE;
}

/**
 * @brief Destroys an entity by marking it as not alive and updating the next available entity index if necessary.
 * @param em A pointer to the entity manager.
 * @param e The ID of the entity to destroy.
*/
static inline void entity_destroy(entity_manager_t* em, entity_t e) { 
    em->alive[e] = false;
    em->tag[e] = TAG_NONE;
    if (e < em->next) {
        em->next = e;
    }
}

#endif // DE_ENTITY_MANAGER_H
