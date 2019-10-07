#include "rpi.h"

libnet_t * rpi_initialize( struct rpi_conf *conf,
                                  char *errbuf )
{   
    libnet_t *ltag;
    struct libnet_ether_addr *hw;

    if (!(ltag = libnet_init( LIBNET_LINK, conf->device, errbuf ))){
        return NULL;
    }

    init_log();
    if ( log_stat != 0 ) {
        strcpy( errbuf, strerror( log_stat ) );
        return NULL;
    }
    
    normalize_ip(
        getaddr( RPI_IPV4, conf->device, errbuf ),
        conf->ip
    );
    normalize_ip(
        getaddr( RPI_MASK, conf->device, errbuf ),
        conf->msk
    );

    // device hardware address
    if ((hw = libnet_get_hwaddr( ltag )) == NULL){
        strcpy( errbuf, libnet_geterror(ltag) );
        return NULL;
    }

    memcpy( conf->hw, hw, 6 );
    return ltag;
}

void rpi_arp_initiate( libnet_t *lctx, struct rpi_conf *conf )
{
    uint16_t _nhosts;
    uint32_t _net_off;

    _net_off = net_off( conf->ip, conf->msk );
    _nhosts  = nhosts( conf->msk );
    _net_off++;

    for ( uint16_t i = 0 ; i < _nhosts ; i++ ) {
        send_packet( lctx, conf, _net_off++ );
        sleep( 1 );
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
    libnet_clear_packet( lctx );
}

void destroy_session( libnet_t *lctx )
{
    libnet_clear_packet( lctx );
    libnet_destroy( lctx );
<<<<<<< HEAD
    _rlog( RPI_LOG_INFO, "Session closed!\n" );
}
=======
}
>>>>>>> c3cf5db31ae80bedcb0d169858c9c066d80b9677
