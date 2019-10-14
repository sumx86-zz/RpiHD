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

void fgetlines( FILE *fp, char **lines )
{
    
}