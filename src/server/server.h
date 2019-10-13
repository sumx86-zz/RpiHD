#ifndef SERVER_H
#define SERVER_H 1

#include "../net.h"
#include <getopt.h>

extern void init_log( rpi_origin_t origin );
extern void mssleep( float ms );
extern void _rlog( rpi_log_t level, char *str );

#endif