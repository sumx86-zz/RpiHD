#include "rpi_rcv.h"


void packet_handler( u_char *args, const struct pcap_pkthdr *header, 
                     const u_char *packet )
{
    short is_reply;
    char buff[0xFF];
    uint16_t ether_type;
    struct rpi_eth_hdr *eth_hdr = (struct rpi_eth_hdr *) packet;
    struct rpi_arp_hdr *arp_hdr = (struct rpi_arp_hdr *) (packet + 14);
    struct rpi_conf *conf       = (struct rpi_conf *) args;
    struct arp_reply r, *reply  = &r;

    is_reply   = 0;
    ether_type = ntohs( eth_hdr->ether_type );
    
    if ( ether_type == ETHERTYPE_ARP )
    {
        if ( ntohs( arp_hdr->opcode ) == ARPOP_REPLY )
        {
            // if the reply is destined to us
            if ( arp_hdr->dst_hw[0] == conf->hw[0]
              && arp_hdr->dst_hw[1] == conf->hw[1]
              && arp_hdr->dst_hw[2] == conf->hw[2]
              && arp_hdr->dst_hw[3] == conf->hw[3]
              && arp_hdr->dst_hw[4] == conf->hw[4]
              && arp_hdr->dst_hw[5] == conf->hw[5] )
            {
                is_reply = 1;
                memcpy( reply->src_hw, arp_hdr->src_hw, 6 );
                memcpy( reply->src_ip, arp_hdr->src_ip, 4 );
            }
        }

        if ( is_reply )
        {
            sprintf( buff, "Found host > %s -- %s\n", cnvrt_ip( reply->src_ip ), cnvrt_hw( reply->src_hw ) );
            notify_server( &sockfd, buff );
        }
        
        // notify the server when the last arp request has been sent
        // and terminate thread
        if ( packet_count == conf->_nhosts - 1 )
        {
            sprintf( buff, "[rpi-end]\n" );
            notify_server( &sockfd, buff ), close( sockfd ), pthread_exit( NULL );
        }
        is_reply = 0;
    }
}

void * rpi_arp_sniffer( void *conf )
{
    pcap_t *handle;
    int snaplen;
    int timeout;
    int promisc;
    struct rpi_conf *_conf = (struct rpi_conf *) conf;

    if ( (csockfd = init_connection( _conf, err_buff )) < 0 )
        _rlog( RPI_LOG_ERR, err_buff );

    _rlog( RPI_LOG_INFO, "Connected to server!\n" );
    snaplen =  64;
    timeout =   0;
    promisc =   0;

    handle = pcap_open_live(
        _conf->device,
        snaplen,
        promisc,
        timeout,
        err_buff
    );

    if ( !handle ) {
        _rlog( RPI_LOG_ERR, err_buff );
    }

    pcap_loop( handle, -1, packet_handler, (u_char *) _conf );
    pcap_close( handle );
    return NULL;
}


int notify_server( int *sock, char *buff )
{
    if ( *sock )
    {
        send( *sock, buff, strlen( buff ), 0 );
    }
    return 0;
}