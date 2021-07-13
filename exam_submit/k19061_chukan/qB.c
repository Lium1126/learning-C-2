//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/11/21.
//  Copyright © 2019 AIT. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void swap(int *pa, int *pb);           // 2値を入れ替える
void sort(int *pa, int *pb);           // 2値の昇順ソートを行う
void bubbleSort(int *array, int num);  // 配列arrayのデータをバブルソートによってソートする

int main(int argc, const char * argv[]) {
    int num;    // データの個数
    int *ptr;   // データを格納するメモリ領域へのポインタ(動的に確保)
    int i;      // カウンタ変数
    
    /*---データの個数の入力---*/
    printf("How many numbers? : ");
    scanf("%d", &num);
    
    /*---メモリ領域の確保---*/
    if((ptr = (int*)malloc(sizeof(int) * num)) == NULL){
        fprintf(stderr, "No enough memory.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---データの入力---*/
    for(i = 0;i < num;i++){
        printf("ptr[%d] = ", i);
        scanf("%d", &ptr[i]);
    }
    
    /*---バブルソート---*/
    bubbleSort(ptr, num);
    
    /*---ソート結果を表示---*/
    for(i = 0;i < num;i++){
        printf("new ptr[%d] = %d\n", i, ptr[i]);
    }
    
    /*---メモリ領域の開放処理---*/
    free(ptr);
    
    return 0;
}

//-----------------------------------------
//機能:2値を入れ替える
//引数 int *pa:---+
//    int *pb:---+--入れ替える値を指すポインタ
//返り値:なし
//-----------------------------------------
void swap(int *pa, int *pb) {
    int temp;
    
    temp = *pa;
    *pa = *pb;
    *pb = temp;
    
    return;
}

//-----------------------------------------
//機能:2値を昇順にソートする
//引数 int *pa:---+
//    int *pb:---+--ソートする値を指すポインタ
//返り値:なし
//-----------------------------------------
void sort(int *pa, int *pb) {
    if(*pa > *pb){
        swap(pa, pb);
    }
    return;
}

//-----------------------------------------
//機能:arrayをバブルソートによってソートする
//引数 int *array:ソートする対象の配列
//    int num   :ソートするデータの個数
//返り値:なし
//-----------------------------------------
void bubbleSort(int *array, int num) {
    int i, j;
    
    for(i = 0;i < num - 1;i++){
        for(j = num - 1;j > i;j--){
            sort(&array[j - 1], &array[j]);
        }
    }
    
    return;
}
