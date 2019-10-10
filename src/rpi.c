#include "rpi.h"

libnet_t * rpi_initialize( struct rpi_conf *conf,
                                  char *errbuf )
{   
    libnet_t *ltag;

    if (!(ltag = libnet_init( LIBNET_LINK, conf->device, errbuf ))){
        return NULL;
    }

    init_log();
    if ( log_stat != 0 ) {
        strcpy( errbuf, strerror( log_stat ) );
        return NULL;
    }
    return ltag;
}

/* start the arp receiving thread */
void rpi_start_receiver( struct rpi_conf *conf )
{
    pthread_t thread;
    int err;

    err = pthread_create( &thread, NULL, rpi_arp_sniffer, (void *) conf );
    if ( err ) {
        _rlog( RPI_LOG_ERR, "Can't start arp sniffer!\n" );
    }
    _rlog( RPI_LOG_INFO, "ARP receiver started successfully!\n" );
}


void rpi_arp_initiate( libnet_t *lctx, struct rpi_conf *conf )
{
    uint32_t _net_off;

    packet_count  = 0;
    _net_off      = net_off( conf->ip, conf->msk );
    conf->_nhosts = nhosts( conf->msk );
    _net_off++;

    for ( uint16_t i = 0 ; i < conf->_nhosts ; i++ ) {
        send_packet( lctx, conf, _net_off++ );
        mssleep( 0.3 );
    }
    destroy_session( lctx );
    exit( RPI_OK );
}


int rpi_packet( libnet_t *lctx, struct rpi_conf *conf,
                       char *errbuf )
{
    libnet_ptag_t eth, arp;
    uint8_t hw_bcast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    uint8_t hw_unkn[6]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
    eth = arp = 0;
    arp = libnet_build_arp(
        ARPHRD_ETHER,
        ETHERTYPE_IP,
        ETH_ALEN,
        4,
        ARPOP_REQUEST,
        conf->hw,
        conf->ip,
        hw_unkn,
        conf->dst_ip,
        NULL,
        0,
        lctx,
        arp
    );

    if ( arp < 0 ) {
        strcpy( errbuf, "rpi_packet() - Arp packet error!\n" );
        return RPI_BAD;
    }

    eth = libnet_build_ethernet(
        hw_bcast,
        conf->hw,
        ETHERTYPE_ARP,
        NULL,
        0,
        lctx,
        eth
    );

    if ( eth < 0 ) {
        strcpy( errbuf, "rpi_packet() - Ethernet frame error!\n" );
        return RPI_BAD;
    }
    return 0;
}

/* build and inject the packet */
void send_packet( libnet_t *lctx, struct rpi_conf *conf,
                  uint32_t _net_off )
{
    int arp_stat;
    conf->dst_ip = long2ip( _net_off );

    // skipping gratuitous arp
    if ( conf->dst_ip[0] == conf->ip[0]
      && conf->dst_ip[1] == conf->ip[1]
      && conf->dst_ip[2] == conf->ip[2]
      && conf->dst_ip[3] == conf->ip[3]
    ) {
        return;
    }

    arp_stat = rpi_packet( lctx, conf, err_buff );

    if ( arp_stat == RPI_BAD ) {
        _rlog( RPI_LOG_ERR, err_buff );
    }

    if ( libnet_write( lctx ) == -1 ) {
        _rlog( RPI_LOG_ERR, "libnet_write() - Error writing packet!\n" );
    }
    packet_count++;
    libnet_clear_packet( lctx );
}

void destroy_session( libnet_t *lctx )
{
    libnet_clear_packet( lctx );
    libnet_destroy( lctx );
    _rlog( RPI_LOG_INFO, "Session closed!\n" );
}