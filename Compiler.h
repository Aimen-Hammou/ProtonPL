#ifndef PROTON_COMPILER_H
#define PROTON_COMPILER_H

#include "Common.h"

// Compiler Pipeline runs the scanner which converts the source
// into tokens which will be converted into bytecode and 
// later on evaluated
void Compile(const char *source);

#endif
