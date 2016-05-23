#ifndef LEXER
#define LEXER

#include "../include/head.h"

bool lexer( char *inputName );
bool lineAnalyse( string &line, int &colNo, string &errmsg, vector<PIS> &vTable );

#endif // LEXER
