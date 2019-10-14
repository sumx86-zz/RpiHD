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
    fseek( fp, 0, SEEK_SET ); // do this FOR FUCK'S SAKE!!
    return size;
}

char ** fgetlines( FILE *fp, short *nlines )
{
    int nl, i;
    char **lines;
    char line[0xFF];
    
    nl = fclines( fp );
    if ( nl <= 0 ) {
        return NULL;
    }

    lines = (char **) malloc( nl );
    if ( !lines ) {
        _rlog( RPI_LOG_ERR, "Cant allocate memory for trusted hosts list!\n" );
    }

    i = 0;
    while ( fgets( line, 0xFF, fp ) )
    {
        lines[i] = (char *) calloc( 25, sizeof( char ) );
        memcpy( lines[i++], line, strlen( line ) + 1 );
    }
    *nlines = nl;
    return lines;
}