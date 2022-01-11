#include "Compiler.h"
#include "Scanner.h"

//					Note regarding the parsing technique
//
// The parser uses the Pratt Parser Technique, which justifies the parsing rules table below.
// Usually Programming Languages have a Parser that
// performs two different actions: creating the AST and trasverse it.
// I take the old approach and merge them together, which is not very suitable
// for programming languages, but in the case of Proton is possible, without
// having to worry about much. The reason why It should be avoided is because
// it lets the compiler/parser have a little semantic context, which a full AST
// gives. In the future versions of Proton probably the language will either 
// work its way up without a VM or will build an AST on top of it and later
// generate code. Somewhere (maybe in VirtualMachine.h) I give the justification
// on why I don't want to use the AST ( spoiler: memory spacing which ruins performance)
// But nothing comes without a trade-off in life so I have to either optimize 
// the bytecode or use for optimizing technique on the scanner, AST, Visitor etc. etc.
//
// In the near future I will probably rewitre Proton without a VM, but just an AST & Visitor.

Parser parser;

// ============================================================================
//						Error notification function
// ============================================================================


static void ErrorAt(Token *ptrToken, const char *message)
{
	fprintf(stderr, "[line %d] Error ", ptrToken->line);

	if (ptrToken->type == TOKEN_EOF)
	{
		fprintf(stderr, " at the end of file");
	}
	else if (ptrToken->type == TOKEN_ERROR)
		;
	else
	{
		fprintf(stderr, "at %.*s ", ptrToken->length, ptrToken->start);
	}

	fprintf(stderr, ": %s\n", message);
	
	// Raise the panic mode flag so we don't have a cascade of errors
	// we are not C++
	parser.panicMode = true;
	parser.hadError  = true;

}
static void Error(const char *message)
{
	if (parser.panicMode)
		return;

	ErrorAt(&parser.current, message);
}

// This function takes the token stream and get the next token each time
// but before doing he saves the current token into the previous field 
// of the parser.
// @param NONE
// @return void
static void Advance()
{
	parser.previous = parser.current;

	// Proton Lexer doesn't report lexical errors.
	// Parser does.

	// Trasverse the Token Stream
	for (;;)
	{
		parser.current = ScanToken();

		if (parser.current.type != TOKEN_ERROR)
			break;

		Error(parser.current.start);
	}
}


bool Compile(const char *source) {

	// Initialization section start
	InitScanner(source);
	parser.hadError  = false;
	parser.panicMode = false;
	// Initialization section end
	
	// Get the first Token
	Advance();
	
	return !parser.hadError;
}