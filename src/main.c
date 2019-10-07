#include "rpi.h"

void rpi_usage( char *prog )
{
    fprintf( stderr, "\nUsage: %s [OPTION] [ARGUMENT]\n", prog );
    fprintf( stderr, "-d [DEVICE]\n" );
    fprintf( stderr, "-s [SERVER]\n" );
    fprintf( stderr, "-p [PORT]\n" );
    exit( RPI_BAD );
}

int main( int argc, char **argv )
{
    libnet_t *ltag;
    int opt;
    struct rpi_conf c, *conf = &c;

    while ( (opt = getopt( argc, argv, "d:s:p:" )) != -1 )
    {
        switch ( opt ) {
            case 'd':
                conf->device = optarg; break;
            case 's':
                conf->server = optarg; break;
            case 'p':
                conf->port   = optarg; break;
            default:
                rpi_usage( argv[0] );
        }
    }

    if ( !conf->device || !conf->server || !conf->port ){
        rpi_usage( argv[0] );
    }

    if ( (ltag = rpi_initialize( conf, err_buff )) == NULL ){
        _rlog( RPI_LOG_ERR, err_buff );
    }

    _rlog( RPI_LOG_INFO, "RPI initialized successfully!\n" );
    rpi_arp_initiate( ltag, conf );
    return 0;
}