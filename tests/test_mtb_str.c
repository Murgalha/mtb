#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "mtb_str.h"

int test_split_empty_string() {
	char *str = "";
	int n;

	char **tokens = mtbs_split(str, " ", &n);

	assert(n == 1 && "Number of tokens is not equal to 1");
	assert(!strcmp(tokens[0], "") && "First token is not empty string");

	printf("Split empty string... OK\n");
	mtbs_split_free(tokens, n);

	return 0;
}

int test_split_null_string() {
	char *str = NULL;
	int n;
	char *delims = " ";

	char **tokens = mtbs_split(str, delims, &n);

	assert(n == 0 && "Number of tokens is not equal to 0");
	assert(tokens == NULL && "Tokens is not NULL");

	mtbs_split_free(tokens, n);

	printf("Split null string... OK\n");
	return 0;
}

int test_split_null_delims() {
	char *str = NULL;
	int n;
	char *delims = " ";

	char **tokens = mtbs_split(str, delims, &n);

	assert(n == 0 && "Number of tokens is not equal to 0");
	assert(tokens == NULL && "Tokens is not NULL");

	mtbs_split_free(tokens, n);

	printf("Split null delims... OK\n");
	return 0;
}

int test_split_slash() {
	char *str = "/home/user/";
	int n;

	char **tokens = mtbs_split(str, "/", &n);

	assert(n == 2 && "Number of tokens is not equal to 2");
	assert(!strcmp(tokens[0], "home") && "First token is not 'home'");
	assert(!strcmp(tokens[1], "user") && "Second token is not 'user'");

	mtbs_split_free(tokens, n);

	printf("Split slash... OK\n");
	return 0;
}

int test_mtb_str() {
	test_split_empty_string();
	test_split_slash();
	test_split_null_string();
	test_split_null_delims();

	return 0;
}
