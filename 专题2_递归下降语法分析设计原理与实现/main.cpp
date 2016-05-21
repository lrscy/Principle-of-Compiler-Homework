#include "parse.h"

void errMsg( string filename, int nrow, int ncol, string errmsg ) {
    printf( "%s:%d:%d syntax error: %s\n", filename.c_str(), nrow, ncol, errmsg.c_str() );
    return ;
}

int main( int argc, char **argv ) {
    bool flag = true;
    char str[MAXLEN], inputName[MAXLEN], outputName[MAXLEN], line[MAXLEN];
    int nrow = 0, ncol;
    FILE *finp;
    string errmsg;
    finp = fopen( argv[1], "r" );
    while( NULL != fgets( line, MAXLEN, finp ) ) {
        ++nrow; ncol = 0;
        int len = strlen( line );
        line[len - 1] = 0;
        --len;
        if( !Parse( line, errmsg, ncol ) ) {
            errMsg( argv[1], nrow, ncol, errmsg );
            flag = false;
        }
    }
    if( !flag ) puts( "Syntax Error!" );
    else puts( "Success!" );
    fclose( finp );
    return 0;
}
