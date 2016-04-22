#include "Lexer.h"

bool isTerminalStage( int stage ) {
	if( stage == 0 || stage == 6 || stage == 7 ||
		stage == 13 || stage == 14 || stage == 16 ) return false;
	return true;
}

int characterType( char ch ) {
	if( ch == ' ' || ch == '\n' || ch == 0 ) return 0;
	switch( ch ) {
		case '+': return 1;
		case '-': return 2;
		case '*': return 3;
		case '/': return 4;
		case '%': return 5;
		case '>': return 6;
		case '<': return 7;
		case '=': return 8;
		case '!': return 9;
		case '&': return 10;
		case '|': return 11;
		case ',': return 12;
		case '(': return 13;
		case ')': return 14;
		case '{': return 15;
		case '}': return 16;
		case ';': return 17;
		default: break;
	}
	if( '0' <= ch && ch <= '9' ) return 18 + ch - '0';
	if( 'a' <= ch && ch <= 'z' ) return 28 + ch - 'a';
	if( 'A' <= ch && ch <= 'Z' ) return 54 + ch - 'A';
	return -1;
}

bool check( string str ) {
	return true;
}

bool stage_0( int &stage, int chtype ) {
	bool flag = true;
	return flag;
}

bool excute( int &stage, char ch, string &str ) {
	int chtype = characterType( ch );
	bool flag = true;
	switch( stage ) {
		case 0: flag = stage_0( stage, chtype ); str = ""; break;
		case 1: flag = stage_1( stage, chtype ); break;
		case 2: flag = stage_2( stage, chtype ); break;
		case 3: flag = stage_3( stage, chtype ); break;
		case 4: flag = stage_4( stage, chtype ); break;
		case 5: flag = stage_5( stage, chtype ); break;
		case 6: flag = stage_6( stage, chtype ); break;
		case 7: flag = stage_7( stage, chtype ); break;
		case 8: flag = stage_8( stage, chtype ); break;
		case 9: flag = stage_9( stage, chtype ); break;
		case 10: flag = stage_10( stage, chtype ); break;
		case 11: flag = stage_11( stage, chtype ); break;
		case 12: flag = stage_12( stage, chtype ); break;
		case 13: flag = stage_13( stage, chtype ); break;
		case 14: flag = stage_14( stage, chtype ); break;
		case 15: flag = stage_15( stage, chtype ); break;
		case 16: flag = stage_16( stage, chtype ); break;
		case 17: flag = stage_17( stage, chtype ); break;
		default: flag = false;
	}
	return flag;
}

bool lineAnalyse( string line, int &colNo ) {
	int stage = 0;
	bool flag = true;
	string str = "";
	while( line[colNo] ) {
		flag = excute( stage, line[colNo], str );
		if( !flag && !check( str ) ) return false;
		else str += line[colNo];
	}
	return true;
}
