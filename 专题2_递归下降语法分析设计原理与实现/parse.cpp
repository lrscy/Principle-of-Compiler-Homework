#include "parse.h"

vector<string> vec;
string errmsg;
int errpos;
string ntable[MAXN];

/*
 * 功能：
 *  初始化关键字及识别码对照表
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
    return ;
}

/*
 * 功能：
 *  存储错误信息
 * 传入参数：
 *  msg:错误信息
 * 传出参数：
 *  pos:出错标识符为该行第pos个标识符
 * 返回值：（无）
 */
void Error( int &pos, string msg ) {
    errmsg = "expected " + msg;
    errpos = pos;
    return ;
}

bool ProcessorE( int &pos );

/*
 * 功能：
 *  非终结符F的处理过程
 * 传入参数：
 *  pos:当前第pos个标识符
 * 传出参数：
 *  pos:当前第pos个标识符
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool ProcessorF( int &pos ) {
    if( vec[pos] != "(" ) {
        if( vec[pos] != "i" ) { Error( pos, "i or (" ); return false; }
        ++pos;
        return true;
    }
    ++pos;
    if( !ProcessorE( pos ) ) { return false; }
    if( vec[pos] != ")" ) { Error( pos, ")" ); return false; }
    ++pos;
    return true;
}

/*
 * 功能：
 *  非终结符A的处理过程
 * 传入参数：
 *  pos:当前第pos个标识符
 * 传出参数：
 *  pos:当前第pos个标识符
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool ProcessorA( int &pos ) {
    if( vec[pos] != "+" && vec[pos] != "-" ) { Error( pos, "+ or -" ); return false; }
    ++pos;
    return true;
}

/*
 * 功能：
 *  非终结符M的处理过程
 * 传入参数：
 *  pos:当前第pos个标识符
 * 传出参数：
 *  pos:当前第pos个标识符
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool ProcessorM( int &pos ) {
    if( vec[pos] != "*" && vec[pos] != "/" ) { Error( pos, "* or /" ); return false; }
    ++pos;
    return true;
}

/*
 * 功能：
 *  非终结符T'的处理过程
 * 传入参数：
 *  pos:当前第pos个标识符
 * 传出参数：
 *  pos:当前第pos个标识符
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool ProcessorTQ( int &pos ) {
    while( true ) {
        if( vec[pos] != "*" && vec[pos] != "/" ) {
            if( vec[pos] != "+" && vec[pos] != "-" && vec[pos] != "#" &&
                    vec[pos] != "*" && vec[pos] != "-" ) {
                Error( pos, "+ or - or * or /" );
                return false;
            }
            return true;
        }
        if( !ProcessorM( pos ) ) return false;
        if( !ProcessorF( pos ) ) return false;
    }
}

/*
 * 功能：
 *  非终结符T的处理过程
 * 传入参数：
 *  pos:当前第pos个标识符
 * 传出参数：
 *  pos:当前第pos个标识符
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool ProcessorT( int &pos ) {
    if( vec[pos] != "i" && vec[pos] != "(" ) { Error( pos, "i or (" ); return false; }
    if( !ProcessorF( pos ) ) return false;
    if( !ProcessorTQ( pos ) ) return false;
    return true;
}

/*
 * 功能：
 *  非终结符E'的处理过程
 * 传入参数：
 *  pos:当前第pos个标识符
 * 传出参数：
 *  pos:当前第pos个标识符
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool ProcessorEQ( int &pos ) {
    while( true ) {
        if( vec[pos] != "+" && vec[pos] != "-" ) {
            if( vec[pos] != ")" && vec[pos] != "#" ) { Error( pos, ")" ); return false; }
            return true;
        }
        if( !ProcessorA( pos ) ) return false;
        if( !ProcessorT( pos ) ) return false;
    }
}

/*
 * 功能：
 *  非终结符E的处理过程
 * 传入参数：
 *  pos:当前第pos个标识符
 * 传出参数：
 *  pos:当前第pos个标识符
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool ProcessorE( int &pos ) {
    if( vec[pos] != "i" && vec[pos] != "(" ) { Error( pos, "i or (" ); return false; }
    if( !ProcessorT( pos ) ) return false;
    if( !ProcessorEQ( pos ) ) return false;
    return true;
}

/*
 * 功能：
 *  进行该行的语法分析
 * 传入参数：
 *  vec:该行字符串的二元式序列
 * 传出参数：
 *  epos:出错标识符首字符所在位置
 *  emsg:出错信息
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool Parse( vector<PIS> &veco, int &epos, string &emsg ) {
    vec.clear();
    for( vector<PIS>::iterator it = veco.begin(); it != veco.end(); ++it ) {
        if( it->first < 40 ) vec.push_back( ntable[it->first] );
        else vec.push_back( it->second );
    }
    vec.push_back( "#" );
    int pos = 0;
    if( !ProcessorE( pos ) ) {
        emsg = errmsg;
        epos = errpos + 1;
        return false;
    }
    return true;
}
