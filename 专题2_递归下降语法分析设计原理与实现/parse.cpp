#include "parse.h"

vector<string> vec;
string errmsg;
int errpos;

void Error( int &pos, string msg ) {
    errmsg = "expected " + msg;
    errpos = pos;
    return ;
}

bool ProcessorE( int &pos );

bool ProcessorF( int &pos ) {
    if( vec[pos] != "(" ) {
        if( vec[pos] != "i" ) { Error( pos, "i or (" ); return false; }
        ++pos;
        return true;
    }
    ++pos;
    if( !ProcessorE( pos ) ) { return false; }
    if( vec[pos] != ")" ) { Error( pos, ")" ); return false; }
    ++pos;
    return true;
}

bool ProcessorA( int &pos ) {
    if( vec[pos] != "+" && vec[pos] != "-" ) { Error( pos, "+ or -" ); return false; }
    ++pos;
    return true;
}

bool ProcessorM( int &pos ) {
    if( vec[pos] != "*" && vec[pos] != "/" ) { Error( pos, "* or /" ); return false; }
    ++pos;
    return true;
}

bool ProcessorTQ( int &pos ) {
    while( true ) {
        if( vec[pos] != "*" && vec[pos] != "/" ) return true;
        if( !ProcessorM( pos ) ) return false;
        if( !ProcessorF( pos ) ) return false;
    }
}

bool ProcessorT( int &pos ) {
    if( vec[pos] != "i" && vec[pos] != "(" ) { Error( pos, "i or (" ); return false; }
    if( !ProcessorF( pos ) ) return false;
    if( !ProcessorTQ( pos ) ) return false;
    return true;
}

bool ProcessorEQ( int &pos ) {
    while( true ) {
        if( vec[pos] != "+" && vec[pos] != "-" ) return true;
        if( !ProcessorA( pos ) ) return false;
        if( !ProcessorT( pos ) ) return false;
    }
}

bool ProcessorE( int &pos ) {
    if( vec[pos] != "i" && vec[pos] != "(" ) { Error( pos, "i or (" ); return false; }
    if( !ProcessorT( pos ) ) return false;
    if( !ProcessorEQ( pos ) ) return false;
    return true;
}

bool Parse( string str, string &emsg, int &epos ) {
    int pos = str.length();
    while( str[--pos] == ' ' );
    str = str.substr( 0, pos + 1 );
    pos = 0;
    vec.clear();
    for( int i = 0; i < str.length(); ++i ) {
        if( str[i] == ' ' ) {
            vec.push_back( str.substr( pos, i - pos ) );
            while( str[i + 1] == ' ' && i + 1 < str.length() ) ++i;
            pos = i + 1;
        }
    }
    vec.push_back( str.substr( pos, str.length() - pos ) );
    vec.push_back( "#" );
    pos = 0;
    if( !ProcessorE( pos ) ) {
        emsg = errmsg;
        epos = str.find( vec[errpos] ) + 1;
        return false;
    }
    return true;
}
