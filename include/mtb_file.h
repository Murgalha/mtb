#ifndef _MTB_FILE_H_
#define _MTB_FILE_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

char *mtb_file_readline(FILE *);
char **mtb_file_readall(FILE *, int *);
char **mtb_filename_readall(char *, int *);

#ifdef __cplusplus
}
#endif

#endif
