#include "main.h"

int main( int argc, char **argv ) {
    bool flag = lexer( argv[1] );
    if( flag ) parse();
    return 0;
}
