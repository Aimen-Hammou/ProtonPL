#include "Memory.h"

//Check Memory.h for documentation
void *Reallocate(void *pElement, size_t oldSize, size_t newSize){

	//We want to free the pointer
	if (newSize == 0){
		free(pElement);
		return NULL; 
	}

	void *pResult = realloc(pElement, newSize);
	
	//Check if realloc failed.
	//Maybe using an IF statement instead of an assert?
	assert(pResult != NULL);

	return pResult;
}