#ifndef PROTON_DEBUG_H
#define PROTON_DEBUG_H

// Author: Aiman Hammou
// Date: 31 December 2021

// This file is for debugging purpose, to make the life of Language/VM Hackers easier.
//
// This file SHOULD NEVER be used by final users.

#include <stdio.h>

#include "Common.h"
#include "Chunk.h"

// This function disassembles the entire chunk
void DisassembleChunk(Chunk *pChunk, const char *debugName);

// This function dissassembles a specific instruction
int  DisassembleInstruction(Chunk *pChunk, int offset);

#endif
