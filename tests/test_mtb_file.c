#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "mtb_file.h"

int test_file_all_lines() {
	FILE *fp = fopen("tests/test_file.txt", "r+");
	int n_lines;

	char **lines = mtb_file_readall(fp, &n_lines);

	assert(fp && "File pointer is NULL");
	assert(n_lines == 5 && "Number of lines is not 5");
	assert(!strcmp(lines[0], "this") && "First line is not 'this'");
	assert(!strcmp(lines[1], "is") && "First line is not 'is'");
	assert(!strcmp(lines[2], "a") && "First line is not 'a'");
	assert(!strcmp(lines[3], "test") && "First line is not 'test'");
	assert(!strcmp(lines[4], "file") && "First line is not 'file'");

	fclose(fp);
	for(int i = 0; i < n_lines; i++) {
		free(lines[i]);
	}
	free(lines);

	printf("File all lines... OK\n");
	return 0;
}

int test_file_single_line() {
	FILE *fp = fopen("tests/test_file.txt", "r+");

	char *line = mtb_file_readline(fp);

	assert(fp && "File pointer is NULL");
	assert(!strcmp(line, "this") && "Line read is not 'this'");

	fclose(fp);
	free(line);

	printf("File single line... OK\n");
	return 0;
}

int test_mtb_file() {
	test_file_all_lines();
	test_file_single_line();

	return 0;
}
