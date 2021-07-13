//
//  main.c
//  prog04
//
//  Created by k19061kk on 2019/12/18.
//  Copyright © 2019 AIT. All rights reserved.
//

/*------------------------------------------+
プログラミング及び演習II 第12回
問題4
授業資料のにある疑似コードで示されるアルゴリズムを関数
として実装せよ.
以下の配列を上記関数に渡して、その後結果を出力せよ.
    ・int a[]={1,2,3,4,5,6,7,8,9,10};
+-------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffleArray(int *a, int n);               // 要素数n(添字は0~n-1)の配列aをシャッフルする
void swapPtr(int *a, int *b);                   // aとbを入れ替える(shuffleArrayのサブ関数)

int main(int argc, const char * argv[]) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // シャッフルする対象の配列
    int size_a;                                 // 配列aの要素数
    int i;                                      // カウンタ変数
    
    /*---配列aの要素数を求める---*/
    size_a = sizeof(a) / sizeof(a[0]);
    
    /*---配列aをシャッフルする---*/
    shuffleArray(a, size_a);
    
    /*---結果を出力---*/
    for (i = 0;i < size_a;i++) {
        printf("a[%d]: %d\n", i, a[i]);
    }
    
    return 0;
}

//-------------------------------------------------
//機能:要素数n(添字は0~n-1)の配列aをシャッフルする
//引数 int *a:シャッフルする対象の配列
//    int n :配列aの要素数
//返り値:なし
//-------------------------------------------------
void shuffleArray(int *a, int n) {
    int i;       // カウンタ変数
    int j;       // ランダムに入れ替える要素の添字
    
    /*---rand関数のシード値を変更する---*/
    srand((unsigned)time(NULL));
    
    /*---aをシャッフルする---*/
    for (i = n - 1;i >= 1;i--) {    // iをn-1から1まで減少させながら、以下を実行する
        j = rand() % (i + 1);       // jに0以上i以下のランダムな整数を代入する
        if (i != j) {
            swapPtr(&a[i], &a[j]);  // a[j]とa[i]を交換する
        }
    }
    
    return;
}

//-------------------------------------------------
//機能:aとbを入れ替える
//引数 int a:---+
//    int b:---+--入れ替える対象へのポインタ
//返り値:なし
//-------------------------------------------------
void swapPtr(int *a, int *b) {
    int temp;    // 作業用変数
    
    /*---aとbを入れ替える---*/
    temp = *a;
    *a = *b;
    *b = temp;
    
    return;
}
