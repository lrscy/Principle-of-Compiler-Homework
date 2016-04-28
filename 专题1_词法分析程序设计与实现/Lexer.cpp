#include "lexer.h"

/*
 * 功能：
 *  判断当前阶段是否为终结阶段
 * 传入参数：
 *  line:包含该行的字符串
 * 传出参数：（无）
 * 返回值：
 *  该阶段是否成功解析。是则返回true，否则返回false。
 */
bool isTerminalStage( int stage ) {
    if( stage == 0 || stage == 4 || stage == 5 ||
        stage == 11 || stage == 12 || stage == 14 ) return false;
    return true;
}

/*
 * 功能： 
 *  判断当前字符的类型
 * 传入参数： 
 *  ch:待判断字符
 * 传出参数：（无）
 * 返回值：
 *  该字符的类型对应的值。
 */
int characterType( char ch ) {
    if( ch == '\t' || ch == ' ' || ch == '\n' || ch == 0 ) return 0;
    switch( ch ) {
        case '+': return 1;
        case '-': return 2;
        case '*': return 3;
        case '/': return 4;
        case '%': return 5;
        case '>': return 6;
        case '<': return 7;
        case '=': return 8;
        case '!': return 9;
        case '&': return 10;
        case '|': return 11;
        case ',': return 12;
        case '(': return 13;
        case ')': return 14;
        case '{': return 15;
        case '}': return 16;
        case ';': return 17;
        case '.': return 18;
        default: break;
    }
    if( '0' <= ch && ch <= '9' ) return 19 + ch - '0';
    if( 'a' <= ch && ch <= 'z' ) return 29 + ch - 'a';
    if( 'A' <= ch && ch <= 'Z' ) return 55 + ch - 'A';
    return -1;
}

/*
 * 功能： 
 *  将double类型值转换为二进制表示。
 * 传入参数： 
 *  d:待转换的double值
 * 传出参数：
 *  str:该double类型值得二进制表示字符串
 * 返回值：（无）
 */
void dtob( double d, string &str ) {
    int a, cnt = 0, flag = 0;
    if( d < 0 ) { d = -d; flag = 1; }
    str = "";
    a = ( int )d; d = d - a;
    while( a ) {
        str = ( char )( ( a & 1 ) + '0' ) + str;
        a >>= 1;
    }
    str += ".";
    while( cnt < PRECISION ) {
        d = d * 2;
        a = ( int )d;
        d -= a;
        str += a + '0';
        ++cnt;
    }
    if( flag ) str = "1" + str;
    else str = "0" + str;
    return ;
}

/*
 * 功能： 
 *  将得到的合法字符串加入到二元式序列中
 * 传入参数： 
 *  str:待加入二元式的合法字符串
 * 传出参数：
 *  vTable:更新后的二元式序列
 * 返回值：（无）
 */
