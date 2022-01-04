#include "Common.h"	
#include "Chunk.h"
#include "Debug.h"
#include "VirtualMachine.h"

// Author: Aiman Hammou <developer.aiman@outlook.com>

void __FIRST_TEST()
{
	// Date: 31 December 2021

	//Create chunk
	Chunk chunkObject;

	//Init the chunk
	InitChunk(&chunkObject);


	// Add value to constant pool of chunk and get index
	int iConstant = AddConstantPool(&chunkObject, 1.2);


	//Write to the chunk the opcode
	WriteToChunk(&chunkObject, OP_CONSTANT, 123);

	//Write to the chunk the index of the constant
	WriteToChunk(&chunkObject, iConstant, 123);

	//Write to the chunk
	WriteToChunk(&chunkObject, OP_RETURN, 123);

	//Debug print of the chunk
	DisassembleChunk(&chunkObject, "First Test");

	//Free the chunk
	FreeChunk(&chunkObject);
}

void __SECOND_TEST()
{
	//Date: 02 January 2022: Added the VM to the example


	//Create chunk
	Chunk chunkObject;

	//Init the Virtual Machine and the chunk
	InitVM();
	InitChunk(&chunkObject);


	// Add value to constant pool of chunk and get index
	int iConstant = AddConstantPool(&chunkObject, 1.2);


	//Write to the chunk the opcode
	WriteToChunk(&chunkObject, OP_CONSTANT, 123);

	//Write to the chunk the index of the constant
	WriteToChunk(&chunkObject, iConstant, 123);

	//Write to the chunk
	WriteToChunk(&chunkObject, OP_RETURN, 123);

	//Debug print of the chunk
	DisassembleChunk(&chunkObject, "Second Test");

	// Vm executes the bytecode source code (entry point)
	Interpret(&chunkObject);

	//Free the VirtualMachine and the chunk
	FreeVM();
	FreeChunk(&chunkObject);
}

void __THIRD_TEST()
{
	//Date: 04 January 2022: Testing Stack and OP_NEGATE


	//Create chunk
	Chunk chunkObject;

	//Init the Virtual Machine and the chunk
	InitVM();
	InitChunk(&chunkObject);


	// Add value to constant pool of chunk and get index
	int iConstant = AddConstantPool(&chunkObject, 1.2);
	int iConstant2 = AddConstantPool(&chunkObject, 2.5);

	//Write to the chunk the opcode
	WriteToChunk(&chunkObject, OP_CONSTANT, 123);

	//Write to the chunk the index of the constant
	WriteToChunk(&chunkObject, iConstant, 123);

	//Write to the chunk the opcode
	WriteToChunk(&chunkObject, OP_CONSTANT, 123);

	//Write to the chunk the index of the constant
	WriteToChunk(&chunkObject, iConstant2, 123);

	// Negate the value
	WriteToChunk(&chunkObject, OP_ADD, 123);

	//Write to the chunk
	WriteToChunk(&chunkObject, OP_RETURN, 123);

	// Vm executes the bytecode source code (entry point)
	Interpret(&chunkObject);

	//Free the VirtualMachine and the chunk
	FreeVM();
	FreeChunk(&chunkObject);
}

int main(int argc, char *argv[]){
	
	__THIRD_TEST();

	return 0;
}
