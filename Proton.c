#include "Common.h"	
#include "Chunk.h"
#include "Debug.h"

int main(int argc, char *argv[]){
	
	//Test: 31 December 2021

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

	return 0;
}
