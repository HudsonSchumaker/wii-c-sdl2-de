/**
 * @file math2d.c
 * @author Hudson Schumaker
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "math2d.h"
static f32 sin_table[SIN_LUT_SIZE];

void build_trigo_tables(void) {
    for (i32 i = 0; i < SIN_LUT_SIZE; i++) {
        f32 angle =  ((f32)i / SIN_LUT_SIZE) * TWO_PI_F;
        sin_table[i] = sinf(angle);
    }
}

i32 degrees_to_index(f32 degrees) {
    return (i32)(degrees * TABLE_SCALE) & ANGLE_MASK;
}

f32 de_sinf(i32 angle) {
    return sin_table[angle & ANGLE_MASK];
}

f32 de_cosf(i32 angle) {
    return sin_table[(angle + (SIN_LUT_SIZE >> 2)) & ANGLE_MASK];
}

f32 de_tanf(i32 angle) {
    f32 cos = de_cosf(angle);
    if (cos > -0.0001f && cos < 0.0001f) {
        return 0.0f;
    }

    return de_sinf(angle) / cos;
}
