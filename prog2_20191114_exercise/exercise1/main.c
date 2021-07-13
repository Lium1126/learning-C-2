//
//  main.c
//  exercise1
//
//  Created by k19061kk on 2019/11/13.
//  Copyright © 2019 AIT. All rights reserved.
//

/*------------------------------------------------------+
 プログラミング及び演習II 第7回
 課題
 はじめに人数入力を受け付ける。テストの点数(100点満点)の入力を人数分
 だけ受け付ける。平均と標準偏差を出力せよ。
 また、このテストで50点をとる確率を求めて出力せよ。
    ※50点の確率は正規分布の式を用いれば算出できる
    ※malloc()を使って人数分の点数領域を確保せよ
 +------------------------------------------------------*/

//インクルード=======================================================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//関数プロトタイプ宣言================================================================
double seekAverage(int *array, int n);                 // n個の配列arrayの平均を求める
double seekDispersion(int *array, double avg, int n);  // n個の配列arrayの分散を求める
double f(double x, double avg, double disp);           // 正規分布の確率密度関数
double seekArea(double x, double avg, double disp);    // f(x)のx=0からxまでの面積を求める

//関数群===========================================================================
int main(int argc, const char * argv[]) {
    int n;            // 人数
    int *input;       // 入力値を受け付ける領域へのポインタ(動的に確保)
    int i;            // カウンタ変数
    double avg;       // 平均
    double disp;      // 分散
    
    /*---人数の入力---*/
    printf("人数を入力してください: ");
    do{
        scanf("%d", &n);
        if(n <= 0){
            printf("不適な入力です\n");
        }
    }while(n <= 0);
    
    /*---人数分のメモリ領域を確保---*/
    if((input = (int*)malloc(sizeof(int) * n)) == NULL){
        fprintf(stderr, "No enough memory.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---点数を入力---*/
    for(i = 0;i < n;i++){
        do{
            printf("%d人目の点数: ", i + 1);
            scanf("%d", &input[i]);
            if(input[i] < 0 || input[i] > 100){
                printf("不適な入力です\n");
            }
        }while(input[i] < 0 || input[i] > 100);
    }
    
    /*---平均と分散を求める--*/
    avg = seekAverage(input, n);
    disp = seekDispersion(input, avg, n);
    
    /*---平均と標準偏差を出力---*/
    printf("平均:%f\n", avg);
    printf("標準偏差:%f\n", sqrt(disp));  // 標準偏差は分散の平方根
    
    /*---50点をとる確率を求める---*/
    if(disp == 0){
        printf("分散が0であるため50点をとれる確率を計算できません\n");
    }else{
        printf("50点をとる確率は%.2f%%です\n", fabs(seekArea(50.5, avg, disp) - seekArea(49.5, avg, disp)) * 100.0);
    }
    
    /*---後処理---*/
    free(input);
    
    return 0;
}

//-----------------------------------------------------
//機能:n個からなるデータ配列arrayの平均値を求める
//引数 int *array:平均値を求めるデータ配列
//    int n     :arrayの要素数
//返り値:平均値をdouble型で返す
//-----------------------------------------------------
double seekAverage(int *array, int n)
{
    int sum = 0;  // データの合計
    int i;        // カウンタ変数
    
    for(i = 0;i < n;i++){
        sum += array[i];
    }
    
    return((double)sum / (double)n);
}

//-----------------------------------------------------
//機能:n個からなるデータ配列arrayの分散を求める
//引数 int *array:標準偏差を求めるデータ配列
//    double avg:arrayの平均値
//    int n     :arrayの要素数
//返り値:分散をdouble型で返す
//-----------------------------------------------------
double seekDispersion(int *array, double avg, int n)
{
    double disp; // 分散
    double temp; // 偏差の2乗の合計
    int i;       // カウンタ変数
    
    /*---分散を求める---*/
    temp = 0;
    for(i = 0;i < n;i++){
        temp += pow((double)array[i] - avg, 2.0);
    }
    disp = temp / (double)n;
    
    /*---標準偏差は分散の平方根---*/
    return(disp);
}

//-----------------------------------------------------
//機能:正規分布の確率密度関数
//引数 double x   :独立変数
//    double avg :データの平均---+
//    double disp:データの分散---+-入力値に依存
//-----------------------------------------------------
double f(double x, double avg, double disp)
{
    return(pow(sqrt(2.0 * M_PI) * sqrt(disp), -1.0) * pow(M_E, -(pow(x - avg, 2.0) / (2 * disp))));
}

//-----------------------------------------------------
//機能:正規分布の確率密度関数に対して、x=0からxまでの面積を求める
//    これは、ある事象の確率変数Xが、0<=X<=xとなる事象の生起確率
//    に等しい
//引数 double x:面積を求める右端
//戻り値:f(x)における面積
//-----------------------------------------------------
double seekArea(double x, double avg, double disp)
{
    double area = 0;       // 区分求積法によって求められる面積
    double i;              // カウンタ変数
    double n = 1000000.0;  // 分解能
    
    x = fabs(x);  // 正規分布の確率密度関数は左右対象なグラフなので、絶対値をとっても問題ない
    
    /*---区分求積法---*/
    for(i = 0;i < n - 1.0;i++){
        area += ((x / n) * f(i * (x / n) + (x / (2.0 * n)), avg, disp));
    }
    
    return(area);
}
