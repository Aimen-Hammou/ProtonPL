#ifndef PROTON_VIRTUAL_MACHINE_H
#define PROTON_VIRTUAL_MACHINE_H

// Author: Aiman Hammou <developer.aiman@outlook.com>

#include "Common.h"
#include "Chunk.h"
#include "DebuG.h"

typedef struct
{
	// The bytecode representation of the source code.
	Chunk *chunk;

	// Instruction Pointer that works as index of the current operation being perfomed
	// You can think of it in terms of assembly language
	//
	// We use a pointer instead of something like an integer that works as index
	// because is way faster to dereference a pointer that to lookup via index
	BYTE *InstructionPointer;

	// Stack that keeps track of data.
	//
	// Max size is 256 which can lead to STACK OVERFLOW but
	// for now we keep it static, and will, later on, fix this.
	Value STACK[STACK_MAX];

	//Pointer to the top of the stack. 
	//
	// We use a pointer instead of something like an integer that works as index
	// because is way faster to dereference a pointer that to lookup via index
	//
	// It points to the position past the last element
	// This is due to the fact that C supports Pointers pointing after the end of the array
	// Meanwhile doesn't accept a negative index.
	// So an empty stack has a pointer to the position 0, instead of -1 which leds to undefined behaviour
	Value *StackTopPtr;

}VirtualMachine;

//Status of the interpretation 
// The interpreter will use this to set the correct exit code.
typedef enum
{
	NONE = 0,

	INTERPRET_OK,
	INTERPRET_COMPILER_ERROR,
	INTERPRET_RUNTIME_ERROR
}InterpretResult;

// A good code standard would not reccomend the use of a global variable
// But I decided to use it anyway to make the code easier to read without
// having to pass the VirtualMachine variable each time.
VirtualMachine VM;

// Function to initialize the component of the virtual machine.
void InitVM();

// Function to free the memory allocated for certain member of the virtual machine
void FreeVM();

// Entry point of the VM which runs the bytecode and returns the InterpretResult
InterpretResult Interpret(Chunk *pChunk);


// Stack operations

// Push an element value to the stack.
void Push(Value value);

// Pop the top element from the stack.
Value Pop();
#endif
