#include "server.h"

void _usage( char *prog )
{
    fprintf( stderr, "\nUsage: %s -p [PORT]\n", prog );
    fprintf( stderr, "-h Display help\n" );
    exit( RPI_BAD );
}

void msg_recv_log( int *sock )
{
    char buff[1024];
    size_t nbytes;

    while ( (nbytes = recv( *sock, buff, 1024, 0 )) > 0 )
    {
        if ( strstr( buff, "[rpi-end]" ) != NULL ) {
            _rlog( RPI_LOG_INFO, "[SESSION END]\n\n" );
        } else {
            _rlog( RPI_LOG_INFO, buff );
        }
    }
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

    while ( (opt = getopt( argc, argv, "p:h" )) != -1 )
    {
        switch ( opt ) {
            case 'h':
                _usage( argv[0] );
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
    
    init_log( rpi_server );
    if ( log_stat != 0 ) {
        // again, here we pipe the error buffer to stderr if log initialization fails
        fprintf( stderr, "%s\n", strerror( log_stat ) );
        exit( RPI_BAD );
    }

    server = server_state_listen( atoi( port ), err_buff );
    if ( !server ) {
        _rlog( RPI_LOG_ERR, err_buff );
    }
    _rlog( RPI_LOG_INFO, "Server started successfully!\n" );

    while ( 1 )
    {
        rpi_sock = accept( 
            sockfd, (struct sockaddr *) &rpi, &rpi_len
        );
        if ( rpi_sock ) {
            _rlog( RPI_LOG_INFO, "Connected with raspberry pi successfully!\n" );
            msg_recv_log( &rpi_sock );
        }
    }
    return 0;
}