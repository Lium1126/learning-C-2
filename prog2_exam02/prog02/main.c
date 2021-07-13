//
//  main.c
//  prog02
//
//  Created by k19061kk on 2020/01/23.
//  Copyright © 2020 AIT. All rights reserved.
//

/*------------------------------------------------+
 プログラミング及び演習II 期末試験
 第2問
 1回の試行を表す構造体を定義せよ.
 その構造体の情報を表示するdispTrial関数を作成せよ.
 また、以下の文字列を読み込み、構造体のメンバ変数に格納し、
 その内容をdispTrial関数を用いて表示せよ.
    char line[]="10,18\n"
 +------------------------------------------------*/

//定義===================================================================================
//インクルード------------------------------------------------------------------
#include <stdio.h>

//構造体-----------------------------------------------------------------------
typedef struct trial {
    int speed;
    int distance;
} Trial;

//関数プロトタイプ宣言======================================================================
//基本操作関数------------------------------------------------------------------
int getSpeed(Trial trial);
void setSpeed(Trial *trial, int speed);
int getDistance(Trial trial);
void setDistance(Trial *trial, int distance);

//操作関数----------------------------------------------------------------------
void dispTrial(Trial trial);

//関数===================================================================================
int main(int argc, const char * argv[]) {
    char line[] = "10,18\n";
    int input_speed, input_dist;
    Trial trial;
    
    /*---lineからデータを入力---*/
    sscanf(line, "%d,%d", &input_speed, &input_dist);
    
    /*---構造体にデータを格納---*/
    setSpeed(&trial, input_speed);
    setDistance(&trial, input_dist);
    
    /*---dispTrial()を呼び出す---*/
    dispTrial(trial);
    
    return 0;
}

//基本操作関数------------------------------------------------------------------
int getSpeed(Trial trial) {
    return(trial.speed);
}

void setSpeed(Trial *trial, int speed) {
    trial -> speed = speed;
    return;
}

int getDistance(Trial trial) {
    return(trial.distance);
}

void setDistance(Trial *trial, int distance) {
    trial -> distance = distance;
    return;
}

//操作関数----------------------------------------------------------------------
//---------------------------------------------------------------------
//機能:構造体Trialのデータ1つの内容を表示する
//引数 Trial trial:表示する対象のデータ
//返り値:なし
//---------------------------------------------------------------------
void dispTrial(Trial trial) {
    printf("Speed: %d, Distance: %d\n", getSpeed(trial), getDistance(trial));
    return;
}
