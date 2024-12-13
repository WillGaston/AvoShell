#define BUFF_SIZE 2056

#include <stdio.h>
#include <stdlib.h>

void loop ();
char *gatherInput();
char **parse (char *ogLine);
void execute ();

//main
int main (int argc, char *argv) {

	loop();

	return 1;

};

// primary shell loop
void loop () {

	char *userInput;
	char **executeArgs;
	int executeStatus = 1;

	while (1) {

		printf("AvoShell> ");

		userInput = gatherInput();
		executeArgs = parse(userInput);


		if (!executeStatus) {
			break;
		}
	}

	free(userInput);

	int pos = 0;
	while (executeArgs[pos++] != NULL) {
		free(executeArgs[pos]);
	}

	free(executeArgs);

};

char *gatherInput() {

	int bufferSize = BUFF_SIZE;
	int currPos = 0;
	char chr;

	char *buffer = malloc(bufferSize);

	if (buffer == NULL) {
		printf("Memory Allocation Failure\n");
		exit(EXIT_FAILURE);
	}

	while (1) {

		chr = getchar();
		if (chr == '\n' || chr == EOF) break;
		
		if (currPos >= bufferSize) {
			buffer = (char *)realloc(buffer, BUFF_SIZE);
			bufferSize += BUFF_SIZE;
			if (buffer == NULL) {
				printf("Memory Re-Allocation Failure\n");
				exit(EXIT_FAILURE);
			}
		}
		
		buffer[currPos] = chr;
		currPos++;
	};

	buffer[currPos] = '\0';

	buffer = (char *)realloc(buffer, currPos + 1);

	return buffer;

}


// parse user input into array of pointers
char **parse (char *ogLine) {

	int argsBufferSize = BUFF_SIZE;
	char *chrPtr;
	char chr;
	int currPosBuffer = 0;
	int currPosArgs = 0;
	int currPosElement;
	int bufferLen = sizeof(ogLine);

	char **args = malloc(argsBufferSize);

	if (args == NULL) {
		printf("Memory Allocation Failure\n");
		exit(EXIT_FAILURE);
	}

	while (1) {

		if (currPosArgs >= argsBufferSize) {
			args = (char **)realloc(args, BUFF_SIZE);
			argsBufferSize += BUFF_SIZE;
			if (args == NULL) {
				printf("Memory Re-Allocation Failure\n");
				exit(EXIT_FAILURE);
			}
		}
		
		int chrPtrBufferSize = BUFF_SIZE;
		chrPtr = malloc(chrPtrBufferSize);

		if (chrPtr == NULL) {
			printf("Memory Allocation Failure\n");
			exit(EXIT_FAILURE);
		}

		currPosElement = 0;

		while (1) {

			//printf("entered parse loop\n");

			chr = ogLine[currPosBuffer];
			if (chr == ' ' || chr == EOF || chr == '\0') break;

			if (currPosElement >= chrPtrBufferSize) {
				chrPtr = (char *)realloc(chrPtr, BUFF_SIZE);
				chrPtrBufferSize += BUFF_SIZE;
				if (chrPtr == NULL) {
					printf("Memory Re-Allocation Failure\n");
					exit(EXIT_FAILURE);
				}
			}

			chrPtr[currPosElement] = chr;
			currPosElement++;
			currPosBuffer++;
		}



		currPosBuffer++;
		chrPtr[currPosElement] = '\0';
		args[currPosArgs] = chrPtr;
		currPosArgs++;

		if (chr == '\0') break;

	};

	args[currPosArgs] = NULL;

	return args;
};

// exexute parsed user input
void execute () {



};