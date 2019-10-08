#ifndef __RPI_RCV_H
#define __RPI_RCV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pcap.h>
#include <time.h>
#include <netinet/ether.h>
#include "conf.h"
#include "net.h"

int    notify_server( int *sock, char *buff );
void * rpi_arp_sniffer( void *conf );

// external functions here
extern void init_log( void );
extern void mssleep( float ms );
extern void _rlog( rpi_log_t level, char *err );

#endif