//
//  main.c
//  prog03
//
//  Created by k19061kk on 2020/01/23.
//  Copyright © 2020 AIT. All rights reserved.
//

/*------------------------------------------------+
 プログラミング及び演習II 期末試験
 第3問
 Q1とQ2を組み合わせ、cars.csvを1行ずつ読み込み、その内容を
 構造体として配列に格納するプログラムを作成せよ.
 配列に格納後、for文とdispTrial関数を用いて配列に格納された
 構造体の内容を表示せよ.
 +------------------------------------------------*/

//定義===================================================================================
//インクルード------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

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

//関数===================================================================================
int main(int argc, const char * argv[]) {
    FILE *fp;
    char line[MAX_LEN];
    int input_speed, input_dist;
    int n, i;
    Trial *trial;
    Trial *temp;
    
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
    
    /*---dispTrialを用いて配列の内容を表示---*/
    for (i = 0;i < n;i++) {
        dispTrial(trial[i]);
    }
    
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
//機能:構造体Trialのデータ1つの内容を表示する
//引数 Trial trial:表示する対象のデータ
//返り値:なし
//---------------------------------------------------------------------
void dispTrial(Trial trial) {
    printf("Speed: %d, Distance: %d\n", getSpeed(trial), getDistance(trial));
    return;
}
