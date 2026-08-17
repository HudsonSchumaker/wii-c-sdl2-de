/**
 * @file collision.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_COLLISION_H
#define DE_COLLISION_H

#include "../de.h"
#include "../math/math2d.h"

/**
 * @brief Checks if a point (px, py) is inside a rectangle defined by (rx, ry, rw, rh).
 * @param px Point X coordinate
 * @param py Point Y coordinate
 * @param rx Rectangle X coordinate
 * @param ry Rectangle Y coordinate
 * @param rw Rectangle width
 * @param rh Rectangle height
 * @return true if the point is inside the rectangle, false otherwise
*/
INLINE bool point_in_rect(i32 px, i32 py, i32 rx, i32 ry, i32 rw, i32 rh) {
    return (
        px >= rx &&
        px <= rx + rw &&
        py >= ry &&
        py <= ry + rh
    );
}

/**
 * @brief Checks if two rectangles intersect.
 * @param ax First rectangle X coordinate
 * @param ay First rectangle Y coordinate
 * @param aw First rectangle width
 * @param ah First rectangle height
 * @param bx Second rectangle X coordinate
 * @param by Second rectangle Y coordinate
 * @param bw Second rectangle width
 * @param bh Second rectangle height
 * @return true if the rectangles intersect, false otherwise
*/
INLINE bool rect_intersects(i32 ax, i32 ay, i32 aw, i32 ah, i32 bx, i32 by, i32 bw, i32 bh) {
    return !(
        ax + aw < bx ||
        ax > bx + bw ||
        ay + ah < by ||
        ay > by + bh
    );
}

/**
 * @brief Checks if two circles intersect.
 * @param a First circle center
 * @param ra First circle radius
 * @param b Second circle center
 * @param rb Second circle radius
 * @return true if the circles intersect, false otherwise
*/
INLINE bool circle_intersects(vec2_t a, i32 ra, vec2_t b, i32 rb) {
    i32 rr = ra + rb;
    return vec2_distance_sq(a, b) <= (rr * rr);
}

#endif // DE_COLLISION_H
