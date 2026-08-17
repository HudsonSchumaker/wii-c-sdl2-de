/**
* @file list.h
* @brief Header file for a dynamic list implementation in C. 
* @author Hudson Schumaker
* @version 1.0.0
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_LIST_H
#define DE_LIST_H

#include "../de.h"

typedef struct {
	void* value;
	size_t size;
	size_t capacity;
	size_t type_size;
} list_t;

/**
 * @brief Initialize a dynamic list
 * @param list Pointer to the list
 * @param type_size Size of the type stored in the list
 */
void list_init(list_t* list, size_t type_size);

/**
 * @brief Resize the list to a new capacity
 * @param list Pointer to the list
 * @param new_capacity New capacity for the list
 * @return true if successful, false otherwise
 */
bool list_resize(list_t* list, size_t new_capacity);

/**
 * @brief Add an item to the end of the list
 * @param list Pointer to the list
 * @param value Pointer to the value to add
 * @return true if successful, false otherwise
 */
bool list_push_back(list_t* list, const void* value);
/**
 * @brief Get an item from the list by index
 * @param list Pointer to the list
 * @param index Index of the item
 * @return Pointer to the item, or NULL if index is out of bounds
 */
void* list_get(const list_t* list, size_t index);

/**
 * @brief Sort the list using a comparator function
 * @param list Pointer to the list
 * @param comparator Comparison function that returns negative, zero, or positive
 */
void list_sort(const list_t* list, int (*comparator)(const void*, const void*));

/**
 * @brief Get the number of items in the list
 * @param list Pointer to the list
 * @return Number of items in the list
 */
size_t list_size(const list_t* list);

/**
 * @brief Free the memory used by the list
 * @param list Pointer to the list
 */
void list_free(list_t* list);

#endif // DE_LIST_H
