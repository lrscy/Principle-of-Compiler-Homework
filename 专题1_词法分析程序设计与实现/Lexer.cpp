#include "lexer.h"

bool isTerminalStage( int stage ) {
    if( stage == 0 || stage == 4 || stage == 5 || stage == 10 ||
        stage == 13 || stage == 14 || stage == 16 ) return false;
    return true;
}

int characterType( char ch ) {
    if( ch == ' ' || ch == '\n' || ch == 0 ) return 0;
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

void dtob( int d, string &str ) {
    int a = ( int )d, cnt = 0;
    d = d - a;
    while( a ) {
        str = ( char )( ( a & 1 ) + '0' ) + str;
        a >>= 1;
    }
    reverse( str.begin(), str.end() );
    str += ".";
    while( cnt < PRECISION ) {
        d = d * 2;
        a = ( int )d;
        str += a + '0';
        ++cnt;
    }
    return ;
}

void check( string str ) {
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
        vTable.push_back( make_pair( 40, str ) );
    } else {
        double a;
        sscanf( str.c_str(), "(%lf)", &a );
        if( a < 0 ) { str = "1"; a = -a; }
        else str = "0";
        dtob( a, str );
        vTable.push_back( make_pair( 41, str ) );
    }
    return ;
}

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
    else if( chtype == 13 ) stage = 9;
    else if( chtype == 12 || ( 14 <= chtype && chtype <= 17 ) ) stage = 17;
    else return false;
    return true;
}

bool stage_1( int &stage, int chtype ) {
    if( chtype == 8 ) stage = 17;
    else return false;
    return true;
}

bool stage_2( int &stage, int chtype ) {
    if( chtype == 6 || chtype == 8 ) stage = 17;
    else return false;
    return true;
}

bool stage_3( int &stage, int chtype ) {
    if( chtype == 7 || chtype == 8 ) stage = 17;
    else return false;
    return true;
}

bool stage_4( int &stage, int chtype ) {
    if( chtype == 10 ) stage = 17;
    else return false;
    return true;
}

bool stage_5( int &stage, int chtype ) {
    if( chtype == 11 ) stage = 17;
    else return false;
    return true;
}

bool stage_6( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 80 ) stage = 6;
    else return false;
    return true;
}

bool stage_7( int &stage, int chtype ) {
    if( chtype == 1 || chtype == 8 ) stage = 17;
    else return false;
    return true;
}

bool stage_8( int &stage, int chtype ) {
    if( chtype == 2 || chtype == 8 ) stage = 17;
    else return false;
    return true;
}

bool stage_9( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 11;
    else if( chtype == 1 || chtype == 2 ) stage = 10;
    else if( chtype == 18 ) stage = 16;
    else return false;
    return true;
}

bool stage_10( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 11;
    else if( chtype == 18 ) stage = 16;
    else return false;
    return true;
}

bool stage_11( int &stage, int chtype ) {
    if( chtype == 32 || chtype == 58 ) stage = 13;
    else if( chtype == 18 ) stage = 12;
    else if( 19 <= chtype && chtype <= 28 ) stage = 11;
    else if( chtype == 14 ) stage = 17;
    else return false;
    return true;
}

bool stage_12( int &stage, int chtype ) {
    if( chtype == 32 || chtype == 58 ) stage = 13;
    else if( 19 <= chtype && chtype <= 28 ) stage = 12;
    else if( chtype == 14 ) stage = 17;
    else return false;
    return true;
}

bool stage_13( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 15;
    else if( chtype == 1 || chtype == 2 ) stage = 14;
    else return false;
    return true;
}

bool stage_14( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 15;
    else return false;
    return true;
}

bool stage_15( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 15;
    else if( chtype == 14 ) stage = 17;
    else return false;
    return true;
}

bool stage_16( int &stage, int chtype ) {
    if( 19 <= chtype && chtype <= 28 ) stage = 12;
    else return false;
    return true;
}

bool stage_17( int &stage, int chtype ) {
    return false;
}

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
        case 16: flag = stage_16( stage, chtype ); break;
        case 17: flag = stage_17( stage, chtype ); break;
        default: flag = false;
    }
    return flag;
}

bool lineAnalyse( string &line, int &colNo ) {
    int stage = 0, st = 0, prestage = 0, len = line.length();
    bool flag = true;
    string str = "";
    while( colNo < len ) {
        st = colNo; prestage = -1;
        while( colNo <= len && colNo - st + 1 <= WORDMAXLEN ) {
            prestage = stage;
            flag = excute( stage, line[colNo] );
            if( !flag ) break;
            str += line[colNo];
            ++colNo;
        }
        if( !isTerminalStage( prestage ) ) {
            errmsg = str + " is illegal.";
            return false;
        }
        check( str );
        stage = 0; str = "";
    }
    return true;
}
