#include "parse.h"

vector<PIS> vec;

void errMsg( string filename, int rowNo, int colNo, string errmsg ) {
    printf( "%s:%d:%d error: %s\n", filename.c_str(), rowNo, colNo, errmsg.c_str() );
    return ;
}

int main( int argc, char **argv ) {
    init();
    FILE *finp;
    char line[MAXLEN], str[MAXLEN];
    int type, nrow, ncol;
    bool flag = true;
    string errmsg;
    finp = fopen( argv[1], "r" );
    nrow = 0;
    while( NULL != fgets( line, MAXLEN, finp ) ) {
        vec.clear();
        do {
            if( line[0] == '#' ) break;
            sscanf( line, "(%d,%s)", &type, str );
            vec.push_back( make_pair( type, str ) );
        } while( NULL != fgets( line, MAXLEN, finp ) );
        ncol = 0;
        if( !Parse( vec, ncol, errmsg ) ) {
            flag = false;
            errMsg( argv[1], nrow, ncol, errmsg );
        }
        if( !flag ) puts( "Syntax Error!" );
        else puts( "Program OK!" );
    }
    fclose( finp );
    return 0;
}
