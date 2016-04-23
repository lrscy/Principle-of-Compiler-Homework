#include "lexer.h"

string errmsg;
vector<PIS> vTable;


void getOutputName( char *inputName, char *outputName ) {
    int len = strlen( inputName );
    strcpy( outputName, inputName );
    while( outputName[len - 1] != '.' ) --len;
    if( len == 0 ) outputName[len] = 'a';
    outputName[len] = 0;
    strcat( outputName, ".lexer" );
    return ;
}

void errMsg( string filename, int rowNo, int colNo ) {
    printf( "%s:%d:%d error: %s\n", filename.c_str(), rowNo, colNo, errmsg.c_str() );
    return ;
}

void spaceProcess( char *line ) {
    int len = strlen( line ), pos = 0;
    for( int i = 0; i < len; ++i ) {
        if( line[i] != ' ' ) line[pos++] = line[i];
    }
    line[pos] = 0;
    return ;
}

bool noteProcess( string &str, bool &noteflag ) {
    while( true ) {
        int p1 = str.find( "//" );
        int p2 = str.find( "/*" );
        int p3 = str.find( "*/" );
        if( p1 == -1 && p2 == -1 && p3 == -1 ) break;
        int minp = str.length();
        if( ~p1 ) minp = min( minp, p1 );
        if( ~p2 ) minp = min( minp, p2 );
        if( ~p3 ) minp = min( minp, p3 );
        if( noteflag ) {
            if( p3 == -1 ) { str = ""; break; }
            else {
                noteflag = false;
                str = str.substr( p3 + 2, str.length() - p3 - 2 );
            }
        } else {
            if( minp == p3 ) {
                errmsg = "*/ cannot be matched.";
                noteflag = false;
                return false;
            } else if( minp == p2 ) {
                if( p3 == -1 ) { str = str.substr( 0, p2 ); noteflag = true; }
                else str = str.substr( 0, p2 ) + str.substr( p3 + 2, str.length() - p3 - 2 );
            } else if( minp == p1 ) {
                str = str.substr( 0, p1 );
            }
        }
    }
    return true;
}

void print() {
    for( int i = 0; i < vTable.size(); ++i ) {
        printf( "( %d, %s )\n", vTable[i].first, vTable[i].second.c_str() );
    }
    return ;
}

int main( int argc, char **argv ) {
    char line[LINEMAXLEN], outputName[LINEMAXLEN];
    int rowNo, colNo;
    bool flag = true, noteflag = false;
    FILE *fp = fopen( argv[1], "r" );
    getOutputName( argv[1], outputName );
    rowNo = 0;
    while( NULL != fgets( line, MAXLEN, fp ) ) {
        int len = strlen( line );
        if( line[len - 1] == '\n' ) line[len - 1] = 0;
        spaceProcess( line );
        colNo = 0;
        string str = line;
        str = str.substr( 0, LINEMAXLEN );
        if( !noteProcess( str, noteflag ) ||
                ( str.length() > 0 && !lineAnalyse( str, colNo ) ) ) {
            errMsg( argv[1], rowNo + 1, colNo + 1 );
        }
        ++rowNo;
    }
    if( noteflag ) {
        colNo = 0;
        flag = false;
        errmsg = "/* cannot be mateched.";
        errMsg( argv[1], rowNo + 1, colNo + 1 );
    }
    if( flag ) { puts( "Program OK." ); print(); }
    else puts( "Syntax Error." );
    return 0;
}
