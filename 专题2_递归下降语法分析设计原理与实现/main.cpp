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
void errMsg( string filename, int nrow, int ncol, string errmsg ) {
    printf( "%s:%d:%d syntax error: %s\n", filename.c_str(), nrow, ncol, errmsg.c_str() );
    return ;
}

int main( int argc, char **argv ) {
    bool flag = true;
    char str[MAXLEN], inputName[MAXLEN], outputName[MAXLEN], line[MAXLEN];
    int nrow = 0, ncol;
    FILE *finp;
    string errmsg;
    // 打开文件
    finp = fopen( argv[1], "r" );

    // 行处理
    while( NULL != fgets( line, MAXLEN, finp ) ) {
        ++nrow; ncol = 0;
        int len = strlen( line );
        line[len - 1] = 0;
        --len;
        // 行解析
        if( !Parse( line, errmsg, ncol ) ) {
            errMsg( argv[1], nrow, ncol, errmsg );
            flag = false;
        }
    }
    if( !flag ) puts( "Syntax Error!" );
    else puts( "Program OK!" );
    fclose( finp );
    return 0;
}
