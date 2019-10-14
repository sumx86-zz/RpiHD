#ifndef FILE_H
#define FILE_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "conf.h"

int fclines( FILE *fp );
char ** fgetlines( FILE *fp, short *nlines );

extern void _rlog( rpi_log_t level, char *err );

#endif