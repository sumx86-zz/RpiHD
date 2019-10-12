#include "../net.h"
#include <getopt.h>

void _usage( char *prog )
{
    fprintf( stderr, "\nUsage: %s -p [PORT]\n", prog );
    exit( RPI_BAD );
}

int main( int argc, char **argv )
{
    char *port;
    int opt;
    int rpi_sock;
    struct sockaddr_in *server, rpi;
    socklen_t rpi_len;

    port    = NULL;
    rpi_len = sizeof( rpi );

    while ( (opt = getopt( argc, argv, "p:" )) != -1 )
    {
        switch ( opt ) {
            case 'p':
                port = optarg;
                break;
            default:
                _usage( argv[0] );
        }
    }
    
    if ( !port ){
        _usage( argv[0] );
    }
    
    server = server_state_listen( atoi( port ), err_buff );
    if ( !server ) {
        fprintf( stderr, "%s\n", err_buff );
        exit( RPI_BAD );
    }

    while ( 1 )
    {
        rpi_sock = accept( 
            sockfd, (struct sockaddr *) &rpi, &rpi_len
        );
        if ( rpi_sock ) {
            fprintf( stdout, "connected with rpi! FUCK YEAH!!!\n" );
        }
    }
    fprintf( stdout, "%d\n", ntohs( server->sin_port ) );
    return 0;
}