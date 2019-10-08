#include "net.h"

uint32_t ip2long( uint8_t *n_ip )
{
    uint32_t long_ip = 0;

    long_ip += (uint32_t) (n_ip[0] << 24);
    long_ip += (uint32_t) (n_ip[1] << 16);
    long_ip += (uint32_t) (n_ip[2] << 8);
    long_ip += (uint32_t) (n_ip[3] << 0);
    
    return long_ip;
}

uint8_t * long2ip( uint32_t long_ip )
{
    static uint8_t ip[4];

    ip[0] = (long_ip >> 24) & 0xFF;
    ip[1] = (long_ip >> 16) & 0xFF;
    ip[2] = (long_ip >> 8)  & 0xFF;
    ip[3] = (long_ip >> 0)  & 0xFF;

    return ip;
}

/* calculate the `hosts part` range of the network */
uint16_t nhosts( uint8_t *nmask )
{
    uint16_t nhosts;
    uint32_t l_mask;
    
    nhosts = 0;
    l_mask = ip2long( nmask );
    nhosts = l_mask ^ 0xFFFFFFFF;
    
    return nhosts;
}

/* calculate the network start offset */
uint32_t net_off( uint8_t *ip, uint8_t *nmask )
{
    uint32_t off, l_ip, l_mask;
    
    l_ip   = ip2long( ip );
    l_mask = ip2long( nmask );
    off    = l_ip & l_mask;

    return off;
}

/* get the ip address or netmask of the device */
uint8_t * getaddr( rpi_adr_type_t type, char *device, char *errbuf )
{
    int sock;
    unsigned long req;
    struct ifreq iface;
    struct sockaddr_in *ip;

    if ( type == RPI_MASK ) req = SIOCGIFNETMASK;
    if ( type == RPI_IPV4 ) req = SIOCGIFADDR;

    if ( (sock = socket( AF_INET, SOCK_STREAM, 0 )) < 0 ){
        sprintf( errbuf, "%s\n", strerror( errno ) );
        return NULL;
    }
    
    strcpy( iface.ifr_name, device );
    if ( ioctl( sock, req, &iface ) < 0 ){
        sprintf( errbuf, "%s\n", strerror( errno ) );
        return NULL;
    }

    close( sock );
    ip = (struct sockaddr_in *) &iface.ifr_addr;
    return (uint8_t *) inet_ntoa( ip->sin_addr );
}

/* convert a dotted ip string to 4 byte array */
int normalize_ip( uint8_t *ip, uint8_t *dst )
{   
    register int i, j;
    char frag[4];
    uint8_t _ip[4];
    
    i = 0;
    j = 0;

    while ( *ip != '\0' )
    {
        if ( *ip == '.' ){
            frag[i] = '\0', _ip[j++] = atoi( frag ), i = 0, ip++;
        }
        frag[i++] = *ip++;
    }
    
    frag[i] = '\0';
    _ip[j]  = atoi( frag );
    memcpy( dst, _ip, 4 );

    return RPI_BAD;
}