void addPair( string str, vector<PIS> &vTable ) {
    if( str == "+" )       vTable.push_back( make_pair( 1, "-" ) );
    else if( str == "-" )  vTable.push_back( make_pair( 2, "-" ) );
    else if( str == "*" )  vTable.push_back( make_pair( 3, "-" ) );
    else if( str == "/" )  vTable.push_back( make_pair( 4, "-" ) );
    else if( str == "%" )  vTable.push_back( make_pair( 5, "-" ) );
    else if( str == "++" ) vTable.push_back( make_pair( 6, "-" ) );
    else if( str == "--" ) vTable.push_back( make_pair( 7, "-" ) );
    else if( str == ">" )  vTable.push_back( make_pair( 8, "-" ) );
    else if( str == "<" )  vTable.push_back( make_pair( 9, "-" ) );
    else if( str == "==" ) vTable.push_back( make_pair( 10, "-" ) );
    else if( str == ">=" ) vTable.push_back( make_pair( 11, "-" ) );
    else if( str == "<=" ) vTable.push_back( make_pair( 12, "-" ) );
    else if( str == "!=" ) vTable.push_back( make_pair( 13, "-" ) );
    else if( str == "!" )  vTable.push_back( make_pair( 14, "-" ) );
    else if( str == "&&" ) vTable.push_back( make_pair( 15, "-" ) );
    else if( str == "||" ) vTable.push_back( make_pair( 16, "-" ) );
    else if( str == "<<" ) vTable.push_back( make_pair( 17, "-" ) );
    else if( str == ">>" ) vTable.push_back( make_pair( 18, "-" ) );
    else if( str == "=" )  vTable.push_back( make_pair( 19, "-" ) );
    else if( str == "+=" ) vTable.push_back( make_pair( 20, "-" ) );
    else if( str == "-=" ) vTable.push_back( make_pair( 21, "-" ) );
    else if( str == "*=" ) vTable.push_back( make_pair( 22, "-" ) );
    else if( str == "/=" ) vTable.push_back( make_pair( 23, "-" ) );
    else if( str == "%=" ) vTable.push_back( make_pair( 24, "-" ) );
    else if( str == "," )  vTable.push_back( make_pair( 25, "-" ) );
    else if( str == "(" )  vTable.push_back( make_pair( 26, "-" ) );
    else if( str == ")" )  vTable.push_back( make_pair( 27, "-" ) );
    else if( str == "{" )  vTable.push_back( make_pair( 28, "-" ) );
    else if( str == "}" )  vTable.push_back( make_pair( 29, "-" ) );
    else if( str == ";" )  vTable.push_back( make_pair( 30, "-" ) );
    else if( str == "void" )   vTable.push_back( make_pair( 31, "-" ) );
    else if( str == "int" )    vTable.push_back( make_pair( 32, "-" ) );
    else if( str == "float" )  vTable.push_back( make_pair( 33, "-" ) );
    else if( str == "double" ) vTable.push_back( make_pair( 34, "-" ) );
    else if( str == "if" )     vTable.push_back( make_pair( 35, "-" ) );
    else if( str == "else" )   vTable.push_back( make_pair( 36, "-" ) );
    else if( str == "for" )    vTable.push_back( make_pair( 37, "-" ) );
    else if( str == "do" )     vTable.push_back( make_pair( 38, "-" ) );
    else if( str == "while" )  vTable.push_back( make_pair( 39, "-" ) );
    else if( ( 'a' <= str[0] && str[0] <= 'z' ) ||
            ( 'A' <= str[0] && str[0] <= 'Z' ) ) {
        for( int i = 0; i < str.length(); ++i ) {
            if( 'A' <= str[i] && str[i] <= 'Z' )
                str[i] += 'a' - 'A';
        }
        vTable.push_back( make_pair( 40, str ) );
    } else {
        double a;
        sscanf( str.c_str(), "%lf", &a );
        dtob( a, str );
        vTable.push_back( make_pair( 41, str ) );
    }
    return ;
}

