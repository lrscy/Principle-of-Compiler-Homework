#include "lexerProcessor.h"
#include "lexer.h"

/*
 * 功能：
 *  向屏幕输出错误信息
 * 传入参数： 
 *  filename:正在处理的文件的文件名称
 *  rowNo:出错行
 *  colNo:出错列
 *  errmsg:错误信息
 * 传出参数：（无）
 * 返回值：（无）
 */
void lexerErrMsg( string filename, int rowNo, int colNo, string errmsg ) {
    printf( "%s:%d:%d error: %s\n", filename.substr( 3 ).c_str(), rowNo, colNo, errmsg.c_str() );
    return ;
}

/*
 * 功能：
 *  预处理，删除字符串内注释
 * 传入参数： 
 *  str:需处理的字符串
 *  Noteflag:该字符串是否处于多行注释中
 * 传出参数：
 *  str:处理过的字符串
 *  noteflag:当前行是否处于多行注释中
 * 返回值：
 *  是否成功处理。如果注释匹配则返回true，否则返回false。
 */
bool noteProcess( string &str, bool &noteflag, string &errmsg ) {
    while( true ) {
        int p1 = str.find( "//" );
        int p2 = str.find( "/*" );
        int p3 = str.find( "*/" );
        if( p1 == -1 && p2 == -1 && p3 == -1 ) break;
        int minp = str.length();
        if( ~p1 ) minp = min( minp, p1 );
        if( ~p2 ) minp = min( minp, p2 );
        if( ~p3 ) minp = min( minp, p3 );
        if( noteflag ) {
            if( p3 == -1 ) { str = ""; break; }
            else {
                noteflag = false;
                str = str.substr( p3 + 2, str.length() - p3 - 2 );
            }
        } else {
            if( minp == p3 ) {
                errmsg = "*/ cannot be matched.";
                noteflag = false;
                return false;
            } else if( minp == p2 ) {
                if( p3 == -1 ) { str = str.substr( 0, p2 ); noteflag = true; }
                else str = str.substr( 0, p2 ) + str.substr( p3 + 2, str.length() - p3 - 2 );
            } else if( minp == p1 ) {
                str = str.substr( 0, p1 );
            }
        }
    }
    return true;
}

/*
 * 功能：
 *  将结果输出到文件中
 * 传入参数： 
 *  fp:输出文件指针
 *  vTable:二元式序列
 * 传出参数：（无）
 * 返回值：（无）
 */
void print( FILE *fp, vector<PIS> &vTable ) {
    for( int i = 0; i < vTable.size(); ++i ) {
        fprintf( fp, "( %d, %s )\n", vTable[i].first, vTable[i].second.c_str() );
    }
    fprintf( fp, "#\n" );
    return ;
}

bool lexer( char *inputName ) {
    char line[LINEMAXLEN], outputName[MAXLEN] = "tmp.lexer";
    int rowNo, colNo;
    bool flag = true, noteflag = false;
    FILE *finp, *foutp;
    string errmsg;
    vector<PIS> vTable;
    
    finp = fopen( inputName, "r" );
    foutp = fopen( outputName, "w+" );

    // 行处理
    rowNo = 0;
    while( NULL != fgets( line, MAXLEN, finp ) ) {
        vTable.clear();
        int len = strlen( line );
        if( line[len - 1] == '\n' ) line[len - 1] = 0;
        colNo = 0;
        string str = line;
        str = str.substr( 0, LINEMAXLEN );
        // 注释预处理及词法分析
        if( !noteProcess( str, noteflag, errmsg ) ||
                ( str.length() > 0 && !lineAnalyse( str, colNo, errmsg, vTable ) ) ) {
            flag = false;
            lexerErrMsg( inputName, rowNo + 1, colNo + 1, errmsg );
        }
        print( foutp, vTable );
        ++rowNo;
    }
    if( noteflag ) {
        colNo = 0;
        flag = false;
        errmsg = "/* cannot be mateched.";
        lexerErrMsg( inputName, rowNo + 1, colNo + 1, errmsg );
    }

    if( !flag ) {
        fclose( foutp );
        foutp = fopen( outputName, "w" );
    }
    fclose( finp ); fclose( foutp );
    return flag;
}
