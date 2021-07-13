//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/11/13.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------------------------+
プログラミング及び演習II 第7回
問題2
charのポインタpを用意し、動的に5文字分のメモリ領域
を確保する。確保した領域にhogeという文字列を入れ、
表示せよ。
+------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char *p;  // 動的に確保したメモリ領域の先頭を指すポインタ
    
    /*---5文字分のメモリ領域を動的に確保---*/
    p = (char*)malloc(sizeof(char) * 5);
    
    /*---"hoge"という文字列を確保した領域に代入---*/
    strcpy(p, "hoge");
    
    /*---出力---*/
    printf("result:%s\n", p);
    
    /*---後処理---*/
    free(p);
    
    return 0;
}
