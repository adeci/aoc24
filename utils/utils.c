#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char* load_input(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("Error opening file");
		return NULL;
	}

	// Move to the end of the file to determine its size
	fseek(file, 0, SEEK_END);
	long filesize = ftell(file);
	rewind(file);

	if (filesize < 0) {
		perror("Error determining file size");
		fclose(file);
		return NULL;
	}

	// Allocate memory for the file content plus a null terminator
	char* buffer = malloc(filesize + 1);
	if (!buffer) {
		perror("Error allocating memory");
		fclose(file);
		return NULL;
	}

	// Read the file content into the buffer
	size_t read_size = fread(buffer, 1, filesize, file);
	if (read_size != filesize) {
		perror("Error reading file");
		free(buffer);
		fclose(file);
		return NULL;
	}

	buffer[filesize] = '\0'; // Null-terminate the string

	fclose(file);
	return buffer;
}

