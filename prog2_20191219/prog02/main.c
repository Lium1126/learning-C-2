//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/12/18.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------+
プログラミング及び演習II 第12回
問題2
x[1]=1,x[n]=x[n-1]+2を計算する関数をつくれ.
n=10のときの値を表示せよ.
+----------------------------------------*/

#include <stdio.h>

//#define ANOTHER_SOLUTION

int solveRecurrenceFormula(int n);     // 漸化式x[1]=1,x[n]=x[n-1]+2を計算する関数

int main(int argc, const char * argv[]) {
    int n = 10;
    printf("漸化式:x[1]=1,x[n]=x[n-1]+2\n");
    printf("n = %d: %d\n", n, solveRecurrenceFormula(n));
    return 0;
}

//----------------------------------------
//機能:漸化式x[1]=1,x[n]=x[n-1]+2を計算する
//引数 int n:上記式のn
//返り値:上記式を計算した結果
//----------------------------------------
#ifndef ANOTHER_SOLUTION
int solveRecurrenceFormula(int n) {
    if (n == 1) {
        return(1);
    } else if(n <= 0) {
        // 不正な関数呼び出しへの対処
        return(0);
    } else {
        return(solveRecurrenceFormula(n - 1) + 2);
    }
}
#endif

#ifdef ANOTHER_SOLUTION
int solveRecurrenceFormula(int n) {
    return(2 * (n - 1) + 1);
}
#endif
