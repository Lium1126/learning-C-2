//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/10/23.
//  Copyright © 2019 AIT. All rights reserved.
//

/*---------------------------------+
 プログラミング及び演習II 第4回
 問題1
 ダメなswap関数とよいswap関数を作れ
 +---------------------------------*/

#include <stdio.h>

void badSwap(int a, int b);     // ダメなswap関数
void goodSwap(int *a, int *b);  // よいswap関数

int main(int argc, const char * argv[]) {
    int a, b;
    
    /*---入力---*/
    printf("a b? ");
    scanf("%d %d", &a, &b);
    
    /*---出力しつつ値の入れ替え---*/
    printf("入れ替え前:a = %d, b = %d\n", a, b);
    // badSwap(a, b);  // ダメなswap関数の呼び出し
    goodSwap(&a, &b);  // よいswap関数の呼び出し
    printf("入れ替え後:a = %d, b = %d\n", a, b);
    
    return 0;
}

//---------------------------------------
//機 能:値を入れ替える
//引 数 int a:---+
//     int b:---+--入れ替える対象
//返り値:なし
//---------------------------------------
void badSwap(int a, int b)
{
    int temp;
    
    /*---以下値の入れ替え---*/
    temp = a;
    a = b;
    b = temp;
    
    return;
}

//---------------------------------------
//機 能:値を入れ替える
//引 数 int a:---+
//     int b:---+--入れ替える対象へのポインタ
//返り値:なし
//---------------------------------------
void goodSwap(int *a, int *b)
{
    int temp;
    
    /*---以下値の入れ替え---*/
    temp = *a;
    *a = *b;
    *b = temp;
    
    return;
}
