/**
 * @file math2d.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../de.h"
//----------------------------------------------------------------
// Lookup tables for trigonometric functions
//----------------------------------------------------------------

/**
 * @brief Builds the sine, cosine, and arctangent lookup tables. This function should be called once during initialization.
*/
void build_trigo_tables(void);

/**
 * @brief Converts degrees to the corresponding index in the lookup table.
 * @param degrees The angle in degrees
 * @return The corresponding index in the range [0, 1024) where 1024 represents 360 degrees
*/
i32 degrees_to_index(f32 degrees);

/**
 * @brief Approximates the sine of an angle using a lookup table.
 * @param angle The input angle in the range [0, 1024) where 1024 represents 360 degrees
 * @return Approximation of the sine of the angle
*/    
f32 de_sinf(i32 angle);

/**
 * @brief Approximates the cosine of an angle using a lookup table.
 * @param angle The input angle in the range [0, 1024) where 1024 represents 360 degrees
 * @return Approximation of the cosine of the angle
*/
f32 de_cosf(i32 angle);

/**
 * @brief Approximates the tangent of an angle using a lookup table.
 * @param angle The input angle in the range [0, 1024) where 1024 represents 360 degrees
 * @return Approximation of the tangent of the angle
*/
f32 de_tanf(i32 angle);

//----------------------------------------------------------------
// Square root and inverse fast square root
//----------------------------------------------------------------

/**
 * @brief Fast inverse square root approximation.
 * @param number The input number
 * @return Approximation of 1/sqrt(number)
*/
INLINE f32 rsqrtf(f32 number) {
    union {
        f32 f;
        i32 i;
    } conv;
    f32 x2, y;
    const f32 threehalfs = 1.5f;

    x2 = number * 0.5f;
    conv.f = number;

    conv.i = 0x5f3759df - (conv.i >> 1);
    y = conv.f;

    y = y * (threehalfs - (x2 * y * y));
    return y;
}

/**
 * @brief Fast square root approximation using the inverse square root.
 * @param number The input number
 * @return Approximation of sqrt(number)
*/
INLINE f32 fsqrtf(f32 number) {
    return number * rsqrtf(number);
}

//----------------------------------------------------------------
// Vector2D struct and functions
//----------------------------------------------------------------

/**
 * @brief A 2D vector structure with x and y components, aligned to 32 bytes for SIMD optimizations.
*/
typedef union ALIGN32 {
    struct {
        f32 x;
        f32 y;
    };
    f32 v[2];
} vec2_t;

/**
 * @brief Creates a new 2D vector with the specified x and y components.
 * @param x The X component of the vector
 * @param y The Y component of the vector
 * @return A vec2_t struct with the specified components
*/
INLINE vec2_t vec2_create(f32 x, f32 y) {
    vec2_t v;
    v.x = x;
    v.y = y;
    return v;
}

/**
 * @brief Returns a zero vector.
 * @return A vector with x = 0 and y = 0
*/
INLINE vec2_t vec2_zero(void) {
    return vec2_create(0.0f, 0.0f);
}

/**
 * @brief Returns a vector pointing to the left.
 * @return A vector with x = -1 and y = 0
*/
INLINE vec2_t vec2_left(void) {
    return vec2_create(-1.0f, 0.0f);
}

/**
 * @brief Returns a vector pointing to the right.
 * @return A vector with x = 1 and y = 0
*/
INLINE vec2_t vec2_right(void) {
    return vec2_create(1.0f, 0.0f);
}

/**
 * @brief Returns a vector pointing upwards.
 * @return A vector with x = 0 and y = -1
*/
INLINE vec2_t vec2_up(void) {
    return vec2_create(0.0f, -1.0f);
}

/**
 * @brief Returns a vector pointing downwards.
 * @return A vector with x = 0 and y = 1
*/
INLINE vec2_t vec2_down(void) {
    return vec2_create(0.0f, 1.0f);
}

