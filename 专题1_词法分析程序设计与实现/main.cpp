#include "Lexer.h"

void getOutputName( char *inputName, char outputName ) {
	int len = strlen( inputName[1] );
	strcpy( outputName, intputName[1] );
	while( outputName[len] != '.' ) --len;
	if( len == 0 ) outputName[len] = 'a';
	outputName[len] = 0;
	strcat( outputName, ".lexer" );
	return ;
}

void errMsg( string filename, int rowNo, int colNo ) {
	printf( "%s:%d:%d error: %s\n", filename.c_str(), rowNo, colNo, errmsg.c_str() );
	return ;
}

int main( int argc, char **argv ) {
	char line[MAXN], outputName[MAXN];
	int rowNo, colNo;
	bool flag = true;
	FILE *fp = fopen( argv[1], "r" );
	getOutputName( argv[1], outputName );
	rowNo = 0;
	while( NULL != fgets( line, MAXN, fp ) ) {
		colNo = 0;
		if( !lineAnalyse( line, colNo ) ) {
			errMsg( argv[1], rowNo + 1, colNo + 1 );
		}
		++rowNo;
	}
	return 0;
}
