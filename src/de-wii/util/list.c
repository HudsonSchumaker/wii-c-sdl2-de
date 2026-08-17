/**
* @file list.c
* @brief Implementation of a dynamic list in C.
* @author Hudson Schumaker
* @version 1.0.0
* @copyright Copyright (c) 2024, Dodoi-Lab
*/
#include "list.h"
#define INITIAL_CAPACITY 8
#define GROWTH_FACTOR 2

void list_init(list_t* list, size_t type_size) {
	list->size = 0;
	list->capacity = INITIAL_CAPACITY; // initial capacity set
	list->type_size = type_size;
	list->value = malloc(list->capacity * list->type_size);
}

bool list_resize(list_t* list, size_t new_capacity) {
	if (new_capacity <= list->capacity) {
        return true;
    }
    
	void* new_value = realloc(list->value, new_capacity * list->type_size);
    if (!new_value) {
        return false;
    }
    
	list->value = new_value;
    list->capacity = new_capacity;
    return true;
}

bool list_push_back(list_t* list, const void* value) {
	if (list->size == list->capacity && !list_resize(list, list->capacity * GROWTH_FACTOR)) {
        return false; // out of memory, entry was not added
    }
    
	memcpy((char*)list->value + list->size * list->type_size, value, list->type_size);
    list->size++;
    return true;
}

void* list_get(const list_t* list, size_t index) {
	if (index < list->size) {
		return (char*)list->value + index * list->type_size;
	}
	return NULL;
}

void list_sort(const list_t* list, int (*comparator)(const void*, const void*)) {
    if (list == NULL || list->value == NULL || list->size <= 1) {
        return; // Nothing to sort
    }

    qsort(list->value, list->size, list->type_size, comparator);
}

size_t list_size(const list_t* list) {
	return list->size;
}

void list_free(list_t* list) {
	free(list->value);
	list->value = NULL;
	list->size = 0;
	list->capacity = 0;
	list->type_size = 0;
}
