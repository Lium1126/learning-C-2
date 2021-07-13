//
//  main.c
//  prog06
//
//  Created by k19061kk on 2020/01/23.
//  Copyright © 2020 AIT. All rights reserved.
//

/*------------------------------------------------+
 プログラミング及び演習II 期末試験
 第6問
 Q5の直線近似についてMSEを求めよ.
 +------------------------------------------------*/

//定義===================================================================================
//インクルード------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//マクロ-----------------------------------------------------------------------
#define MAX_LEN 256

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
int linearFunction(int a, int x);
double calcMSE(Trial *trial, int n, int a);

//関数===================================================================================
int main(int argc, const char * argv[]) {
    FILE *fp;
    char line[MAX_LEN];
    int input_speed, input_dist;
    int n, i;
    int a = 2;
    Trial *trial;
    Trial *temp;
    double MSE;
    
    /*---ファイルを開く---*/
    fp = fopen("./cars.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---構造体の配列を確保---*/
    trial = (Trial*)malloc(sizeof(Trial));
    
    /*---ファイルからデータを入力し、構造体に格納---*/
    n = 0;
    while (fgets(line, MAX_LEN, fp) != NULL) {
        temp = (Trial*)realloc(trial, sizeof(Trial) * (n + 1));
        if (temp == NULL) {
            fprintf(stderr, "No enough memory.\n");
            free(trial);
            fclose(fp);
            exit(EXIT_FAILURE);
        } else {
            trial = temp;
        }
        
        sscanf(line, "%d,%d", &input_speed, &input_dist);
        setSpeed(&trial[n], input_speed);
        setDistance(&trial[n], input_dist);
        
        n++;
    }
    
    /*---ファイルを閉じる---*/
    fclose(fp);
    
    /*---推定の式を表示---*/
    printf("推定: distance = %d * speed\n", a);
    
    /*---dispTrialを用いて配列の内容と推定との誤差を表示---*/
    for (i = 0;i < n;i++) {
        dispTrial(trial[i]);
        printf(", 推定との誤差: %d\n", getDistance(trial[i]) - linearFunction(a, getSpeed(trial[i])));
    }
    
    /*---MSEを求めて表示する---*/
    MSE = calcMSE(trial, n, a);
    printf("---\n");
    printf("MSE: %lf\n", MSE);
    
    /*---trialを解放---*/
    free(trial);
    
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
//機能:構造体Trialのデータ1つの内容を表示する(改行しない)
//引数 Trial trial:表示する対象のデータ
//返り値:なし
//---------------------------------------------------------------------
void dispTrial(Trial trial) {
    printf("Speed: %2d, Distance: %3d", getSpeed(trial), getDistance(trial));
    return;
}

//---------------------------------------------------------------------
//機能:y=axを計算する
//引数 int a:傾き
//    int x:横軸変数
//返り値:y=axの値を返す
//---------------------------------------------------------------------
int linearFunction(int a, int x) {
    return(a * x);
}

//---------------------------------------------------------------------
//機能:MSEを求める
//引数 Trial *trial:速度と距離が格納された構造体の配列
//    int n       :trialの要素数
//    int a       :推定するy=axという関数の傾き
//返り値:求めたMSEを返す
//---------------------------------------------------------------------
double calcMSE(Trial *trial, int n, int a) {
    int i;
    double sum = 0;
    
    for (i = 0;i < n;i++) {
        sum += pow((double)(getDistance(trial[i]) - linearFunction(a, getSpeed(trial[i]))), 2.0);
    }
    
    return(sum / (double)n);
}
