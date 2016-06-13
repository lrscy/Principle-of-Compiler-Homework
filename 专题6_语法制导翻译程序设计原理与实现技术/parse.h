#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef pair<int, string> PIS;
typedef pair<string, int> PSI;
const int MAXN = 100 + 10;
const int MAXLEN = 255;

struct Node {
    string op, arg1, arg2, res;
    Node() {}
    Node( string _op, string _arg1, string _arg2, string _res ):
            op( _op ), arg1( _arg1 ), arg2( _arg2 ), res( _res ) {}
};

void init();
bool sentenceAnalysis( vector<PIS> vec, int &ecol, vector<Node> &vecGen );
//bool sentenceAnalysis( vector<PIS> vec, int &ecol );
