/**
 * @file easy_curve.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_EASY_CURVE_H
#define DE_EASY_CURVE_H

#include "../de.h"

/**
 * @brief Linearly interpolates between two floating-point values a and b by a factor of t.
 * @param a The start value
 * @param b The end value
 * @param t The interpolation factor in the range [0, 1]
 * @return The interpolated value
*/
INLINE f32 lerpf(f32 a, f32 b, f32 t) {
    return a + (b - a) * t;
}

/**
 * @brief Clamps a floating-point value t to the range [0, 1].
 * @param t The input value to clamp
 * @return The clamped value in the range [0, 1]
*/
INLINE f32 clamp01(f32 t) {
    if (t < 0.0f) return 0.0f;
    if (t > 1.0f) return 1.0f;
    return t;
}

//-----------------------------------------------------------------
// Linear
//-----------------------------------------------------------------

/**
 * @brief Eases linearly with no acceleration or deceleration.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_linear(f32 t) {
    return clamp01(t);
}

//-----------------------------------------------------------------
// Quadratic
//-----------------------------------------------------------------

/**
 * @brief Eases in with a quadratic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_in_quad(f32 t) {
    return t * t;
}

/**
 * @brief Eases out with a quadratic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_out_quad(f32 t) {
    return 1.0f - (1.0f - t) * (1.0f - t);
}

/**
 * @brief Eases in and out with a quadratic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_in_out_quad(f32 t) {
    if (t < 0.5f) {
        return 2.0f * t * t;
    }
    return 1.0f - powf(-2.0f * t + 2.0f, 2.0f) * 0.5f;
}

/**
 * @brief Eases out and in with a quadratic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_out_in_quad(f32 t) {
    if (t < 0.5f) {
        return 0.5f * ease_out_quad(t * 2.0f);
    }
    return 0.5f * ease_in_quad((t - 0.5f) * 2.0f) + 0.5f;
}

//-----------------------------------------------------------------
// Cubic
//-----------------------------------------------------------------

/**
 * @brief Eases in with a cubic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_in_cubic(f32 t) {
    return t * t * t;
}

/**
 * @brief Eases out with a cubic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_out_cubic(f32 t) {
    f32 u = 1.0f - t;
    return 1.0f - (u * u * u);
}

/**
 * @brief Eases in and out with a cubic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_in_out_cubic(f32 t) {
    if (t < 0.5f) {
        return 4.0f * t * t * t;
    }

    f32 u = -2.0f * t + 2.0f;
    return 1.0f - (u * u * u) * 0.5f;
}

/**
 * @brief Eases out and in with a cubic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_out_in_cubic(f32 t) {
    if (t < 0.5f) {
        return 0.5f * ease_out_cubic(t * 2.0f);
    }

    return 0.5f * ease_in_cubic((t - 0.5f) * 2.0f) + 0.5f;
}

//-----------------------------------------------------------------
// Quartic
//-----------------------------------------------------------------

/**
 * @brief Eases in with a quartic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_in_quart(f32 t) {
    return t * t * t * t;
}

/**
 * @brief Eases out with a quartic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_out_quart(f32 t) {
    f32 u = 1.0f - t;
    return 1.0f - (u * u * u * u);
}

/**
 * @brief Eases in and out with a quartic function.
 * @param t The interpolation factor in the range [0, 1]
 * @return The eased value
*/
INLINE f32 ease_in_out_quart(f32 t) {
    if (t < 0.5f) {
        return 8.0f * t * t * t * t;
    }

    f32 u = -2.0f * t + 2.0f;
    return 1.0f - (u * u * u * u) * 0.5f;
}

#endif // DE_EASY_CURVE_H
