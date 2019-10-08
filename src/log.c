#include "log.h"

void init_log( void )
{
    log_fp   = fopen( RPI_LOG_FILE, "a+" );
    log_stat = ( !log_fp ) ? errno : 0 ;
}

void _rlog( rpi_log_t level, char *str )
{   
    int _exit = 0;
    char timebuf[45], *logbuf;
    time_t rawtime;
    struct tm *timeinfo;

    time( &rawtime );
    timeinfo = localtime( &rawtime );
    strftime( timebuf, 45, "%m/%d/%Y - %H:%M:%S", timeinfo );

    if ( level == RPI_LOG_ERR ) {
        logbuf = "ERROR";
        _exit  = 1;
    }

    if ( level == RPI_LOG_INFO ) {
        logbuf = "INFO";
    }
    
    fprintf( log_fp, "[%s] [%s] - %s", logbuf, timebuf, str );
    fflush( log_fp );
    if ( _exit ) exit( RPI_BAD );
}

void mssleep( float ms )
{   
    int st;
    struct timespec start, stop;

    start.tv_sec  = 0;
    start.tv_nsec = ms * 1000000000L;

    st = nanosleep( &start, &stop );

    if ( st < 0 ){
        printf( "%s\n", strerror( errno ) );
        exit( 1 );
    }
}