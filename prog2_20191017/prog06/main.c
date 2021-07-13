//
//  main.c
//  prog06
//
//  Created by k19061kk on 2019/10/17.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------------+
プログラミング及び演習II 第3回
問題6
3値のソートを行う関数を実装せよ。
 (swap(),sort()関数を使用する)
 (swap(),sort()関数ともに手を加えずそのまま使用する)
+--------------------------------------------*/

#include <stdio.h>

void swap(int *pnum1, int *pnum2);              // 2つの整数値入れ替える
void sort(int *pnum1, int *pnum2);              // 2つの整数値を昇順ソートする
void sort3(int *pnum1, int *pnum2, int *pnum3); // 3つの整数値を昇順ソートする

int main(int argc, const char * argv[]) {
    int num1, num2, num3; // ソートする整数値を格納する変数
    
    /*---入力---*/
    printf("num1 num2 num3? ");
    scanf("%d %d %d", &num1, &num2, &num3);
    
    /*---3値のソート---*/
    sort3(&num1, &num2, &num3);
    
    /*---ソート結果の出力---*/
    printf("ソート後:num1 = %d, num2 = %d, num3 = %d\n", num1, num2, num3);
    
    return 0;
}

//----------------------------------------------
//機能  :2つの整数値を入れ替える
//引数 int *pnum1:---+
//    int *pnum2:---+--入れ替える整数値へのポインタ
//返り値:なし
//----------------------------------------------
void swap(int *pnum1, int *pnum2)
{
    int temp; // 作業用変数
    
    /*---値の入れ替え---*/
    temp = *pnum1;
    *pnum1 = *pnum2;
    *pnum2 = temp;
    
    return;
}

//----------------------------------------------
//機能  :2つの整数値をソートする
//引数 int *pnum1:---+
//    int *pnum2:---+--ソートする整数値へのポインタ
//返り値:なし
//-----------------------------------------------
void sort(int *pnum1, int *pnum2)
{
    // num1が大きい場合は入れ替える
    if(*pnum1 > *pnum2){
        swap(pnum1, pnum2);
    }
    return;
}

//----------------------------------------------
//機能  :3つの整数値をソートする
//引数 int *pnum1:---+
//    int *pnum2:---+--ソートする整数値へのポインタ
//    int *pnum3:---+
//返り値:なし
//----------------------------------------------
void sort3(int *pnum1, int *pnum2, int *pnum3)
{
    sort(pnum1, pnum2);
    sort(pnum2, pnum3);
    sort(pnum1, pnum2);
    return;
}
