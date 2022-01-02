// Author: Aiman Hammou <developer.aiman@outlook.com>

#include "Debug.h"


// Static functions

// This function manages the print of a basic instruction.
//
// By basic instruction I mean all the instruction that don't have data appended
// to them.
static int BasicInstruction(const char *strInstructionName, int iOffset){

	printf("%s\n", strInstructionName);
	return (iOffset + 1);
}

static int ConstantInstruction( 
	const char *strInstructionName, 
	Chunk *pChunk, 
	int iOffset
) {

	BYTE bConstant = pChunk->code[iOffset + 1];

	printf("%-16s %4d -> '", strInstructionName, bConstant);

	PrintValue(pChunk->constantPool.values[bConstant]);

	printf("'\n");

	// +1 for the opcode, +1 for the data
	return (iOffset + 2);
}


// Header functions
void DisassembleChunk(Chunk *pChunk, const char *debugName) {

	printf("============%s============\n", debugName);

	// We iterate from the first element offset = 0
	// to the last one, which is the pChunk->count
	// Increment of the offset is done inside the DisassembleInstruction function
	for (int iOffset = 0; iOffset < pChunk->count; )
		iOffset = DisassembleInstruction(pChunk, iOffset);
	
}

int DisassembleInstruction(Chunk *pChunk, int iOffset) {
	
	printf("%04d ", pChunk->lines[iOffset]);
	printf("%04d\t", iOffset);

	// Get the data at the current offset
	BYTE bInstruction = pChunk->code[iOffset];

	// Each instruction has his own printing function
	switch(bInstruction){
		case OP_RETURN:
			return BasicInstruction("OP_RETURN", iOffset);

		case OP_CONSTANT:
			return ConstantInstruction("OP_CONSTANT", pChunk, iOffset);

		default:
			printf("Unknown instruction at offset %04d\n", iOffset);
	} 

	return (iOffset + 1);
}