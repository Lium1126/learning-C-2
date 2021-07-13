//
//  main.c
//  exercise01
//
//  Created by k19061kk on 2019/10/17.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------------+
プログラミング及び演習II 第3回
課題
getAvgSD()という関数を用意する。
 ・引数は4つ、返り値はなし
 ・ユーザからintの入力を2つ受け付ける
 ・入力値の平均値と標準偏差をdoubleとして計算する
 
main()関数の中でgetAvgSD()を呼び出し、計算された値
を出力しなさい。
+--------------------------------------------*/

#include <stdio.h>
#include <math.h>

void getAvgSD(int a, int b, double *avg_p, double *sd_p); // 2値の平均値と標準偏差を求める

int main(int argc, const char * argv[]) {
    int a, b;       // 入力値を格納する変数
    double avg, sd; // avg:平均値 sd:標準偏差
    
    /*---入力---*/
    printf("a b? ");
    scanf("%d %d", &a, &b);
    
    /*---平均と標準偏差を求める---*/
    getAvgSD(a, b, &avg, &sd);
    
    /*---出力---*/
    printf("平均値:%f 標準偏差:%f\n", avg, sd);
    
    return 0;
}

//------------------------------------------------------
//機能  :2つの整数値の平均値と標準偏差を求める
//引数 int a        :---+
//    int b        :---+--平均値と標準偏差を求める対象の整数
//    double *avg_p:求めた平均値を格納する先を指すポインタ
//    double *sd_p :求めた標準偏差を格納する先を指すポインタ
//返り値:なし
//------------------------------------------------------
void getAvgSD(int a, int b, double *avg_p, double *sd_p)
{
    *avg_p = ((double)a + (double)b) / 2.0;
    *sd_p = sqrt(0.5 * (pow((double)a - *avg_p, 2.0) + pow((double)b - *avg_p, 2.0)));
    return;
}
