#include "main.h"

int main( int argc, char **argv ) {
    bool flag;
    flag = lexer( argv[1] );
    if( flag ) flag = parse();
    if( flag ) puts( "Program OK!" );
    else puts( "Syntax Error!" );
    return 0;
}