/*
 * 功能： 
 *  阶段0处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_0( int &stage, int chtype ) {
    if( chtype == 0 ) stage = 0;
    else if( ( 3 <= chtype && chtype <= 5 ) ||
            chtype == 8 || chtype == 9 ) stage = 1;
    else if( chtype == 6 )  stage = 2;
    else if( chtype == 7 )  stage = 3;
    else if( chtype == 10 ) stage = 4;
    else if( chtype == 11 ) stage = 5;
    else if( 29 <= chtype && chtype <= 80 ) stage = 6;
    else if( chtype == 1 )  stage = 7;
    else if( chtype == 2 )  stage = 8;
    else if( 19 <= chtype && chtype <= 28 ) stage = 9;
    else if( chtype == 18 ) stage = 14;
    else if( 12 <= chtype && chtype <= 17 ) stage = 15;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段1处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_1( int &stage, int chtype ) {
    if( chtype == 8 ) stage = 15;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段2处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_2( int &stage, int chtype ) {
    if( chtype == 6 || chtype == 8 ) stage = 15;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段3处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_3( int &stage, int chtype ) {
    if( chtype == 7 || chtype == 8 ) stage = 15;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段4处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_4( int &stage, int chtype ) {
    if( chtype == 10 ) stage = 15;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段5处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_5( int &stage, int chtype ) {
    if( chtype == 11 ) stage = 15;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段6处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_6( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 80 ) stage = 6;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段7处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_7( int &stage, int chtype ) {
    if( chtype == 1 || chtype == 8 ) stage = 15;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段8处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_8( int &stage, int chtype ) {
    if( chtype == 2 || chtype == 8 ) stage = 15;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段9处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_9( int &stage, int chtype ) {
    if( chtype == 33 || chtype == 59 ) stage = 11;
    else if( chtype == 18 ) stage = 10;
    else if( 19 <= chtype && chtype <= 28 ) stage = 9;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段10处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_10( int &stage, int chtype ) {
    if( chtype == 33 || chtype == 59 ) stage = 11;
    else if( 19 <= chtype && chtype <= 28 ) stage = 10;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段11处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_11( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 13;
    else if( chtype == 1 || chtype == 2 ) stage = 12;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段12处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_12( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 13;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段13处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_13( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 13;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段14处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_14( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 10;
    else return false;
    return true;
}

/*
 * 功能： 
 *  阶段15处理
 * 传入参数： 
 *  stage:当前阶段
 *  chtype:下一个字符的类别
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool stage_15( int &stage, int chtype ) {
    return false;
}

/*
 * 功能： 
 *  阶段转换
 * 传入参数： 
 *  Stage:当前阶段
 *  ch:下一个字符
 * 传出参数：
 *  stage:下一个阶段
 * 返回值：
 *  是否进入下一个合法的阶段。进入返回true，否则返回false。
 */
bool excute( int &stage, char ch ) {
    int chtype = characterType( ch );
    bool flag = true;
    switch( stage ) {
        case 0: flag = stage_0( stage, chtype ); break;
        case 1: flag = stage_1( stage, chtype ); break;
        case 2: flag = stage_2( stage, chtype ); break;
        case 3: flag = stage_3( stage, chtype ); break;
        case 4: flag = stage_4( stage, chtype ); break;
        case 5: flag = stage_5( stage, chtype ); break;
        case 6: flag = stage_6( stage, chtype ); break;
        case 7: flag = stage_7( stage, chtype ); break;
        case 8: flag = stage_8( stage, chtype ); break;
        case 9: flag = stage_9( stage, chtype ); break;
        case 10: flag = stage_10( stage, chtype ); break;
        case 11: flag = stage_11( stage, chtype ); break;
        case 12: flag = stage_12( stage, chtype ); break;
        case 13: flag = stage_13( stage, chtype ); break;
        case 14: flag = stage_14( stage, chtype ); break;
        case 15: flag = stage_15( stage, chtype ); break;
        default: flag = false;
    }
    return flag;
}

/*
 * 功能： 
 *  行词法分析
 * 传入参数： 
 *  line:包含该行的字符串
 *  colNo:起始处理位置
 * 传出参数：
 *  colNo:处理完成位置
 *  errmsg:错误信息
 *  vTable:该行的二元式序列
 * 返回值：
 *  该行是否成功解析。成功返回true，否则返回false。
 */
bool lineAnalyse( string &line, int &colNo, string &errmsg, vector<PIS> &vTable ) {
    int stage = 0, st = 0, prestage = 0, len = line.length();
    bool flag = true;
    char prech;
    string str = "";
    while( colNo < len ) {
        st = colNo; prestage = -1; prech = ' ';
        while( colNo <= len && colNo - st + 1 <= WORDMAXLEN ) {
            prestage = stage;
            flag = excute( stage, line[colNo] );
            if( !flag ) break;
            if( characterType( line[colNo] ) > 0 ) str += line[colNo];
            prech = line[colNo];
            ++colNo;
        }
        if( !isTerminalStage( prestage ) ) {
            errmsg = str + " is illegal.";
            return false;
        }
        addPair( str, vTable );
        stage = 0; str = "";
    }
    return true;
}
