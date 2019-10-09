#ifndef __RPI_CONF_H
#define __RPI_CONF_H 1

#define RPI_LOG_FILE "/tmp/log.rpi"

FILE *log_fp;

int sockfd;

// the status of the log initialization
int log_stat;

// global error buffer
char err_buff[0xFF];

// rpi configuration structure
struct rpi_conf
{
    char *device;
    char *server;
    char *port;
    char *delay;
    uint8_t ip[4];
    uint8_t hw[6];
    uint8_t msk[4];
    uint8_t *dst_ip;
    uint16_t _nhosts;
};

// return stats
typedef enum
{
    RPI_OK  =  0,
    RPI_BAD = -1
} 
rpi_stat_t;

// rpi log levels
typedef enum
{
    RPI_LOG_ERR,
    RPI_LOG_INFO
}
rpi_log_t;

// address types
typedef enum
{
    RPI_IPV4,
    RPI_MASK
} 
rpi_adr_type_t;

#endif