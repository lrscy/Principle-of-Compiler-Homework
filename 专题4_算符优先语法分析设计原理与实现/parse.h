#ifndef PARSE
#define PARSE

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, string> PIS;
const int MAXN = 100;
const int MAXLEN = 255;

void init();
bool sentenceAnalysis( vector<PIS> &vec, int &ncol );

#endif // PARSE
