//
//  main.c
//  prog07
//
//  Created by k19061kk on 2019/11/13.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------+
プログラミング及び演習II 第7回
問題7
ユーザから一つの数字を入力させる。
負の数が入力されるまで入力を繰り返す。
全ての入力値を最後に一度に出力する。
+-----------------------------*/

//インクルード=======================================================================
#include <stdio.h>
#include <stdlib.h>

//関数プロトタイプ宣言================================================================
void printData(int *array, int num);  // 配列arrayのデータをnum個表示する
int seekDigit(int n);                 // nの桁数を求める(printData()のサブ関数)

//関数群============================================================================
int main(int argc, const char * argv[]) {
    int idx;     // 入力を受け付ける要素のインデックス
    int *input;  // 入力値を格納する領域へのポインタ(動的に確保)
    int *temp;   // realloc用の作業用変数
    
    /*---inputに最初の1つ分を動的に確保---*/
    if((input = (int*)malloc(sizeof(int))) == NULL){
        fprintf(stderr, "No enough memory.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---インデックスをずらしながら負の数が入力されるまで入力を繰り返す---*/
    idx = -1;   // ループ初回で0にするために-1で初期化
    do{
        idx++;
        printf("input[%d]? ", idx);
        scanf("%d", &input[idx]);
        
        if(input[idx] >= 0){  // 入力値が負の数でないのでメモリ領域を再度確保(メモリ領域をidx+2個へ拡張)
            if((temp = (int*)realloc(input, sizeof(int) * (idx + 2))) == NULL){ // realloc時にメモリが不足
                printData(input, idx + 1); //---+
                free(input); //-----------------+--その時点までの出力をして、確保されているメモリを解放
                fprintf(stderr, "No enough memory.\n");
                exit(EXIT_FAILURE);
            }else{
                input = temp;
            }
        }
    }while(input[idx] >= 0);
    
    /*---データを出力---*/
    printf("------------------------------\n");
    printData(input, idx + 1);
    
    /*---後処理---*/
    free(input);
    
    return 0;
}

//--------------------------------------------------
//機能:配列arrayの内容をnum個表示する
//引数 int *array:内容を表示する配列
//    int num   :表示するデータの個数
//戻り値:なし
//--------------------------------------------------
void printData(int *array, int num)
{
    int i, j;         // カウンタ変数
    int digit_of_num; // numの桁数
    
    /*---データを表示---*/
    digit_of_num = seekDigit(num);
    for(i = 0;i < num;i++){
        for(j = 0;j < digit_of_num - seekDigit(i);j++){  // 見栄えを整えるための空白を出力
            printf(" ");
        }
        printf("%d:%d\n", i, array[i]);
    }
    
    return;
}

//-------------------------------------------------
//機能:nの桁数を求める
//引数 int n:桁数を求める対象の整数値
//戻り値:nの桁数.0の場合1、負の数の場合は絶対値の桁数を返す.
//-------------------------------------------------
int seekDigit(int n)
{
    int cnt = 0;  // 桁数をカウントするカウンタ変数
    
    /*---桁数を求める---*/
    n = abs(n);
    do{
        cnt++;
        n /= 10;
    }while(n != 0);
    
    return(cnt);
}
