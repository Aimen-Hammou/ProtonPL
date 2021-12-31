#ifndef PROTON_CHUNK_H
#define PROTON_CHUNK_H

#include "Common.h"
#include "Value.h"


#define BYTE uint8_t

typedef enum {

	// TODO (Aiman): Create an OP_CONSTANT_LONG to manage 32bit values

	// ByteCode Operation to add a variable
	// Ex: OP_CONSTANT, Index of the element inside constantPool dyn array
	OP_CONSTANT,
	
	// ByteCode Operation to return from function
	OP_RETURN
}OpCode;


// This struct contains all the data needed for the bytecode translation
typedef struct {
	//Dynamic Array Variables to manage the allocation of new space
	int count;
	int capacity;

	//Dynamic Array containing the data
	BYTE *code;

	ConstantPool constantPool;

	// FIXME (Aiman): Find a smarter way to handle line reporting
	// Dynamic array containing line of each instruction
	// Has same count and capacity of BYTE *code;
	int *lines;
}Chunk;


// This function initialize a chunk struct element.
void InitChunk(Chunk *chunk);



// This function append element to the dynamic array of the chunk 
void WriteToChunk(Chunk *pChunk, BYTE value, int line);


// This function frees the chunk array ONLY. 
void FreeChunk(Chunk *pChunk);

// [ CONSTANT POOL FUNCTIONS ]

int AddConstantPool(Chunk *pChunk, Value value);
#endif
