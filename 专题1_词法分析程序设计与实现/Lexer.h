#ifndef LEXER
#define LEXER

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <map>
using namespace std;
const int MAXN = 255;

string keyword[9] = { "void", "int", "float", "double", "if", "else", "for", "do", "while" };
string errmsg;
map<string, string> mpTable;

bool lineAnalyse( string line, int &colNo );

#endif
