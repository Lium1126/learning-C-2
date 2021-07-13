//
//  main.c
//  prog04
//
//  Created by k19061kk on 2019/11/13.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------+
プログラミング及び演習II 第7回
問題4
問題2をメモリ確保失敗に対応させよ。
+---------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char *p;  // 動的に確保したメモリ領域の先頭を指すポインタ
    
    /*---5文字分のメモリ領域を動的に確保---*/
    if((p = (char*)malloc(sizeof(char) * 5)) == NULL){
        fprintf(stderr, "No enough memory.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---"hoge"という文字列を確保した領域に代入---*/
    strcpy(p, "hoge");
    
    /*---出力---*/
    printf("result:%s\n", p);
    
    /*---後処理---*/
    free(p);
    
    return 0;
}
