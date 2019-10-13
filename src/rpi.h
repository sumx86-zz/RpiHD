#ifndef __RPI_H
#define __RPI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <getopt.h>
#include <libnet.h>
#include <time.h>
#include <netinet/ether.h>
#include <pthread.h>
#include "conf.h"
#include "net.h"

libnet_t * rpi_initialize( struct rpi_conf *conf, char *errbuf );
void       rpi_usage( char *prog );
void       destroy_session( libnet_t *lctx );
void       rpi_arp_initiate( libnet_t *lctx, struct rpi_conf *conf );
void       send_packet( libnet_t *lctx, struct rpi_conf *conf, uint32_t _net_off );
void       rpi_start_receiver( struct rpi_conf *conf );
int        rpi_packet( libnet_t *lctx, struct rpi_conf *conf, char *errbuf );

// external functions here
extern void init_log( rpi_origin_t origin );
extern void mssleep( float ms );
extern void _rlog( rpi_log_t level, char *err );
extern void * rpi_arp_sniffer( void *conf );

#endif