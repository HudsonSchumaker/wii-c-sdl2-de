/**
 * @file radar_system.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "radar_system.h"
#include "../core/engine.h"
#include "../math/math2d.h"

void radar_system(tag_e source, tag_e target) {
    entity_manager_t* em = engine_get_entity_manager();
    transform_pool_t* t = engine_get_transform_pool();
    texture_pool_t* tp = engine_get_texture_pool();

    for (entity_t i = 0; i < MAX_ENTITIES; i++) {
        if (em->alive[i] && em->tag[i] == source) {
            f32 source_x = t->px[i];
            f32 source_y = t->py[i];
            f32 source_w = tp->w[i] * t->sx[i];
            f32 source_h = tp->h[i] * t->sy[i];

            for (entity_t j = 0; j < MAX_ENTITIES; j++) {
                if (em->alive[j] && em->tag[j] == target) {
                    f32 target_x = t->px[j];
                    f32 target_y = t->py[j];
                    f32 target_w = tp->w[j] * t->sx[j];
                    f32 target_h = tp->h[j] * t->sy[j];

                    f32 target_cx = target_x + (target_w * 0.5f);
                    f32 target_cy = target_y + (target_h * 0.5f);
                    f32 source_cx = source_x + (source_w * 0.5f);
                    f32 source_cy = source_y + (source_h * 0.5f);

                    f32 dx = target_cx - source_cx;
                    f32 dy = target_cy - source_cy;
                    f32 distance_sq = dx * dx + dy * dy;
                    f32 range = 64.0f; 
                    if (distance_sq > range * range) {
                        continue;
                    }

                    i32 angle = degrees_to_index(rad2deg(angle_between_direction(dx, dy)));
                    t->ra[i] = angle;

                    // Here you can implement the logic to check the distance between (source_x, source_y) and (target_x, target_y)
                    // and perform any necessary actions based on that.
                }
            }
        }
    }
}
