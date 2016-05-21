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
void errMsg( string filename, int rowNo, int colNo, string errmsg ) {
    printf( "%s:%d:%d error: %s\n", filename.c_str(), rowNo, colNo, errmsg.c_str() );
    return ;
}

int main( int argc, char **argv ) {
    FILE *finp;
    char line[MAXLEN], str[MAXLEN];
    int type, nrow, ncol;
    bool flag = true;
    vector<PIS> vec;
    string errmsg;

    init();

    finp = fopen( argv[1], "r" );
    
    nrow = 0;
    // 行处理
    while( NULL != fgets( line, MAXLEN, finp ) ) {
        vec.clear();
        // 读入一行代码的二元组序列
        do {
            if( line[0] == '#' ) break;
            sscanf( line, "(%d,%s)", &type, str );
            vec.push_back( make_pair( type, str ) );
        } while( NULL != fgets( line, MAXLEN, finp ) );
        ncol = 0;
        // 行解析
        if( !Parse( vec, ncol, errmsg ) ) {
            flag = false;
            errMsg( argv[1], nrow, ncol, errmsg );
        }
        if( !flag ) puts( "Syntax Error!" );
        else puts( "Program OK!" );
    }
    fclose( finp );
    return 0;
}
