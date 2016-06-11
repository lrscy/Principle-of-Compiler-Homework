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
};

void init();
//bool sentenceAnalysis( vector<PIS> vec, int &ecol, vector<Node> &gen );
bool sentenceAnalysis( vector<PIS> vec, int &ecol );
