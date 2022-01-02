// Author: Aiman Hammou <developer.aiman@outlook.com>

#include "Value.h"


void InitConstantPool(ConstantPool *pConstantPool) {

	pConstantPool->count = 0;
	pConstantPool->capacity = 0;
	pConstantPool->values = NULL;

}

void WriteConstantPool(ConstantPool *pConstantPool, Value value){
	
	// Check if array is full
	if (pConstantPool->capacity < pConstantPool->count + 1) {

		int iOldCapacity = pConstantPool->capacity;

		//Get new capacity
		pConstantPool->capacity = GROW_CAPACITY(iOldCapacity);

		//Allocate new space and copy array
		pConstantPool->values = GROW_ARRAY(
			Value,
			pConstantPool->values,
			iOldCapacity,
			pConstantPool->capacity
		);
	}

	pConstantPool->values[pConstantPool->count] = value;
	pConstantPool->count++;
}

// We don't free the object ConstantPool itself, but the data in it.
// The reason for this is because the chunk will be re-used
// So instead of allocating a new object later on on the heap
// we keep the one allocated.
void FreeConstantPool(ConstantPool *pConstantPool) {

	FREE_ARRAY(Value, 
			   pConstantPool->values, 
		       pConstantPool->capacity);

	InitConstantPool(pConstantPool);

}

void PrintValue(Value value){
	
	printf("%g", value);

}