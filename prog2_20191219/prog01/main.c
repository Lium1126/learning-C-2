//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/12/18.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------+
 プログラミング及び演習II 第12回
 問題1
 Σ[k=0,n]a^(n-k)を計算する関数をつくれ.
 n=10,a=4としたときの値を表示せよ.
 +----------------------------------------*/

#include <stdio.h>
#include <math.h>

//#define ANOTHER_SOLUTION

int sumNumberSequence(int n, int a);    // Σ[k=0,n]a^(n-k)を計算する関数

int main(int argc, const char * argv[]) {
    int n = 10, a = 4;
    printf("Σ[k=0,%d]%d^(%d-k) = %d\n", n, a, n ,sumNumberSequence(n, a));
    return 0;
}

//-------------------------------------------------
//機能:Σ[k=0,n]a^(n-k)を計算する
//引数 int n:---+
//    int a:---+--計算に必要なパラメータ
//返り値:計算した結果
//-------------------------------------------------
#ifndef ANOTHER_SOLUTION
int sumNumberSequence(int n, int a) {
    if (n == 0) {
        return(1);
    } else if (n < 0) {
        // 不正な関数呼び出しへの対処
        return(0);
    } else {
        int rec = 0;
        rec += (int)pow((double)a, (double)n) + sumNumberSequence(n - 1, a);
        return(rec);
    }
}
#endif

#ifdef ANOTHER_SOLUTION
int sumNumberSequence(int n, int a) {
    int k;
    int result = 0;
    
    for(k = 0;k <= n;k++) {
        result += pow((double)a, (double)(n - k));
    }
    
    return(result);
}
#endif
