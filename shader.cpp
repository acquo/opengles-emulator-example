#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

char* loadShader(const char* fileName)
{
	char *pResult = NULL;
	FILE *pFile = NULL;
	long iLen = 0;

	pFile = fopen(fileName, "r");

	if (pFile == NULL) {
		fprintf(stderr, "Error: Cannot read file '%s'\n", fileName);
		return NULL;
	}

	fseek(pFile, 0, SEEK_END); /* Seek end of file */
	iLen = ftell(pFile);
	fseek(pFile, 0, SEEK_SET); /* Seek start of file again */
	pResult = (char*)calloc(iLen + 1, sizeof(char));
	fread(pResult, sizeof(char), iLen, pFile);
	pResult[iLen] = '\0';
	fclose(pFile);

	return pResult;
}

void processShader(GLuint * pShader, const char * fileName, GLint shaderType)
{
	GLint iStatus;
	const char *aStrings[1] = { NULL };
	*pShader = glCreateShader(shaderType);
	aStrings[0] = loadShader(fileName);
	glShaderSource(*pShader, 1, aStrings, NULL);
	free((void *)aStrings[0]);
	aStrings[0] = NULL;
	glCompileShader(*pShader);
	glGetShaderiv(*pShader, GL_COMPILE_STATUS, &iStatus);
}
