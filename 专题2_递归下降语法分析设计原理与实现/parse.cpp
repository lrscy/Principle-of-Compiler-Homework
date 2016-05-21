#include "parse.h"

vector<string> vec;
string errmsg;
int errpos;

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
        if( vec[pos] != "*" && vec[pos] != "/" ) return true;
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
        if( vec[pos] != "+" && vec[pos] != "-" ) return true;
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
 *  str:该行字符串
 * 传出参数：
 *  emsg:出错信息
 *  epos:出错标识符首字符所在位置
 * 返回值：
 *  是否成功解析。是则返回true，否则返回false。
 */
bool Parse( string str, string &emsg, int &epos ) {
    int pos = str.length();
    while( str[--pos] == ' ' );
    str = str.substr( 0, pos + 1 );
    pos = 0;
    vec.clear();
    for( int i = 0; i < str.length(); ++i ) {
        if( str[i] == ' ' ) {
            vec.push_back( str.substr( pos, i - pos ) );
            while( str[i + 1] == ' ' && i + 1 < str.length() ) ++i;
            pos = i + 1;
        }
    }
    vec.push_back( str.substr( pos, str.length() - pos ) );
    vec.push_back( "#" );
    pos = 0;
    if( !ProcessorE( pos ) ) {
        emsg = errmsg;
        epos = str.find( vec[errpos] ) + 1;
        return false;
    }
    return true;
}
