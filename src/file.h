#ifndef FILE_H
#define FILE_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int  fclines( FILE *fp );
void fgetlines( FILE *fp, char **lines );

#endif