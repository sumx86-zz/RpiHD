#include "file.h"

int fclines( FILE *fp )
{
    register int c, size;
    c    = 0;
    size = 0;
    while ( (c = getc( fp )) != EOF ) {
        if ( c == '\n' )
            ++size;
    }
    return size;
}

int fgetlines( FILE *fp, char **lines )
{
    int nl, i;
    char line[0xFF];
    
    i  = 0;
    nl = fclines( fp );
    if ( nl <= 0 ) {
        return -1;
    }
    return nl;
}