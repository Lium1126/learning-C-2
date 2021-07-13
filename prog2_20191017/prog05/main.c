//
//  main.c
//  prog05
//
//  Created by k19061kk on 2019/10/17.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------+
プログラミング及び演習II 第3回
問題5
2値のソートを行うsort()関数を実装せよ。
 (問題4のswap()関数をそのまま用いること)
 (swap()関数自体には手を加えないこと)
+----------------------------------*/

#include <stdio.h>

void swap(int *pnum1, int *pnum2); // 2つの整数値入れ替える
void sort(int *pnum1, int *pnum2); // 2つの整数値を昇順ソートする

int main(int argc, const char * argv[]) {
    int num1, num2; // ソートする整数値を格納する変数
    
    /*---入力---*/
    printf("num1 num2? ");
    scanf("%d %d", &num1, &num2);
    
    /*---2値のソート---*/
    sort(&num1, &num2);
    
    /*---ソート結果の出力---*/
    printf("ソート後:num1 = %d, num2 = %d\n", num1, num2);
    
    return 0;
}

//---------------------------------------------
//機能  :2つの整数値を入れ替える
//引数 int *pnum1:---+
//    int *pnum2:---+--入れ替える整数値へのポインタ
//返り値:なし
//---------------------------------------------
void swap(int *pnum1, int *pnum2)
{
    int temp; // 作業用変数
    
    /*---値の入れ替え---*/
    temp = *pnum1;
    *pnum1 = *pnum2;
    *pnum2 = temp;
    
    return;
}


//------------------------------------------
//機能  :2つの整数値をソートする
//引数 int *pnum1:---+
//    int *pnum2:---+--ソートする整数値へのポインタ
//返り値:なし
//------------------------------------------
void sort(int *pnum1, int *pnum2)
{
    // num1が大きい場合は入れ替える
    if(*pnum1 > *pnum2){
        swap(pnum1, pnum2);
    }
    return;
}
