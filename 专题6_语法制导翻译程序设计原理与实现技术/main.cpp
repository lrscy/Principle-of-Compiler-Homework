#include "parse.h"

/*
 * 功能：
 *  得到输出文件名
 * 传入参数：inputname:需处理的文件的文件名
 * 传出参数：outputname:输出文件的文件名
 * 返回值：（无）
 */
void getOutputName( char *inputName, char *outputName ) {
    int len = strlen( inputName );
    strcpy( outputName, inputName );
    while( outputName[--len] != '.' && len > 0 );
    if( len == 0 ) outputName[len] = 'a';
    outputName[len] = 0;
    strcat( outputName, ".gen" );
    return ;
}

/*
 * 功能：
 *  向屏幕输出错误信息
 * 传入参数： 
 *  filename:正在处理的文件的文件名称
 *  rowNo:出错行
 *  colNo:出错列
 * 传出参数：（无）
 * 返回值：（无）
 */
void errMsg( string filename, int rowNo, int colNo ) {
    printf( "%s:%d:%d syntax error!\n", filename.c_str(), rowNo, colNo );
    return ;
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
void print( FILE *fp, vector<Node> &vecGen ) {
    for( int i = 0; i < vecGen.size(); ++i ) {
        fprintf( fp, "( %s, %s, %s, %s )\n",
                vecGen[i].op.c_str(), vecGen[i].arg1.c_str(),
                vecGen[i].arg2.c_str(), vecGen[i].res.c_str() );
    }
    fprintf( fp, "#\n" );
    return ;
}

int main( int argc, char **argv ) {
    FILE *finp, *foutp;
    char line[MAXLEN], str[MAXLEN], outputName[MAXLEN];
    int type, nrow, ncol;
    bool flag = true;
    vector<PIS> vec;
    vector<Node> vecGen;
    
    // 文件后缀处理
    getOutputName( argv[1], outputName );
    finp = fopen( argv[1], "r" );
    foutp = fopen( outputName, "w" );
    fclose( foutp );
    foutp = fopen( outputName, "a+" );
    getOutputName( argv[1], outputName );
    init();

    // 打开文件
    finp = fopen( argv[1], "r" );
    
    nrow = 0;
    // 行处理
    while( NULL != fgets( line, MAXLEN, finp ) ) {
        vec.clear(); vecGen.clear();
        // 读入一行代码的二元组序列
        do {
            if( line[0] == '#' ) break;
            sscanf( line, "(%d,%s)", &type, str );
            vec.push_back( make_pair( type, str ) );
        } while( NULL != fgets( line, MAXLEN, finp ) );
        vec.push_back( make_pair( 40, "#" ) );
        ++nrow; ncol = 0;
        // 行解析
        if( !sentenceAnalysis( vec, ncol, vecGen ) ) {
//        if( !sentenceAnalysis( vec, ncol ) ) {
            flag = false;
            errMsg( argv[1], nrow, ncol + 1 );
        }
        print( foutp, vecGen );
    }

    if( !flag ) {
        fclose( foutp );
        foutp = fopen( outputName, "w" );
        puts( "Syntax Error!" );
    } else puts( "Program OK!" );
    fclose( finp ); fclose( foutp );
    return 0;
}
