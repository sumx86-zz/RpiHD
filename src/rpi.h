#ifndef __RPI_H
#define __RPI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <getopt.h>
#include <libnet.h>
#include <netinet/ether.h>
#include "conf.h"
#include "net.h"

libnet_t * rpi_initialize( struct rpi_conf *conf, char *errbuf );
void       rpi_usage( char *prog );
void       destroy_session( libnet_t *lctx );
void       rpi_arp_initiate( libnet_t *lctx, struct rpi_conf *conf );
void       send_packet( libnet_t *lctx, struct rpi_conf *conf, uint32_t _net_off );
int        rpi_packet( libnet_t *lctx, struct rpi_conf *conf, char *errbuf );

extern void init_log( void );
extern void _rlog( rpi_log_t level, char *err );
// external logging functions here

#endif