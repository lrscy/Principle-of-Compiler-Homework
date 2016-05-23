#include "parse.h"

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
void errMsgP( string filename, int nrow, int ncol, string errmsg ) {
    printf( "%s:%d:%d syntax error: %s\n", filename.c_str(), nrow, ncol, errmsg.c_str() );
    return ;
}

bool parse() {
    bool flag = true;
    char str[MAXLEN], inputName[MAXLEN] = "tmp.lexer", line[MAXLEN];
    int nrow = 0, ncol, tn;
    FILE *finp;
    string errmsg;
    vector<PIS> vec;

    init();

    // 打开文件
    finp = fopen( inputName, "r" );

    // 行处理
    while( NULL != fgets( line, MAXLEN, finp ) ) {
        vec.clear();
        // 读入一行代码的二元式序列
        do {
            if( line[0] == '#' ) break;
            sscanf( line, "(%d,%s)", &tn, str );
            vec.push_back( make_pair( tn, str ) );
        } while( NULL != fgets( line, MAXLEN, finp ) ); 
        ++nrow; ncol = 0;
        // 行解析
        if( !Parse( vec, ncol, errmsg ) ) {
            errMsgP( inputName, nrow, ncol, errmsg );
            flag = false;
        }
    }
    if( !flag ) puts( "Syntax Error!" );
    else puts( "Program OK!" );
    fclose( finp );
    return flag;
}
