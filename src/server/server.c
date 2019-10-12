#include "../net.h"

void _usage( char *prog )
{
    fprintf( stderr, "\nUsage: %s -p [PORT]\n", prog );
    exit( RPI_BAD );
}

int main( int argc, char **argv )
{
    if ( (sockfd = init_sock( err_buff )) < 0 ) {
        fprintf( stderr, "%s\n", err_buff );
        exit( RPI_BAD );
    }
    return 0;
}