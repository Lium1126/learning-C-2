//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/11/13.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------------------+
 プログラミング及び演習II 第7回
 問題1
 intのポインタpを用意し、動的にint4つ分のメモリ領域
 を確保する。4つ分の領域にそれぞれ数字を入れ、表示せよ。
 +--------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    int *p; // 動的に確保したメモリ領域の先頭を指すポインタ
    int i;  // カウンタ変数
    
    /*---int型4つ分のメモリ領域を動的に確保---*/
    p = (int*)malloc(sizeof(int) * 4);
    
    /*--確保した領域に数値を代入---*/
    for(i = 0;i < 4;i++){
        p[i] = 5 * i;
    }
    
    /*---出力---*/
    for(i = 0;i < 4;i++){
        printf("p[%d]:%d\n", i, p[i]);
    }
    
    /*---後処理---*/
    free(p);
    
    return 0;
}
