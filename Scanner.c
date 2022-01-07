#include "Scanner.h"

// INTERNAL FUNCTION

static bool isAtEnd() {
	return *Scanner.current == '\0';
}

static bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}

static bool isAlpha(char c) {
	return (c >= 'a' && c <= 'z') ||
		   (c >= 'A' && c <= 'Z') ||
		    c == '_';
}

static Token MakeToken(TokenType type) {
	Token tok;
	
	tok.type = type;
	tok.start = Scanner.start;
	tok.length = (int)(Scanner.current - Scanner.start);
	tok.line = Scanner.line;

	return tok;
}

static Token ErrorToken(const char *message) {
	Token errorTok;

	errorTok.type = TOKEN_ERROR;
	errorTok.length = strlen(message);
	errorTok.start = message;
	errorTok.line = Scanner.line;

	return errorTok;
}

static char Advance() {
	return *Scanner.current++;
}

static bool Match(char expected) {
	if (isAtEnd())
		return false;

	if (*Scanner.current != expected)
		return false;

	Scanner.current++;
	return true;
}

static char Peek() {
	return *Scanner.current;
}

static char PeekNext() {
	return(isAtEnd() ? '\0' : *(Scanner.current + 1));
}


static void SkipWhitespaces() {

	for (;;) {

		char c = Peek();

		switch (c) {
			case ' ':
			case '\r':
			case '\t':
				Advance();
				break;
			case '\n':
				Scanner.line++;
				Advance();
				break;

			case '/': // For now only one line comments are supported
				if (PeekNext() == '/')
					while (Peek() != '\n' && !isAtEnd())
						Advance();
				break;

			default:
				return;
		}
	}
}


static Token String() {

	//As long as we didn't counter '"' and not end of fike
	while (Peek() != '"' && !isAtEnd()) {
		if (Peek() == '\n') // We support multi line strings
			Scanner.line++;
		Advance();
	}

	// We exited the while loop above because we reached the end of file
	// And haven't encountered a closing '"'
	if (isAtEnd())
		return ErrorToken("ERROR: Unterminated String");

	// Skip Closing '"'
	Advance();
	return MakeToken(TOKEN_STRING);
}

static Token Number() {

	while (isDigit(Peek()))
		Advance();

	if (Peek() == '.' && isDigit(PeekNext())) // float number
	{
		//consume the fractional point
		Advance();

		while (isDigit(Peek()))
			Advance();
	}

	return MakeToken(TOKEN_NUMBER);

}

static TokenType CheckKeyword(int start, int length, char *rest, TokenType type)
{
	if (
		Scanner.current - Scanner.start == start + length
		&&
		memcmp(Scanner.start + start, rest, length) == 0
		)
		return type;

	return TOKEN_IDENTIFIER;
}

//Keyword checking
static TokenType IdentifierType() {
	switch (Scanner.start[0]) {
		case 'a': return CheckKeyword(1, 2, "nd", TOKEN_AND);
		case 'c': return CheckKeyword(1, 4, "lass", TOKEN_CLASS);
		case 'e': return CheckKeyword(1, 3, "lse", TOKEN_ELSE);
		case 'i': return CheckKeyword(1, 1, "f", TOKEN_IF);
		case 'n': return CheckKeyword(1, 2, "il", TOKEN_NIL);
		case 'o': return CheckKeyword(1, 1, "r", TOKEN_OR);
		case 'p': return CheckKeyword(1, 4, "rint", TOKEN_PRINT);
		case 'r': return CheckKeyword(1, 5, "eturn", TOKEN_RETURN);
		case 's': return CheckKeyword(1, 4, "uper", TOKEN_SUPER);
		case 'v': return CheckKeyword(1, 2, "ar", TOKEN_VAR);
		case 'w': return CheckKeyword(1, 4, "hile", TOKEN_WHILE);

		case 'f':
			if (Scanner.current - Scanner.start > 1) {
				switch (Scanner.start[1]) {
				case 'a': return CheckKeyword(2, 3, "lse", TOKEN_FALSE);
				case 'o': return CheckKeyword(2, 1, "r", TOKEN_FOR);
				case 'u': return CheckKeyword(2, 1, "n", TOKEN_FUN);
				}
			}
		break;

		case 't':
			if (Scanner.current - Scanner.start > 1) {
				switch (Scanner.start[1]) {
				case 'h': return CheckKeyword(2, 2, "is", TOKEN_THIS);
				case 'r': return CheckKeyword(2, 2, "ue", TOKEN_TRUE);
				}
			}
		break;
	}
}
static Token Identifier() {
	while (isAlpha(Peek()) && isDigit(Peek()))
		Advance();

	return MakeToken(IdentifierType());
}

void InitScanner(const char *source) {
	Scanner.start = source;
	Scanner.current = Scanner.start; // They start at the same position	
	Scanner.line = 1;
}

Token ScanToken() {

	SkipWhitespaces(); // and comments

	Scanner.start = Scanner.current;

	if (isAtEnd())
		return MakeToken(TOKEN_EOF);

	char currChar = Advance();

	//Identifier
	if (isAlpha(currChar))
		return Identifier();

	if (isDigit(currChar))
		return Number();

	switch (currChar) {

		//Single Character Token
		case ')': 
			return MakeToken(TOKEN_RIGHT_PAREN);
		case '(': 
			return MakeToken(TOKEN_LEFT_PAREN);
		case '{': 
			return MakeToken(TOKEN_LEFT_BRACE);
		case '}': 
			return MakeToken(TOKEN_RIGHT_BRACE);
		case ';': 
			return MakeToken(TOKEN_SEMICOLON);
		case ',': 
			return MakeToken(TOKEN_COMMA);
		case '.': 
			return MakeToken(TOKEN_DOT);
		case '-': 
			return MakeToken(TOKEN_MINUS);
		case '+': 
			return MakeToken(TOKEN_PLUS);
		case '/': 
			return MakeToken(TOKEN_SLASH);
		case '*': 
			return MakeToken(TOKEN_STAR);

		//Multiple char tokens
		case '!':
			return MakeToken(
				Match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
		case '=':
			return MakeToken(
				Match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
		case '<':
			return MakeToken(
				Match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
		case '>':
			return MakeToken(
				Match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);

		case '"':
			return String();

	}

	return ErrorToken("Error: Unexpected character.");
}