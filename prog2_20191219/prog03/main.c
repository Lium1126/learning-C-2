//
//  main.c
//  prog03
//
//  Created by k19061kk on 2019/12/18.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------+
プログラミング及び演習II 第12回
問題3
フィボナッチ数列のn番目の値を求める関数をつくれ.
nが1から10のときの値をそれぞれ表示せよ.
+----------------------------------------*/

#include <stdio.h>

#define MIN_N 1
#define MAX_N 10

int solveFib(int n);

int main(int argc, const char * argv[]) {
    int n;
    
    for(n = MIN_N;n <= MAX_N;n++) {
        printf("n = %2d: %d\n", n, solveFib(n));
    }
    
    return 0;
}

//-------------------------------------------------
//機能:フィボナッチ数列のn番目の値を求める
//引数 int n:何番目のフィボナッチ数列を求めるかを表す
//返り値:n番目のフィボナッチ数列の値
//-------------------------------------------------
int solveFib(int n) {
    static int mem[MAX_N + 1] = {};
    if (mem[n] != 0) {               // n番目の値が既に計算済みだったらそれを返す
        return(mem[n]);
    } else if (n == 1 || n == 2) {  // 基底条件
        return(mem[n] = 1);
    } else if(n <= 0) {              // 不正な関数呼び出しへの対処
        return(0);
    } else {                        // 再帰呼び出し
        return(mem[n] = (solveFib(n - 1) + solveFib(n - 2)));
    }
}
