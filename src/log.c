#include "log.h"

void init_log( void )
{
    log_fp   = fopen( RPI_LOG_FILE, "a+" );
    log_stat = ( !log_fp ) ? errno : 0 ;
}

void _rlog( rpi_log_t level, char *str )
{   
    int _exit = 0;
    char *msg;
    char linf[0xff] = "[RPI-INFO] - ";
    char lerr[0xff] = "[RPI-ERROR] - ";

    if ( level == RPI_LOG_ERR ) {
        msg   = strcat( lerr, str );
        _exit = 1;
    }

    if ( level == RPI_LOG_INFO ) {
        msg = strcat( linf, str );
    }
    
    fputs( msg, log_fp );
    fflush( log_fp );
    if ( _exit ) exit( RPI_BAD );
}