//
//  main.c
//  prog08
//
//  Created by k19061kk on 2019/10/24.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------------------+
プログラミング及び演習II 第4回
問題8
要素数5,4のint型配列を用意する
    int a[5] = {10, 20, 30, 40, 50};
    int b[4] = {3, 4, 5, 6};
配列内の数字を10倍する関数を作成せよ
上記の問題をsizeofを使って実現せよ
+------------------------------------*/

#include <stdio.h>

void times10(int *p, int n);  // 配列の要素を10倍する

int main(int argc, const char * argv[]) {
    int a[5] = {10, 20, 30, 40, 50};
    int b[4] = {3, 4, 5, 6};
    int size_a = sizeof(a) / sizeof(a[0]); // aの要素数
    int size_b = sizeof(b) / sizeof(b[0]); // bの要素数
    int i;  // カウンタ変数
    
    times10(a, size_a);
    times10(b, size_b);
    
    /*---出力---*/
    for(i = 0;i < 5;i++){
        printf("a[%d]:%d\n", i, a[i]);
    }
    for(i = 0;i < 4;i++){
        printf("b[%d]:%d\n", i ,b[i]);
    }
    
    return 0;
}

//------------------------------------------
//機 能:配列の要素を10倍する
//引数 int *p:要素を10倍するint型配列
//    int n :配列の要素数
//返り値:なし
//------------------------------------------
void times10(int *p, int n)
{
    int i;  // カウンタ変数
    
    /*---arrayの要素を10倍する---*/
    for(i = 0;i < n;i++){
        p[i] *= 10;
    }
    
    return;
}
