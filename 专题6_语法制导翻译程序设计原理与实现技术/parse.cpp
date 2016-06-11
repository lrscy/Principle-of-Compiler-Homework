#include "parse.h"

map<string, int> mp;
PSI table[MAXN][MAXN];
string ntable[MAXN];
vector<string> grammar[MAXN];

void init() {
    char str[MAXN], c;
    FILE *fp;
    int n;
    mp["i"] = 1; mp["="] = 2; mp["+"] = 3; mp["-"] = 4; mp["*"] = 5; mp["/"] = 6;
    mp["("] = 7; mp[")"] = 8; mp["#"] = 9; mp["S"] = 10; mp["A"] = 11; mp["V"] = 12;
    mp["E"] = 13; mp["T"] = 14; mp["F"] = 15;
    fp = fopen( "table.txt", "r" );
    for( int i = 0; i < 20; ++i ) {
        for( int j = 1; j <= 15; ++j ) {
            fscanf( fp, "%s", str );
            switch( str[0] ) {
                case 'S': 
                    sscanf( str, "%c%d", &c, &n );
                    table[i][j] = make_pair( "S", n );
                    break;
                case 'R': 
                    sscanf( str, "%c%d", &c, &n );
                    table[i][j] = make_pair( "R", n );
                    break;
                case 'a': 
                    table[i][j] = make_pair( "A", 0 );
                    break;
                case '-': 
                    table[i][j] = make_pair( "-", 0 );
                    break;
                default:
                    sscanf( str, "%d", &n );
                    table[i][j] = make_pair( "S", n );
            }
        }
    }
    fclose( fp );
    fp = fopen( "grammar.txt", "r" );
    for( int i = 1; i <= 11; ++i ) {
        fscanf( fp, "%d", &n );
        for( int j = 0; j < n; ++j ) {
            fscanf( fp, "%s", str );
            grammar[i].push_back( str );
        }
    }
    fclose( fp );
    fp = fopen( "ntable.txt", "r" );
    for( int i = 0; i < 40; ++i ) {
        fscanf( fp, "%s %d", str, &n );
        ntable[n] = str;
    }
    fclose( fp );
    return ;
}

//bool sentenceAnalysis( vector<PIS> vec, int &ecol, vector<Node> &gen ) {
bool sentenceAnalysis( vector<PIS> vec, int &ecol ) {
    string sign[MAXN], str, tstr;
    int status[MAXN];
    int top = 0, tn, len, ncol;
    PSI tpsi;
    sign[top] = "#"; status[top] = 0; ++top;
    for( int i = 0; i < vec.size(); ++i ) {
        tn = vec[i].first;
        if( tn < 40 ) str = ntable[tn];
        else str = vec[i].second;
        ncol = mp[str];
        if( ncol == 0 ) { ecol = i; return false; }
        tpsi = table[status[top - 1]][ncol];
        if( tpsi.first == "-" ) { ecol = i; return false; }
        if( tpsi.first == "A" ) {
            if( i != vec.size() - 1 ) { ecol = i; return false; }
            break;
        }
        if( tpsi.first == "S" ) {
            sign[top] = str; status[top] = tpsi.second; ++top;
        }
        if( tpsi.first == "R" ) {
            --i;
            tn = tpsi.second;
            ;
            tstr = grammar[tn][0];
            len = grammar[tn].size() - 1;
            top -= len;
            if( tstr == "S" ) continue;
            if( top <= 0 ) { ecol = i; return false; }
            tpsi = table[status[top - 1]][mp[tstr]];
            if( tpsi.first != "S" && tpsi.first != "A" ) { ecol = i; return false; }
            sign[top] = tstr; status[top] = tpsi.second; ++top;
        }
    }
    return true;
}
