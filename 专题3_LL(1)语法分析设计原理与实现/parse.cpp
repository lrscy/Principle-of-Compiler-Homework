#include "parse.h"

map<string, int> mpVn;              // 非终结符离散化   E=1; E'=2; T=3; T'=4; F=5; A=6; M=7;
map<string, int> mpVt;              // 终结符离散化     i=1; +=2; -=3 *=4; /=5; (=6; )=7; #=8; e=9; e->ε
vector<string> table[MAXN][MAXN];   // LL(1)分析表
string ntable[MAXN];                // 关键字及识别码对照表

/*
 * 功能：
 *  初始化LL(1)分析表，关键字及识别码对照表，离散化（非）终结符
 * 传入参数：（无）
 * 传出参数：（无）
 * 返回值：（无）
 */
void init() {
    mpVn["E"] = 1; mpVn["E'"] = 2; mpVn["T"] = 3; mpVn["T'"] = 4;
    mpVn["F"] = 5; mpVn["A"] = 6; mpVn["M"] = 7;
    mpVt["i"] = 1; mpVt["+"] = 2; mpVt["-"] = 3; mpVt["*"] = 4;
    mpVt["/"] = 5; mpVt["("] = 6; mpVt[")"] = 7; mpVt["#"] = 8; mpVt["e"] = 9;
    table[1][1].push_back( "T" ); table[1][1].push_back( "E'" );
    table[1][6].push_back( "T" ); table[1][6].push_back( "E'" );
    table[2][2].push_back( "A" ); table[2][2].push_back( "T" ); table[2][2].push_back( "E'" );
    table[2][3].push_back( "A" ); table[2][3].push_back( "T" ); table[2][3].push_back( "E'" );
    table[2][7].push_back( "e" );
    table[2][8].push_back( "e" );
    table[3][1].push_back( "F" ); table[3][1].push_back( "T'" );
    table[3][6].push_back( "F" ); table[3][6].push_back( "T'" );
    table[4][2].push_back( "e" );
    table[4][3].push_back( "e" );
    table[4][4].push_back( "M" ); table[4][4].push_back( "F" ); table[4][4].push_back( "T'" );
    table[4][5].push_back( "M" ); table[4][5].push_back( "F" ); table[4][5].push_back( "T'" );
    table[4][7].push_back( "e" );
    table[4][8].push_back( "e" );
    table[5][1].push_back( "i" );
    table[5][6].push_back( "(" ); table[5][6].push_back( "E" ); table[5][6].push_back( ")" );
    table[6][2].push_back( "+" );
    table[6][3].push_back( "-" );
    table[7][4].push_back( "*" );
    table[7][5].push_back( "/" );
    FILE *finp = fopen( "ntable.txt", "r" );
    char line[MAXLEN], str[MAXLEN];
    int tn;
    while( NULL != fgets( line, MAXLEN, finp ) ) {
        sscanf( line, "%s%d", str, &tn );
        ntable[tn] = str;
    }
    fclose( finp );
    return ;
}

/*
 * 功能：
 *  进行该行的语法分析
 * 传入参数：
 *  vec:该行二元式序列
 * 传出参数：
 *  emsg:出错信息
 *  epos:出错标识符首字符所在位置
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool Parse( const vector<PIS> &vec, int &ncol ) {
    string st[MAXLEN];
    int top = 0;
    st[top++] = "E";
    bool flag = true;
    for( int i = 0; i < vec.size(); ++i ) {
        int tn = vec[i].first;
        string ts = vec[i].second;
        if( tn < 40 ) ts = ntable[tn];
        int r, c = mpVt[ts];
        while( true ) {
            r = mpVn[st[top - 1]];
            // 栈顶为终结符
            if( r == 0 ) break;
            --top;
            vector<string> tstr = table[r][c];
            // 分析表中该点为空
            if( tstr.size() == 0 ) { flag = false; break; }
            // 逆向添加入栈
            for( vector<string>::reverse_iterator it = tstr.rbegin(); it != tstr.rend(); ++it ) {
                if( *it == "e" ) break;
                st[top++] = *it;
            }
        }
        --top;
        if( ( top == 0 && i != vec.size() - 1 ) ) flag = false;
        if( !flag ) { ncol = i; break; }
    }
    return flag;
}