/**
 * @brief Adds two vectors a and b.
 * @param a First vector
 * @param b Second vector
 * @return The resulting vector after addition
*/
INLINE vec2_t vec2_add(vec2_t a, vec2_t b) {
    vec2_t r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

/**
 * @brief Subtracts vector b from vector a.
 * @param a First vector
 * @param b Second vector to subtract from the first
 * @return The resulting vector after subtraction
 */
INLINE vec2_t vec2_sub(vec2_t a, vec2_t b) {
    vec2_t r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

/**
 * @brief Multiplies a vector v by a scalar s.
 * @param v The input vector
 * @param s The scalar value
 * @return The resulting vector after multiplication
*/
INLINE vec2_t vec2_mul(vec2_t v, f32 s) {
    vec2_t r;
    r.x = v.x * s;
    r.y = v.y * s;
    return r;
}

/**
 * @brief Calculates the dot product of two vectors a and b.
 * @param a First vector
 * @param b Second vector
 * @return The dot product of the two vectors
*/
INLINE f32 vec2_dot(vec2_t a, vec2_t b) {
    return (a.x * b.x) + (a.y * b.y);
}

/**
 * @brief Calculates the squared length of a vector v.
 * @param v The input vector
 * @return The squared length of the vector
*/
INLINE f32 vec2_length_sq(vec2_t v) {
    return vec2_dot(v, v);
}

/**
 * @brief Calculates the length of a vector v using a fast approximation.
 * @param v The input vector
 * @return Approximation of the length of the vector
*/
INLINE f32 vec2_length(vec2_t v) {
    f32 len_sq = vec2_length_sq(v);
    if (len_sq <= 0.0f) {
        return 0.0f;
    }

    return len_sq * rsqrtf(len_sq);
}

/**
 * @brief Normalizes a vector v using a fast approximation.
 * @param v The input vector
 * @return Approximation of the normalized vector
*/
INLINE vec2_t vec2_normalize(vec2_t v) {
    f32 len_sq = vec2_length_sq(v);
    if (len_sq < EPSILON_F) {
        return vec2_zero();
    }

    f32 inv_len = rsqrtf(len_sq);
    vec2_t r;
    r.x = v.x * inv_len;
    r.y = v.y * inv_len;

    return r;
}

/**
 * @brief Rotates a vector v by a given angle using the sine and cosine lookup tables.
 * @param v The input vector
 * @param angle The angle to rotate by in the range [0, 1024) where 1024 represents 360 degrees
 * @return The rotated vector
*/
INLINE vec2_t vec2_rotate(vec2_t v, i32 angle) {
    f32 s = de_sinf(angle);
    f32 c = de_cosf(angle);

    vec2_t r;
    r.x = (v.x * c) - (v.y * s);
    r.y = (v.x * s) + (v.y * c);

    return r;
}

/**
 * @brief Moves a position forward in the direction of a given angle by a specified speed.
 * @param position The current position
 * @param angle The direction to move in the range [0, 1024) where 1024 represents 360 degrees
 * @param speed The distance to move
 * @return The new position after moving forward
*/
INLINE vec2_t vec2_move_forward(vec2_t position, i32 angle,f32 speed) {
    position.x += de_cosf(angle) * speed;
    position.y += de_sinf(angle) * speed;

    return position;
}

//----------------------------------------------------------------
// Math utility functions
//----------------------------------------------------------------

/**
 * @brief Returns the minimum of two floating-point values.
 * @param a First value
 * @param b Second value
 * @return The minimum value
*/
INLINE f32 minf(f32 a, f32 b) {
    return (a < b) ? a : b;
}

/**
 * @brief Returns the maximum of two floating-point values.
 * @param a First value
 * @param b Second value
 * @return The maximum value
*/
INLINE f32 maxf(f32 a, f32 b) {
    return (a > b) ? a : b;
}

/**
 * @brief Clamps a floating-point value between a minimum and maximum range.
 * @param v The value to clamp
 * @param min The minimum value
 * @param max The maximum value
 * @return The clamped value
*/
INLINE f32 clampf(f32 v, f32 min, f32 max) {
    return minf(maxf(v, min), max);
}

/**
 * @brief Returns the absolute value of a floating-point number.
 * @param v The input value
 * @return The absolute value of the input
*/
INLINE f32 absf(f32 v) {
    return (v < 0.0f) ? -v : v;
}

/**
 * @brief Returns a random floating-point number between min and max.
 * @param min The minimum value
 * @param max The maximum value
 * @return A random floating-point number in the range [min, max]
*/
INLINE f32 randf(f32 min, f32 max) {
    return ((f32)rand() / (f32)RAND_MAX) * (max - min) + min;
}

/**
 * @brief Calculates the distance between two points (x1, y1) and (x2, y2) using a fast approximation.
 * @param x1 First point X coordinate
 * @param y1 First point Y coordinate
 * @param x2 Second point X coordinate
 * @param y2 Second point Y coordinate
 * @return Approximation of the distance between the two points
*/
INLINE f32 distance_pointsf(f32 x1, f32 y1, f32 x2, f32 y2) {
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;

    f32 dist_sq = dx * dx + dy * dy;
    f32 inv = rsqrtf(dist_sq);
    return dist_sq * inv;
}

/**
 * @brief Calculates the squared distance between two points (x1, y1) and (x2, y2).
 * @param x1 First point X coordinate
 * @param y1 First point Y coordinate
 * @param x2 Second point X coordinate
 * @param y2 Second point Y coordinate
 * @return Squared distance between the two points
*/
INLINE f32 distance_points_sqf(f32 x1, f32 y1, f32 x2, f32 y2) {
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;
    return dx * dx + dy * dy;
}

/**
 * @brief Calculates the squared distance between two vectors a and b.
 * @param a First vector
 * @param b Second vector
 * @return Squared distance between the two vectors
*/
INLINE f32 vec2_distance_sq(vec2_t a, vec2_t b) {
    f32 dx = b.x - a.x;
    f32 dy = b.y - a.y;
    return dx * dx + dy * dy;
}

/**
 * @brief Calculates the distance between two vectors a and b using a fast approximation.
 * @param a First vector
 * @param b Second vector
 * @return Approximation of the distance between the two vectors
*/
INLINE f32 vec2_distance(vec2_t a, vec2_t b) {
    return fsqrtf(vec2_distance_sq(a, b));
}

/**
 * @brief Calculates the angle in radians between two points (x1, y1) and (x2, y2).
 * @param x1 First point X coordinate
 * @param y1 First point Y coordinate
 * @param x2 Second point X coordinate
 * @param y2 Second point Y coordinate
 * @return The angle in radians between the two points
*/
INLINE f32 angle_between_pointsf(f32 x1, f32 y1, f32 x2, f32 y2) {
    f32 dx = x2 - x1;
    f32 dy = y2 - y1;
    return atan2f(dy, dx);
}

INLINE f32 angle_between_direction(f32 dx, f32 dy) {
    return atan2f(dy, dx);
}

//----------------------------------------------------------------
// Angle utilities
//----------------------------------------------------------------

/**
 * @brief Wraps an angle to the range [0, 1024) where 1024 represents 360 degrees.
 * @param angle The input angle
 * @return The wrapped angle in the range [0, 1024)
*/
INLINE i32 wrap_angle(i32 angle) {
    return angle & ANGLE_MASK;
}

/**
 * @brief Converts degrees to radians.
 * @param deg The angle in degrees
 * @return The angle in radians
*/
INLINE f32 deg2rad(f32 deg) {
    return deg * DEG_2_RAD_F;
}

/**
 * @brief Converts radians to degrees.
 * @param rad The angle in radians
 * @return The angle in degrees
*/
INLINE f32 rad2deg(f32 rad) {
    return rad * RAD_2_DEG_F;
}
