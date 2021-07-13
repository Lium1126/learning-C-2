//
//  main.c
//  prog04
//
//  Created by k19061kk on 2020/01/30.
//  Copyright © 2020 AIT. All rights reserved.
//

/*-------------------------------------------+
 プログラミング及び演習II
 第15回 期末試験解答 問題4
 以下を発見して表示せよ
    ・speedの最小値
    ・speedの最大値
    ・distanceの最小値
    ・distanceの最大値
 +-------------------------------------------*/

//定義======================================================================================
//インクルード------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//マクロ-----------------------------------------------------------------
#define MAX_LEN 256

//構造体-----------------------------------------------------------------
typedef struct trial {
    int speed;      // 速度
    int distance;   // 制動距離
} Trial;

//関数プロトタイプ宣言=========================================================================
//基本操作関数-------------------------------------------------------------
int getSpeed(Trial trial);               // trialから速度の情報を取得する
void setSpeed(Trial *trial, int speed);  // trialに速度の情報を設定する
int getDist(Trial trial);                // trialから制動距離の情報を取得する
void setDist(Trial *trial, int dist);    // trialに制動距離の情報を設定する

//関数群====================================================================================
int main(int argc, const char * argv[]) {
    Trial *trial;                 // 1回の試行の情報を格納する構造体の配列(動的に確保)
    Trial *temp;                  // メモリ再確保のための作業用変数
    FILE *fp;                     // cars.csvのファイルポインタ
    char line[MAX_LEN];           // ファイル入力を1行受け付けるバッファ配列
    int input_speed, input_dist;  // 入力用変数
    int num, i;                   // カウンタ変数
    int min_speed, max_speed;     // 速度の最小値・最大値
    int min_dist, max_dist;       // 制動距離の最小値・最大値
    
    /*---入力ファイルを開く---*/
    fp = fopen("./cars.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---構造体の配列を動的に確保する---*/
    trial = (Trial*)malloc(sizeof(Trial));
    if (trial == NULL) {
        fprintf(stderr, "No enough memory.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    
    /*---ファイルから1行ずつ読み込み、構造体に格納する---*/
    num = 0;
    while (fgets(line, MAX_LEN, fp) != NULL) {
        // メモリを再確保する
        temp = (Trial*)realloc(trial, sizeof(Trial) * (num + 1));
        if (temp == NULL) {  // メモリ再確保に失敗
            fprintf(stderr, "No enough memory.\n");
            free(trial);
            fclose(fp);
            exit(EXIT_FAILURE);
        } else {             // メモリ再確保に成功
            trial = temp;
        }
        
        // ファイルから読み込んだ情報を入力用変数に格納する
        sscanf(line, "%d,%d", &input_speed, &input_dist);
        
        // 入力した情報を構造体に格納する
        setSpeed(&trial[num], input_speed);
        setDist(&trial[num], input_dist);
        
        // カウンタを進める
        num++;
    }
    
    /*---入力ファイルを閉じる---*/
    fclose(fp);
    
    /*---速度・制動距離の最小値・最大値を初期化する---*/
    min_speed = min_dist = INT_MAX;
    max_speed = max_dist = -1;
    
    /*---速度・制動距離の最小値・最大値を探索する---*/
    for (i = 0;i < num;i++) {
        if (min_speed > getSpeed(trial[i])) {
            min_speed = getSpeed(trial[i]);
        }
        if (max_speed < getSpeed(trial[i])) {
            max_speed = getSpeed(trial[i]);
        }
        if (min_dist > getDist(trial[i])) {
            min_dist = getDist(trial[i]);
        }
        if (max_dist < getDist(trial[i])) {
            max_dist = getDist(trial[i]);
        }
    }
    
    /*---速度・制動距離の最小値・最大値を表示する---*/
    printf("speedの最小値:%d\n", min_speed);
    printf("speedの最大値:%d\n", max_speed);
    printf("distanceの最小値:%d\n", min_dist);
    printf("distanceの最大値:%d\n", max_dist);
    
    /*---構造体の配列を解放する---*/
    free(trial);
    
    return 0;
}

//基本操作関数-------------------------------------------------------------
//------------------------------------------------------------
//機能:trialから速度の情報を取得する
//引数 Trial trial:1回の試行を表す構造体
//返り値:trialに格納されている速度の情報
//------------------------------------------------------------
int getSpeed(Trial trial) {
    return(trial.speed);
}

//------------------------------------------------------------
//機能:trialに速度の情報を設定する
//引数 Trial *trial:速度の情報を格納する対象の構造体へのポインタ
//    int speed   :格納する速度情報
//返り値:なし
//------------------------------------------------------------
void setSpeed(Trial *trial, int speed) {
    trial -> speed = speed;
    return;
}

//------------------------------------------------------------
//機能:trialから制動距離の情報を取得する
//引数 Trial trial:1回の試行を表す構造体
//返り値:trialに格納されている制動距離の情報
//------------------------------------------------------------
int getDist(Trial trial) {
    return(trial.distance);
}

//------------------------------------------------------------
//機能:trialに制動距離の情報を設定する
//引数 Trial *trial:制動距離の情報を格納する対象の構造体へのポインタ
//    int dist    :格納する制動距離の情報
//返り値:なし
//------------------------------------------------------------
void setDist(Trial *trial, int dist) {
    trial -> distance = dist;
    return;
}
