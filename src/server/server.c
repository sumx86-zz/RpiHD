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
    struct sockaddr_in *server;

    port = NULL;

    while ( (opt = getopt( argc, argv, "p:" )) != -1 )
    {
        switch ( opt ) {
            case 'p': port = optarg; break;
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
    fprintf( stdout, "%d\n", ntohs( server->sin_port ) );
    return 0;
}