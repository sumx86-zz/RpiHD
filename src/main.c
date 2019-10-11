#include "rpi.h"

void rpi_usage( char *prog )
{
    fprintf( stderr, "\nUsage: %s [OPTION] [ARGUMENT]\n", prog );
    fprintf( stderr, "-d [DEVICE]\n" );
    fprintf( stderr, "-s [SERVER]\n" );
    fprintf( stderr, "-p [PORT]\n" );
    fprintf( stderr, "-t [ARP REQUEST TIME DELAY]\n" );
    exit( RPI_BAD );
}

int main( int argc, char **argv )
{
    libnet_t *ltag;
    int opt;
    struct libnet_ether_addr *hw;
    struct rpi_conf c, *conf = &c;

    conf->device = NULL;
    conf->server = NULL;
    conf->port   = NULL;
    conf->delay  = NULL;

    while ( (opt = getopt( argc, argv, "d:s:p:t:" )) != -1 )
    {
        switch ( opt ) {
            case 'd':
                conf->device = optarg; break;
            case 's':
                conf->server = optarg; break;
            case 'p':
                conf->port   = optarg; break;
            case 't':
                conf->delay  = optarg; break;
            default:
                rpi_usage( argv[0] );
        }
    }

    if ( !conf->device || !conf->server || !conf->port || !conf->delay ){
        rpi_usage( argv[0] );
    }

    if ( (int) atof( conf->delay ) != 0 ){
        fprintf( stderr, "Delay must be in the range [0.0 - 0.9]\n" );
        exit( RPI_BAD );
    }

    if ( (ltag = rpi_initialize( conf, err_buff )) == NULL ){
        // this is the only place where _rlog() is not used since the initialization includes
        // creation of log file ( init_log() ), so in case where init_log() fails, error buffer
        // should be piped to `stderr` instead
        fprintf( stderr, "%s\n", err_buff );
        exit( RPI_BAD );
    }

    normalize_ip(
        getaddr( RPI_IPV4, conf->device, err_buff ),
        conf->ip
    );
    normalize_ip(
        getaddr( RPI_MASK, conf->device, err_buff ),
        conf->msk
    );

    // device hardware address
    if ((hw = libnet_get_hwaddr( ltag )) == NULL){
        strcpy( err_buff, libnet_geterror(ltag) );
    }

    if ( strlen( err_buff ) > 0 ) {
        _rlog( RPI_LOG_ERR, err_buff );
    }
    
    memcpy( conf->hw, hw, 6 );
    _rlog( RPI_LOG_INFO, "RPI initialized successfully!\n" );
    rpi_start_receiver( conf );
    rpi_arp_initiate( ltag, conf );
    return 0;
}