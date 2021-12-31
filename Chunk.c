#include "Chunk.h"
#include "Memory.h"

void InitChunk(Chunk *chunk) {
	
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	chunk->lines = NULL;

	InitConstantPool(&chunk->constantPool);
}

void WriteToChunk(Chunk *pChunk, BYTE value, int line)
{
	//Check if dynamic array is full.
	// We do count + 1, instead of simply count to manage the case of the init
	if (pChunk->capacity < pChunk->count + 1)
	{
		int oldCapacity = pChunk->capacity;
		
		//Get new capacity
		pChunk->capacity = GROW_CAPACITY(oldCapacity);

		//Grow the byte array
		pChunk->code = GROW_ARRAY(
			BYTE,
			pChunk->code,
			oldCapacity,
			pChunk->capacity // new capacity
		);

		// Line dynamic array grows simultaneously with code.
		pChunk->lines = GROW_ARRAY(
			int,
			pChunk->lines,
			oldCapacity,
			pChunk->capacity // new capacity
		);

	}

	//Otherwise we simply write to the array and the corresponding line
	pChunk->code[pChunk->count] = value;
	pChunk->lines[pChunk->count] = line;

	pChunk->count++;

}

// We don't free the object chunk itself, but the data in it.
// The reason for this is because the chunk will be re-used
// So instead of allocating a new object later on on the heap
// we keep the one allocated.
void FreeChunk(Chunk *pChunk) {

	FREE_ARRAY(BYTE, pChunk->code, pChunk->capacity);
	FREE_ARRAY(int , pChunk->lines, pChunk->capacity);

	InitChunk(pChunk);
}

int AddConstantPool(Chunk *pChunk, Value value){

	// Note: constalPool.count gets incremented
	WriteConstantPool(&pChunk->constantPool, value);

	return pChunk->constantPool.count - 1;
}

