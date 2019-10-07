#include "log.h"

void init_log( void )
{
    log_fp   = fopen( RPI_LOG_FILE, "a+" );
    log_stat = ( !log_fp ) ? errno : 0 ;
}

void _rlog( rpi_log_t level, char *err )
{
    if ( level == RPI_LOG_ERR ) {

    }
}