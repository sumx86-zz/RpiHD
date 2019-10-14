#ifndef FILE_H
#define FILE_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t _f_clines( FILE *fp );
size_t _f_glines( FILE *fp, char **lines );

#endif