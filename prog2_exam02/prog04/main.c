//
//  main.c
//  prog04
//
//  Created by k19061kk on 2020/01/23.
//  Copyright © 2020 AIT. All rights reserved.
//

/*------------------------------------------------+
 プログラミング及び演習II 期末試験
 第4問
 以下を発見して表示せよ.
    ・speedの最小値
    ・speedの最大値
    ・distanceの最小値
    ・distanceの最大値
 +------------------------------------------------*/

//定義===================================================================================
//インクルード------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

//関数===================================================================================
int main(int argc, const char * argv[]) {
    FILE *fp;
    char line[MAX_LEN];
    int input_speed, input_dist;
    int n, i;
    Trial *trial;
    Trial *temp;
    int min_speed = INT_MAX, max_speed = 0;
    int min_dist = INT_MAX, max_dist = 0;
    
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
    
    /*---speed,distanceの最小値・最大値を求める---*/
    for (i = 0;i < n;i++) {
        if (min_speed > getSpeed(trial[i])) {
            min_speed = getSpeed(trial[i]);
        }
        if (min_dist > getDistance(trial[i])) {
            min_dist = getDistance(trial[i]);
        }
        if (max_speed < getSpeed(trial[i])) {
            max_speed = getSpeed(trial[i]);
        }
        if (max_dist < getDistance(trial[i])) {
            max_dist = getDistance(trial[i]);
        }
    }
    
    /*---speed,distanceの最小値・最大値を表示---*/
    printf("speedの最小値: %d\n", min_speed);
    printf("speedの最大値: %d\n", max_speed);
    printf("distanceの最小値: %d\n", min_dist);
    printf("distanceの最大値: %d\n", max_dist);
    
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
