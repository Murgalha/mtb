#ifndef _MTB_FILE_H_
#define _MTB_FILE_H_

#include <stdio.h>

char *mtb_file_readline(FILE *);
char **mtb_file_readall(FILE *, int *);
char **mtb_filename_readall(char *, int *);

#endif
