//
//  main.c
//  exercise01
//
//  Created by k19061kk on 2019/10/24.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------+
プログラミング及び演習II 第4回
課題
配列を受け取ってバブルソートを行う関数bubble
を作成せよ
main関数でbubbleを呼び出し、ソート前後で配列
要素を出力して結果を確認せよ
+--------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 30

void bubble(int *array, int num);     // 配列arrayに対してバブルソートを行う
void printData(int *array, int num);  // 配列の要素を表示する
void sort(int *a, int *b);            // aとbを小さい順にソートする(bubbleのサブ関数)
void swap(int *a, int *b);            // aとbを入れ替える(sortのサブ関数)

int main(int argc, const char * argv[]) {
    int array[MAX_NUM];  // バブルソートを行う対象の配列
    int num;             // 配列の要素数
    int i;               // カウンタ変数
    
    /*---入力---*/
    printf("要素数? ");
    scanf("%d", &num);
    
    if(num > MAX_NUM){
        printf("入力可能な最大値を超えています\n");  // 例外処理
        exit(0);
    }else{
        for(i = 0;i < num;i++){
            printf("%d番目の要素? ", i + 1);
            scanf("%d", &array[i]);
        }
    }
    
    /*---ソート前に一度出力---*/
    printf("ソート前------------------\n");
    printData(array, num);
    
    /*---バブルソートを行う---*/
    bubble(array, num);
    
    /*---ソート結果を出力---*/
    printf("ソート後------------------\n");
    printData(array, num);
    
    return 0;
}

//-----------------------------------------------------
//機 能:バブルソートを行う
//引数 int *array:整列対象の配列
//    int num   :配列の要素数
//返り値:なし
//-----------------------------------------------------
void bubble(int *array, int num)
{
    int i, j; // カウンタ変数
    
    /*---バブルソート---*/
    for(i = 0;i < num - 1;i++){
        for(j = num - 1;j > i;j--){
            sort(&array[j - 1], &array[j]);
        }
    }
    
    return;
}

//-----------------------------------------------------
//機 能:配列の要素を表示する
//引数 int *array:表示対象の配列
//    int num   :配列の要素数
//返り値:なし
//-----------------------------------------------------
void printData(int *array, int num)
{
    int i;  // カウンタ変数
    
    /*---配列の要素を表示---*/
    for(i = 0;i < num;i++){
        printf("array[%d]:%d\n", i, array[i]);
    }
    
    return;
}

//-----------------------------------------------------
//機 能:2値のソートを行う
//引数 int *a:---+
//    int *b:---+--ソートを行う2値へのポインタ
//返り値:なし
//-----------------------------------------------------
void sort(int *a, int *b)
{
    if(*a > *b){
        swap(a, b);
    }
    return;
}

//-----------------------------------------------------
//機 能:2値の入れ替えを行う
//引数 int *a:---+
//    int *b:---+--入れ替える対象へのポインタ
//返り値:なし
//-----------------------------------------------------
void swap(int *a, int *b)
{
    int temp;  // 値を一時保存する作業用変数
    
    /*---値を入れ替える---*/
    temp = *a;
    *a = *b;
    *b = temp;
    
    return;
}
