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

#endif
