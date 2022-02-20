#ifndef _MTB_STR_H_
#define _MTB_STR_H_

#include <stddef.h>

char *mtbs_new(char *);
char *mtbs_join(int, char *, ...);
void mtbs_concat(int, char **, ...);
char *mtbs_substr(char *, size_t, size_t);
char **mtbs_split(char *, char *, int *);
void mtbs_split_free(char **, int);

#endif
