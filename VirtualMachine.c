#include "VirtualMachine.h"
#include "Compiler.h"

// Author: Aiman Hammou <developer.aiman@outlook.com>

//STATIC FUNCTION SECTION

// Internal VM Helper Function that handles the interpretation of the bytecode source
// and returns the result in term of interpretation (InterpreterResult)

static void ResetStack(){

	//The top will now point to the first element so old values will be written
	VM.StackTopPtr = VM.STACK; 
}


#define BINARY_OPERATION(operation) \
		do{							\
			Value b = Pop();		\
			Value a = Pop();		\
									\
			Push(a operation b);	\
		}while(0);					\
		

static InterpretResult Run() {

	for (;;) {

		BYTE bCurrentInstruction = 0;
		int iConstantIdx = 0;

		//if debug logging is actived print each instruction before executing it
	
#ifdef DEBUG_EXECUTION_LOG

		// Stack Logging
		printf("	");

		// Iterate thru the stack
		for (Value *StackIterator = VM.STACK; 
			StackIterator < VM.StackTopPtr;
			StackIterator++) {

			printf("[ "); 
			PrintValue(*StackIterator);
			printf(" ]");
		}

		printf("\n");

		//Instruction Logging
		DisassembleInstruction(VM.chunk, (int)(VM.InstructionPointer - VM.chunk->code));
#endif

		// To perform the correct operation we need to know the current OP_CODE
		// This operation is called DISPATCHING
		//
		// Get the current instruction and move the IP to the next one.
		switch ((bCurrentInstruction = (*VM.InstructionPointer++))) 
		{
			case OP_CONSTANT:

				// Get the index of the constant and move the IP 
				iConstantIdx = *VM.InstructionPointer++;

				Value vConstant = VM.chunk->constantPool.values[iConstantIdx];
				
				Push(vConstant); 

				break;

			case OP_NEGATE:
				// As mentioned in Chunk.h the value has to be already pushed in the stack
				Push(-Pop());
				break;
			
			case OP_ADD:
				BINARY_OPERATION(+);
				break;
			case OP_SUBSTRACT:
				BINARY_OPERATION(-);
				break;
			case OP_MULTIPLY:
				BINARY_OPERATION(*);
				break;
			case OP_DIVIDE:
				BINARY_OPERATION(/);
				break;

			case OP_RETURN:
				return INTERPRET_OK;
		}
	}
}

// END OF STATIC FUNCTIONS SECTION

void InitVM(){
	ResetStack();
}

void FreeVM() {
	;
}


InterpretResult Interpret(const char *source){
	Compile(source);
	return INTERPRET_OK;
}

void Push(Value value) {
	*VM.StackTopPtr = value;
	 VM.StackTopPtr++;
}


Value Pop(){
	
	VM.StackTopPtr--;
	return *VM.StackTopPtr;
}