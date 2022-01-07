#ifndef PROTON_SCANNER_H
#define PROTON_SCANNER_H

#include "Common.h"
#include "Token.h"

typedef enum {
	// Single-character tokens.
	TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
	TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
	TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
	TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,

	// One or two character tokens.
	TOKEN_BANG, TOKEN_BANG_EQUAL,
	TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
	TOKEN_GREATER, TOKEN_GREATER_EQUAL,
	TOKEN_LESS, TOKEN_LESS_EQUAL,

	// Literals.
	TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,

	// Keywords.
	TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
	TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
	TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
	TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE,

	TOKEN_ERROR, TOKEN_EOF
} TokenType;

typedef struct {
	
	TokenType type;

	// Ptr to the Source Code where the Token is
	const char *start;
	
	// Length of the value of the token
	int length;

	// Traceback purpose
	int line;
}Token;

typedef struct {

	// Pointer to the start of the Lexeme being scanned
	const char *start; 
	// Pointer to the current Position of the Lexeme being scanned
	const char *current;

	//EXAMPLE: print "Proton"
	//               ^    ^
	//               |    |
	//             start, current
	
	//Tracking of the line being scanned for error reporting.
	int line;
}Scanner_S;


// A good code standard would not reccomend the use of a global variable
// But I decided to use it anyway to make the code easier to read without
// having to pass the Scanner_S variable each time.
Scanner_S Scanner;


// Initialize the scanner struct with the file/REPL content
void InitScanner(const char *source);

// Proton doesn't execute the scanning of the entire file beforehand
// Instead we scan a token, or two, each time and pass it to the compiler
// for the use of them.
// So the compiler Eats Tokens as we scan them and pass to it.
// There is no AST Building because I want to avoid Memory Spacing and the cost of it.
Token ScanToken();

#endif
