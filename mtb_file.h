#ifndef _MTB_FILE_H_
#define _MTB_FILE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>

char *mtb_file_readline(FILE *);
char **mtb_file_readall(FILE *, int *);
char **mtb_filename_readall(char *, int *);

#ifdef MTB_FILE_IMPLEMENTATION

char *mtb_file_readline(FILE *file) {
	if(!file) {
		return NULL;
	}
	int len = 0, capacity = 2;
	char *str = (char *) malloc(sizeof(char) * capacity);
	char c;

	do {
		if(capacity == len) {
			capacity <<= 1;
			str = (char *) realloc(str, sizeof(char) * capacity);
		}
		c = fgetc(file);
		str[len++] = c;
	} while(c != '\n' && c != EOF);

	len--;

	// Free empty lines to avoid leak
	if(len == 0) {
		free(str);
		str = NULL;
	}
	// realloc 'string' to avoid keeping unused bytes
	else {
		str[len] = '\0';
		str = (char *) realloc(str, sizeof(char) * (len + 1));
	}

	return str;
}


char **mtb_file_readall(FILE *file, int *n) {
	if(!file) {
		*n = -1;
		return NULL;
	}

	*n = 0;
	int capacity = 2;
	char *tmp;
	char **lines = (char **) malloc(sizeof(char *) * capacity);

	while(!feof(file)) {
		// avoid realloc every time
		if(capacity == *n) {
			capacity <<= 1;
			lines = (char **) realloc(lines, sizeof(char *) * capacity);
		}
		tmp = mtb_file_readline(file);
		// ignore NULL pointers
		if(tmp) {
			lines[(*n)++] = tmp;
		}
	}
	return lines;
}

char **mtb_filename_readall(char *filename, int *n) {
	FILE *fp = fopen(filename, "r+");
	*n = -1;

	if(!fp) {
		return NULL;
	}
	char **lines = mtb_file_readall(fp, n);
	fclose(fp);

	return lines;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
