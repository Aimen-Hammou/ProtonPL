#ifndef PROTON_COMPILER_H
#define PROTON_COMPILER_H

#include "Common.h"
#include "Chunk.h"
#include "Token.h"
#include "Scanner.h"

typedef struct {
	Token current;
	Token previous;

	bool hadError;

	// If the parser encounters an error we don't want to have the compiler
	// print a list of error deriving from the first one.
	// Will be set inside the ErrorAt(Token, message) and checked in Error(const char*)
	bool panicMode;
} Parser;

// Compile the source code into ByteCode and put it inside the chunk code.
// @param source "Proton Source Code"
// @parma chunk "Chunk where put the bytecode"
//@return true if Compile was a success, otherwise false.
bool Compile(const char *source, Chunk *chunk);

#endif
