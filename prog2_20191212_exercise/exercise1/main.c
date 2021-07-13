//
//  main.c
//  exercise1
//
//  Created by k19061kk on 2019/12/12.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------------+
 プログラミング及び演習II
 第11回 課題
 h2011_eq.csvを用い、緯度(latitude)2°刻みで、その緯度
 での地震の回数を出力するプログラムを作成せよ。
 +----------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 256

int main(int argc, const char * argv[]) {
    FILE *fp;            // ファイルポインタ
    char line[MAX_LEN];  // fgetsのバッファ変数
    int cnt[91] = {};    // 緯度ごとの地震回数
    int i, j;            // カウンタ変数
    int num;             // データ数
    int *data;           // 緯度のデータ(動的に確保、ファイルから入力)
    int *temp;           // reallocで使う作業用変数
    
    /*---ファイルを開く---*/
    fp = fopen("h2011_eq_latitude_sorted.txt", "r");
    if(fp == NULL) {
        fprintf(stderr, "Cannot open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---動的にメモリ領域を確保---*/
    if((data = (int*)malloc(sizeof(int))) == NULL) {
        fprintf(stderr, "No enough memory.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    
    /*---動的メモリを拡張しながらファイルから入力---*/
    num = 0;
    while((fgets(line, MAX_LEN, fp)) != NULL) {
        // 動的メモリを拡張
        temp = (int*)realloc(data, sizeof(int) * (num + 1));
        if(temp == NULL) {    /*メモリ拡張失敗*/
            fprintf(stderr, "No enough memory.\n");
            free(data);
            fclose(fp);
            exit(EXIT_FAILURE);
        } else {              /*メモリ拡張成功*/
            data = temp;
        }
        
        // データをファイルから入力
        sscanf(line, "%d", &data[num]);
        
        num++;
    }
    
    /*---入力ファイルを閉じる---*/
    fclose(fp);
    
    /*---緯度ごとの地震回数をカウントする---*/
    j = 0;
    for(i = 0;i <= 90;i++) {
        // 緯度がi°の回数をカウント
        while(data[j] == i && j <= num) {
            cnt[i]++;
            j++;
        }
    }
    
    /*---結果を出力---*/
    printf("緯度n°以上m°未満での地震回数を表示\n");
    for(i = 0;i < 90;i += 2) {
        printf("%2d°~%2d°: %d回\n", i, i + 2, cnt[i] + cnt[i + 1]);
    }
    printf("    90°: %d回\n", cnt[90]);
    
    /*---動的メモリ領域を解放---*/
    free(data);
    
    return 0;
}
