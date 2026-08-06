/**
 * @file arrays.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#pragma once
#include "../de.h"

/**
 * @brief Number of items in a static array
 * @param array The array to get the length of
*/
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof((array)[0]))

/**
 * @brief Size of one array item
 * @param array The array to get the item size of
*/
#define ARRAY_ITEM_SIZE(array) (sizeof((array)[0]))

/**
 * @brief Total size of array in bytes
 * @param array The array to get the total size of
*/
#define ARRAY_SIZE(array) (sizeof(array))

/**
 * @brief Get the last item in an array
 * @param array The array to get the last item of
*/
#define ARRAY_LAST(array) ((array)[ARRAY_LENGTH(array) - 1])

/**
 * @brief Clear an array by setting all bytes to zero
 * @param array The array to clear
*/
#define ARRAY_CLEAR(array) memset((array), 0, sizeof(array))

/**
 * @brief Iterate over each item in an array
 * @param type The type of the items in the array
 * @param item The loop variable for the current item
 * @param array The array to iterate over
*/
#define ARRAY_FOR_EACH(type, item, array) \
    for (type* item = (array); \
        item < (array) + ARRAY_LENGTH(array); \
        item++)

/**
 * @brief Seed the random number generator for array shuffling
*/
static inline void array_shuffle_seed(void) {
    srand((unsigned int)time(NULL));
}

/**
 * @brief Comparison function for integers
 * @param a Pointer to the first integer
 * @param b Pointer to the second integer
 * @return Negative if a < b, zero if a == b, positive if a > b
*/
static inline i32 compare_i32(const void* a, const void* b) {
    return (*(const i32*)a - *(const i32*)b);
}

/**
 * @brief Comparison function for floating-point numbers
 * @param a Pointer to the first float
 * @param b Pointer to the second float
 * @return Negative if a < b, zero if a == b, positive if a > b
*/
static inline i32 compare_f32(const void* a, const void* b) {
    f32 fa = *(const f32*)a;
    f32 fb = *(const f32*)b;

    return (fa > fb) - (fa < fb);
}

/**
 * @brief Swap the byte order of two items in an array
 * @param a Pointer to the first item
 * @param b Pointer to the second item
 * @param item_size Size of each item in bytes
*/
static inline void array_swap_bytes(void* a, void* b, size_t item_size) {
    uint8_t* pa = (uint8_t*)a;
    uint8_t* pb = (uint8_t*)b;

    while (item_size--) {
        uint8_t tmp = *pa;
        *pa++ = *pb;
        *pb++ = tmp;
    }
}

/**
 * @brief Reverse the byte order of each item in an array
 * @param arr The array to reverse
 * @param count Number of items in the array
 * @param item_size Size of each item in bytes
*/
static inline void array_reverse(void* array, size_t count, size_t item_size) {
    uint8_t* arr = (uint8_t*)array;

    for (size_t i = 0; i < count / 2; i++) {
        uint8_t* left  = arr + (i * item_size);
        uint8_t* right = arr + ((count - 1 - i) * item_size);
        array_swap_bytes(left, right, item_size);
    }
}

/**
 * @brief Shuffle the items in an array using the Fisher-Yates algorithm
 * @param array The array to shuffle
 * @param count Number of items in the array
 * @param item_size Size of each item in bytes
*/
static inline void array_shuffle(void* array, size_t count, size_t item_size) {
    uint8_t* arr = (uint8_t*)array;

    for (size_t i = count - 1; i > 0; i--) {
        size_t j = (size_t)(rand() % (i + 1));
        uint8_t* a = arr + (i * item_size);
        uint8_t* b = arr + (j * item_size);
        array_swap_bytes(a, b, item_size);
    }
}

/**
 * @brief Sort an array using the C standard library qsort function
 * @param array The array to sort
 * @param count Number of items in the array
 * @param item_size Size of each item in bytes
 * @param compare Comparison function that returns negative, zero, or positive
*/
static inline void array_sort(void* array, size_t count, size_t item_size, i32 (*compare)(const void*, const void*)) {
    qsort(array, count, item_size, compare);
}

/**
 * @brief Perform a linear search on an array
 * @param array The array to search
 * @param count Number of items in the array
 * @param item_size Size of each item in bytes
 * @param key The item to search for
 * @param compare Comparison function that returns negative, zero, or positive
 * @return The index of the found item, or -1 if not found
*/
static inline int array_linear_search(const void* array, size_t count, size_t item_size,const void* key, i32 (*compare)(const void*, const void*)) {
    const uint8_t* arr = (const uint8_t*)array;
    for (size_t i = 0; i < count; i++) {
        const void* item = arr + (i * item_size);
        if (compare(item, key) == 0) {
            return (int)i;
        }
    }
    return -1;
}

/**
 * @brief Perform a binary search on a sorted array
 * @param array The sorted array to search
 * @param count Number of items in the array
 * @param item_size Size of each item in bytes
 * @param key The item to search for
 * @param compare Comparison function that returns negative, zero, or positive
 * @return The index of the found item, or -1 if not found
*/
static inline int array_binary_search(const void* array, size_t count, size_t item_size, const void* key, i32 (*compare)(const void*, const void*)) {
    size_t left = 0;
    size_t right = count;
    const uint8_t* arr = (const uint8_t*)array;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        const void* item = arr + (mid * item_size);
        i32 result = compare(item, key);

        if (result == 0) {
            return (int)mid;
        }

        if (result < 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return -1;
}

/**
 * @brief Find the minimum item in an array
 * @param array The array to search
 * @param count Number of items in the array
 * @param item_size Size of each item in bytes
 * @param compare Comparison function that returns negative, zero, or positive
 * @return Pointer to the minimum item, or NULL if the array is empty
*/
static inline void* array_min(void* array, size_t count, size_t item_size, i32 (*compare)(const void*, const void*)) {
    if (count == 0) {
        return NULL;
    }

    uint8_t* arr = (uint8_t*)array;
    void* min_item = arr;
    for (size_t i = 1; i < count; i++) {
        void* current = arr + (i * item_size);
        if (compare(current, min_item) < 0) {
            min_item = current;
        }
    }

    return min_item;
}

/**
 * @brief Find the maximum item in an array
 * @param array The array to search
 * @param count Number of items in the array
 * @param item_size Size of each item in bytes
 * @param compare Comparison function that returns negative, zero, or positive
 * @return Pointer to the maximum item, or NULL if the array is empty
*/
static inline void* array_max(void* array, size_t count, size_t item_size, i32 (*compare)(const void*, const void*)) {
    if (count == 0) {
        return NULL;
    }

    uint8_t* arr = (uint8_t*)array;
    void* max_item = arr;
    for (size_t i = 1; i < count; i++) {
        void* current = arr + (i * item_size);
        if (compare(current, max_item) > 0) {
            max_item = current;
        }
    }

    return max_item;
}
