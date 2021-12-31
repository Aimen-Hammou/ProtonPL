#ifndef PROTON_CONSTANT_POOL_H
#define PROTON_CONSTANT_POOL_H

// Author: Aiman Hammou
// Date: 31 December 2021 Basic Implementation of ConstantPool and basic functions

// Header file to manage the values declared inside Proton source code

#include "Common.h"
#include "Memory.h"

typedef double Value;

typedef struct{

	// Variables to manage dynamic array
	int count;
	int capacity;

	// Dynamic array of values
	Value *values;

}ConstantPool;


// This function initialize a ConstantPool struct element.
void InitConstantPool(ConstantPool *pConstantPool);

// This function writes a value to the constant pool
void WriteConstantPool(ConstantPool *pConstantPool, Value value);

// This function frees a ConstantPool instance.
void FreeConstantPool(ConstantPool *pConstantPool);

// This function prints the value at a given index
// Purpose is for debugging. Check Debug.h
void PrintValue(Value value);


#endif
