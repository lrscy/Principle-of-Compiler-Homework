#include "parse.h"

int table[MAXN][MAXN];  // 算符优先矩阵
string ntable[MAXN];    // 关键字及识别码对照表
map<string, int> mpVt;  // 终结符离散化 i=1; +=2; -=3 *=4; /=5; (=6; )=7; #=8;

/*
 * 功能：
 *  初始化算符优先矩阵，关键字及识别码对照表，离散化终结符
 * 传入参数：（无）
 * 传出参数：（无）
 * 返回值：（无）
 */
void init() {
	FILE *finp = fopen( "ntable.txt", "r" );
    char line[MAXLEN], str[MAXLEN];
    int tn;
    while( NULL != fgets( line, MAXLEN, finp ) ) {
        sscanf( line, "%s%d", str, &tn );
        ntable[tn] = str;
    }
    fclose( finp );
    finp = fopen( "table.txt", "r" );
    fscanf( finp, "%d", &tn );
    for( int i = 1; i <= tn; ++i ) {
        fscanf( finp, "%s", str );
        mpVt[str] = i;
    }
    for( int i = 1; i <= tn; ++i ) {
        for( int j = 1; j <= tn; ++j )
            fscanf( finp, "%d", &table[i][j] );
    }
    fclose( finp );
    return ;
}

/*
 * 功能：
 *  进行该句的语法分析
 * 传入参数：
 *  vec:该行二元式序列
 * 传出参数：
 *  ncol:出错标识符为第ncol个标识符
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool sentenceAnalysis( vector<PIS> &vec, int &ncol ) {
    string st[MAXN];
    int top = 0, pos = 0;
    bool flag = true;
    st[top++] = "#";
    for( int i = 0; i < vec.size(); ++i ) {
        string tstr;
        int ta, tb, tc;
        // 识别第i个标识符
        if( vec[i].first < 40 ) tstr = ntable[vec[i].first];
        else tstr = vec[i].second;
        // 获取该终结符的离散化值
        tb = mpVt[tstr];
        do {
            // 获取最靠近栈顶的终结符的离散化值
            pos = top - 1;
            ta = mpVt[st[pos]];
            if( ta == 0 ) ta = mpVt[st[--pos]];
            // 算符优先矩阵中该点位空则报错
            if( table[ta][tb] == 0 ) { flag = false; break; }
            // 如果是栈顶终结符<=输入终结符
            if( table[ta][tb] == 1 || table[ta][tb] == 2 ) break;
            // 寻找最左素短语
            do {
                tc = ta;
                ta = mpVt[st[--pos]];
                if( ta == 0 ) ta = mpVt[st[--pos]];
            } while( table[ta][tc] == 2 );
            if( table[ta][tc] == 3 ) { flag = false; break; }
            // 将最左素短语替换为任意非终结符
            ++pos; st[pos] = "N";
            top = pos + 1;
        } while( top > 2 );
        // 最终将输入终结符入栈
        st[top++] = tstr;
        if( !flag ) { ncol = i + 1; break; }
    }
    return flag;
}
