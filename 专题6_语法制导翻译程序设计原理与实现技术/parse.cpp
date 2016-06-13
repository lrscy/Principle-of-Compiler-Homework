#include "parse.h"

map<string, int> mp;
PSI table[MAXN][MAXN];
string ntable[MAXN];
vector<string> grammar[MAXN];
string valVn[MAXN][MAXN];
int topVn[MAXN];

/*
 * 功能：
 *  初始化SLR(1)分析表，非终结符值栈（顶），关键字及识别码对照表，离散化（非）终结符
 * 传入参数：（无）
 * 传出参数：（无）
 * 返回值：（无）
 */
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
                default:    // 将GOTO函数解析成ACTION的S操作，便于后续处理
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
    memset( topVn, 0, sizeof( topVn ) );
    return ;
}

/*
 * 功能：
 *  生成新临时变量
 * 传入参数：（无）
 * 传出参数：（无）
 * 返回值：新临时变量名
 */
string newTemp() {
    static int No = 1;
    char str[MAXN];
    sprintf( str, "T%d", No++ );
    return str;
}

/*
 * 功能：
 *  根据规约式生成相应四元式
 * 传入参数：
 *  no: 规约项
 * 传出参数：
 *  vecGen: 四元式序列
 * 返回值：（无）
 */
void generate( int no, vector<Node> &vecGen ) {
    string tstr;
    switch( no ) {
        case 1: break;
        case 2:
            vecGen.push_back( Node( "=", valVn[2][topVn[2] - 1], "-", valVn[3][topVn[3] - 1] ) );
            break;
        case 3:
            tstr = newTemp();
            vecGen.push_back( Node( "+", valVn[3][topVn[3] - 1], valVn[4][topVn[4] - 1], tstr ) );
            --topVn[3]; --topVn[4]; valVn[3][topVn[3]++] = tstr;
            break;
        case 4:
            tstr = newTemp();
            vecGen.push_back( Node( "-", valVn[3][topVn[3] - 1], valVn[4][topVn[4] - 1], tstr ) );
            --topVn[3]; --topVn[4]; valVn[3][topVn[3]++] = tstr;
            break;
        case 5:
            valVn[3][topVn[3]++] = valVn[4][topVn[4] - 1];
            --topVn[4];
            break;
        case 6:
            tstr = newTemp();
            vecGen.push_back( Node( "*", valVn[4][topVn[4] - 1], valVn[5][topVn[5] - 1], tstr ) );
            --topVn[4]; --topVn[5]; valVn[4][topVn[4]++] = tstr;
            break;
        case 7:
            tstr = newTemp();
            vecGen.push_back( Node( "/", valVn[4][topVn[4] - 1], valVn[5][topVn[5] - 1], tstr ) );
            --topVn[4]; --topVn[5]; valVn[4][topVn[4]++] = tstr;
            break;
        case 8:
            valVn[4][topVn[4]++] = valVn[5][topVn[5] - 1];
            --topVn[5];
            break;
        case 9:
            valVn[5][topVn[5]++] = valVn[3][topVn[3] - 1];
            --topVn[3];
            break;
        case 10:
            valVn[5][topVn[5]++] = "i";
            break;
        case 11:
            valVn[2][topVn[2]++] = "i";
            break;
    }
    return ;
}

/*
 * 功能：
 *  对每行进行分析处理并生成四元式序列
 * 传入参数：
 *  vec: 输入二元式
 * 传出参数：
 *  ecol: 出错标识符位置
 *  vecGen: 四元式序列
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool sentenceAnalysis( vector<PIS> &vec, int &ecol, vector<Node> &vecGen ) {
    string sign[MAXN], str, tstr;
    int status[MAXN];
    int top = 0, tn, len, ncol;
    PSI tpsi;
    sign[top] = "#"; status[top] = 0; ++top;
    for( int i = 0; i < vec.size(); ++i ) {
        // 获取二元式中真实值
        tn = vec[i].first;
        if( tn < 40 ) str = ntable[tn];
        else str = vec[i].second;
        ncol = mp[str];
        if( ncol == 0 ) { ecol = i; return false; }
        tpsi = table[status[top - 1]][ncol];
        // 分析表中该位置为 空
        if( tpsi.first == "-" ) { ecol = i; return false; }
        // 分析表中该位置为 acc
        if( tpsi.first == "A" ) {
            if( i != vec.size() - 1 ) { ecol = i; return false; }
            break;
        }
        // 分析表中该位置为 S* 状态转移操作
        if( tpsi.first == "S" ) {
            sign[top] = str; status[top] = tpsi.second; ++top;
        }
        // 分析表中该位置为 R* 即规约操作
        if( tpsi.first == "R" ) {
            --i;
            tn = tpsi.second;
            // 生成四元式
            generate( tn, vecGen );
            // 规约操作
            tstr = grammar[tn][0];
            len = grammar[tn].size() - 1;
            top -= len;
            // 忽略扩展部分的规约操作
            if( tstr == "S" ) continue;
            if( top <= 0 ) { ecol = i; return false; }
            tpsi = table[status[top - 1]][mp[tstr]];
            if( tpsi.first != "S" && tpsi.first != "A" ) { ecol = i; return false; }
            // 将值入栈
            sign[top] = tstr; status[top] = tpsi.second; ++top;
        }
    }
    return true;
}
