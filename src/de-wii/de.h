/**
 * @file de.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Console-specific includes
#include <gccore.h>
#include <wiiuse/wpad.h>

// SDL2 includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))
#define FIELD_LEN(obj, field) (sizeof((obj)->field) / sizeof((obj)->field[0]))

#define INLINE static inline __attribute__((always_inline)) 
#define ALIGN32 __attribute__((aligned(32))) 
#define RESTRICT __restrict__

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define H_WINDOW_WIDTH 320
#define H_WINDOW_HEIGHT 240

#define SIN_LUT_SIZE 2048
#define ANGLE_MASK (SIN_LUT_SIZE - 1)
#define TABLE_SCALE (SIN_LUT_SIZE / 360.0f)

#define MAP_WIDTH 20
#define MAP_HEIGHT 15
#define MAP_TILE_SIZE 32
#define MAX_ENTITIES 128

#define DIV2   0.5f
#define DIV3   0.3333333333f
#define DIV4   0.25f
#define DIV5   0.2f
#define DIV6   0.1666666667f
#define DIV7   0.1428571429f
#define DIV8   0.125f
#define DIV9   0.1111111111f
#define DIV10  0.1f
#define DIV16  0.0625f
#define DIV32  0.03125f
#define DIV64  0.015625f
#define DIV128 0.0078125f

#define PI_F 3.1415927f
#define TWO_PI_F (PI_F * 2.0f)
#define HALF_PI_F (PI_F * 0.5f)
#define DEG_2_RAD_F (PI_F / 180.0f)
#define RAD_2_DEG_F (180.0f / PI_F)
#define EPSILON_F 0.00001f

#define BIT_0 (1u << 0)
#define BIT_1 (1u << 1)
#define BIT_2 (1u << 2)
#define BIT_3 (1u << 3)
#define BIT_4 (1u << 4)
#define BIT_5 (1u << 5)
#define BIT_6 (1u << 6)
#define BIT_7 (1u << 7)

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float   f32;
typedef double  f64;
typedef u16 entity_t;

typedef struct {
    u8 value;
} byte_t;
