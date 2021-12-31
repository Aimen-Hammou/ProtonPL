#ifndef PROTON_MEMORY_H
#define PROTON_MEMORY_H

// Author: Aiman Hammou
// Date: 31 December 2021

/*
 *  This file contains all the function regarding memory manipulation
 *  of the dynamic array and so forth.
 */

#include "Common.h"

//Macro function that grows the capacity given the old one
#define GROW_CAPACITY(oldCapacity) \
	( (oldCapacity) < 8 ? 8 : (oldCapacity) * 2)


//Macro function that grow the dynamic array by reallocate-ing it
//
//We use a macro instead of calling reallocate directly due to the
//ability of macro functions to pass a type
#define GROW_ARRAY(type, ptr, oldCap, newCap) \
	(type *)Reallocate(ptr, sizeof(type) * (oldCap), \
		sizeof(type) * (newCap))


//Macro function that frees the pointer
//
//We use a macro instead of calling reallocate directly due to the
//ability of macro functions to pass a type
#define FREE_ARRAY(type, ptr, capacity) \
	Reallocate(ptr, sizeof(type) * capacity, 0)

//Function to reallocate the dynamic array
//It can also be used to free the dynamic array
//
// oldSize = 0, newSize != 0 -> Allocate new block
// oldSize != 0, newSize = 0 -> Free the pElement
// oldSize != 0, newSize != 0 && newSize < oldSize -> Shrink the pElement
// oldSize != 0, newSize != 0 && newSize > oldSize -> Grow the pElement
void *Reallocate(void *pElement, size_t oldSize, size_t newSize);

#endif
