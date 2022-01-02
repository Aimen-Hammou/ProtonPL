#include "VirtualMachine.h"

// Author: Aiman Hammou <developer.aiman@outlook.com>


//Static functions

// This is so far ( 2 January 2022 ) the most important function in Proton

// Internal VM Helper Function that handles the interpretation of the bytecode source
// and returns the result in term of interpretation (InterpreterResult)
	
static InterpretResult Run() {

	for (;;) {

		BYTE bCurrentInstruction = 0;
		int iConstantIdx = 0;

		//if debug logging is actived print each instruction before executing it
#ifdef DEBUG_EXECUTION_LOG
		DisassembleInstruction(VM.chunk, (int)(VM.InstructionPointer - VM.chunk->code));
#endif

		// To perform the correct operation we need to know the current OP_CODE
		// This operation is called DISPATCHING
		//
		// Get the current instruction and move the IP to the next one.
		switch ((bCurrentInstruction = *VM.InstructionPointer++)) 
		{
			case OP_CONSTANT:

				// Get the index of the constant and move the IP 
				iConstantIdx = *VM.InstructionPointer++;

				Value vConstant = VM.chunk->constantPool.values[iConstantIdx];
				
				PrintValue(vConstant);
				printf("\n");

				break;

			case OP_RETURN:
				return INTERPRET_OK;
		}
	}
}

void InitVM(){
	;
}

void FreeVM() {
	;
}

InterpretResult Interpret(Chunk *pChunk) {

	// "Copy" the chunk into the VM.
	VM.chunk = pChunk;

	// Set the instruction pointer to the first element (op_code) of the chunk
	//
	// The InstructionPointer always points to the next instruction
	// not the one being handled.
	VM.InstructionPointer = VM.chunk->code;



	// Internal helper function that actually runs the chunk containing 
	// the bytecode source and reports the InterpreterResult.
	return Run();
}