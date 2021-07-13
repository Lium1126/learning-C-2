//
//  main.c
//  prog04
//
//  Created by k19061kk on 2019/10/17.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------+
プログラミング及び演習II 第3回
問題4
swap()関数を実装せよ。
(2つの整数値を入れ替える関数)
+--------------------------------*/

#include <stdio.h>

void swap(int *pnum1, int *pnum2); // 2つの整数値を入れ替える

int main(int argc, const char * argv[]) {
    int num1, num2; // 入れ替える整数値を格納する変数
    
    /*---入力---*/
    printf("num1 num2? ");
    scanf("%d %d", &num1, &num2);
    
    /*---値の入れ替え---*/
    swap(&num1, &num2);
    
    /*---出力---*/
    printf("入れ替え後:num1 = %d, num2 = %d\n", num1, num2);
    
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
