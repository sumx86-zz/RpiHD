#ifndef __RPI_RCV_H
#define __RPI_RCV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pcap.h>
#include <time.h>
#include <net/if.h>
#include <netinet/ether.h>
#include "conf.h"
#include "net.h"

struct rpi_eth_hdr
{
    uint8_t hw_dst[ETH_ALEN];
    uint8_t hw_src[ETH_ALEN];
    uint16_t ether_type;
};

struct rpi_arp_hdr
{
    uint16_t hwtype;
    uint16_t ptype;
    uint8_t  hwlen;
    uint8_t  ptlen;
    uint16_t opcode;
    uint8_t  src_hw[6];
    uint8_t  src_ip[4];
    uint8_t  dst_hw[6];
    uint8_t  dst_ip[4];
};

int    init_sock( char *errbuf );
int    notify_server( int *sock, char *buff );
void * rpi_arp_sniffer( void *conf );
void   packet_handler( u_char *args, const struct pcap_pkthdr *header, const u_char *packet );

// external functions here
extern void init_log( void );
extern void mssleep( float ms );
extern void _rlog( rpi_log_t level, char *err );

extern char * cnvrt_ip( uint8_t *ip );
extern char * cnvrt_hw( uint8_t *hw );

#endif