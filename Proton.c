#include "Common.h"	
#include "Chunk.h"
#include "Debug.h"
#include "VirtualMachine.h"

// Author: Aiman Hammou <developer.aiman@outlook.com>

// Static functions SECTION

static void REPL() {

	char line[1024];
	for (;;) {
		printf(">> ");

		if (!fgets(line, sizeof(line), stdin)) {
			printf("\n");
			break;
		}
		Interpret(line);
	}

	
}


static char *ReadFile(const char *filePath) {

	FILE *filePtr = fopen(filePath, "rb"); 
	if (filePtr == NULL) {
		fprintf(stderr, "Couldn't open the file: %s\n", filePath);
		exit(74);
	}

	//Get size of file content
	fseek(filePtr, 0L, SEEK_END );
	size_t fileSize = ftell(filePtr);
	rewind(filePtr);

	//Read content
	char *fileBuffer = (char *)malloc(sizeof(char) * fileSize + 1);  assert(fileBuffer != NULL);
	size_t numBytesRead = fread(fileBuffer, sizeof(char), fileSize, filePtr); assert(numBytesRead >= fileSize);
	fileBuffer[numBytesRead] = '\0';
	
	fclose(filePtr);
	return fileBuffer;
}

static void RunFile(const char *filePath) {

	char *FileContent = ReadFile(filePath);

	InterpretResult Result = Interpret(FileContent);

	free(FileContent);

	if (Result == INTERPRET_COMPILER_ERROR)
		exit(65);
	if (Result == INTERPRET_RUNTIME_ERROR)
		exit(70);


}
// End of Static functions SECTION

int main(int argc, char *argv[]){
	
	InitVM();

	if (argc == 1) {
		REPL();
	}
	else if (argc == 2) {
		RunFile(argv[1]);
	}
	else {
		fprintf(stderr, "Usage: proton [FILE PATH]\n");
		exit(64);
	}

	FreeVM();

	return 0;
}
