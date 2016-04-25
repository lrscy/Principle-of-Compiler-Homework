#ifndef LEXER
#define LEXER

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
using namespace std;
typedef pair<int, string> PIS;
const int MAXLEN = 10000;
const int LINEMAXLEN = 255;
const int WORDMAXLEN = 15;
const int PRECISION = 15;

bool lineAnalyse( string &line, int &colNo, string &errmsg, vector<PIS> &vTable );

#endif // LEXER
