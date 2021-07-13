//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/11/28.
//  Copyright © 2019 AIT. All rights reserved.
//

/*---------------------------------+
 プログラミング及び演習II 第9回
 追加課題
 h2011_eq.csvを読み込んで構造体に格納し、
 その内容を標準出力に表示せよ。
 +---------------------------------*/

//インクルード===========================================================
#include <stdio.h>
#include <stdlib.h>

//定義=================================================================
//マクロ-----------------------------------------------------
#define LINE_LEN 50

//構造体-----------------------------------------------------
typedef struct earthquake {
    int year, month, date;       // 発生年月日
    double latitude, longitude;  // 緯度, 経度
    int eqScale;                 // 震度
} EarthQuake;

//関数プロトタイプ宣言-----------------------------------------
int getYear(EarthQuake eq);                            // 年を取得する
void setYear(EarthQuake *eq, int year);                // 年を設定する
int getMonth(EarthQuake eq);                           // 月を取得する
void setMonth(EarthQuake *eq, int month);              // 月を設定する
int getDate(EarthQuake eq);                            // 日付を取得する
void setDate(EarthQuake *eq, int date);                // 日付を設定する
double getLatitude(EarthQuake eq);                     // 緯度を取得する
void setLatitude(EarthQuake *eq, double latitude);     // 緯度を設定する
double getLongitude(EarthQuake eq);                    // 経度を取得する
void setLongitude(EarthQuake *eq, double longitude);   // 経度を設定する
int getEqScale(EarthQuake eq);                         // 震度を取得する
void setEqScale(EarthQuake *eq, int eqScale);          // 震度を設定する
void setParameter(EarthQuake *eq, int year, int month, int date, double latitude, double longitude, int eqScale);  // 各パラメータを設定する
void printEq(EarthQuake *eq, int num);                 // 地震の諸情報を表示する

//関数群===============================================================
//main関数--------------------------------------------------
int main(int argc, const char * argv[]) {
    FILE *fp;                    // ファイルポインタ
    EarthQuake *eq;              // 地震の諸情報を格納する構造体配列(動的に確保)
    EarthQuake *temp;            // reallocで使用する作業用変数
    int cnt;                     // カウンタ変数
    char line[LINE_LEN];         // fgetsの入力を一行分受け付ける文字配列
    int year, month, date;       //---+
    double latitude, longitude;  //---+--入力用変数
    int eqScale;                 //---+
    
    /*---メモリ確保---*/
    if((eq = (EarthQuake*)malloc(sizeof(EarthQuake))) == NULL){
        fprintf(stderr, "No enough memory.\n");
        exit(EXIT_FAILURE);
    }

    /*---ファイルを開く---*/
    fp = fopen("h2011_eq.csv", "r");
    if(fp == NULL){
        fprintf(stderr, "Can not open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---ファイルの内容を格納---*/
    cnt = 0;
    while(fgets(line, LINE_LEN, fp) != NULL){
        temp = realloc(eq, sizeof(EarthQuake) * (cnt + 1));
        if(temp == NULL){
            fprintf(stderr, "No enough memory.\n");
            free(eq);
            exit(EXIT_FAILURE);
        }else{
            eq = temp;
        }
        
        sscanf(line, "%d,%d,%d,%lf,%lf,%d", &year, &month, &date, &latitude, &longitude, &eqScale);
        setParameter(&eq[cnt], year, month, date, latitude, longitude, eqScale);
        cnt++;
    }
    
    /*---eqの内容を表示---*/
    printEq(eq, cnt);
    
    /*--ファイルを閉じる---*/
    fclose(fp);
    
    /*---メモリを解放---*/
    free(eq);
    
    return 0;
}

//基本操作関数----------------------------------------------
//----------------------------------------------------
//機能:eqの発生年を取得する
//引数 EarthQuake eq: 発生年を取得する対象
//返り値:eqの発生年(西暦)
//----------------------------------------------------
int getYear(EarthQuake eq) {
    return(eq.year);
}

//----------------------------------------------------
//機能:eqの発生年を設定する
//引数 EarthQuake *eq: 発生年を設定する対象へのポインタ
//    int year      : 設定する年(西暦)
//返り値:なし
//----------------------------------------------------
void setYear(EarthQuake *eq, int year) {
    eq -> year = year;
    return;
}

//----------------------------------------------------
//機能:eqの発生月を取得する
//引数 EarthQuake eq: 発生月を取得する対象
//返り値:eqの発生月
//----------------------------------------------------
int getMonth(EarthQuake eq) {
    return(eq.month);
}

//----------------------------------------------------
//機能:eqの発生月を設定する
//引数 EarthQuake *eq: 発生月を設定する対象へのポインタ
//    int month     : 設定する月
//返り値:なし
//----------------------------------------------------
void setMonth(EarthQuake *eq, int month) {
    eq -> month = month;
    return;
}

//----------------------------------------------------
//機能:eqの発生日を取得する
//引数 EarthQuake eq: 発生日を取得する対象
//返り値:eqの発生日
//----------------------------------------------------
int getDate(EarthQuake eq) {
    return(eq.date);
}

//----------------------------------------------------
//機能:eqの発生日を設定する
//引数 EarthQuake *eq: 発生日を設定する対象へのポインタ
//    int date      : 設定する日付
//返り値:なし
//----------------------------------------------------
void setDate(EarthQuake *eq, int date) {
    eq -> date = date;
    return;
}

//----------------------------------------------------
//機能:eqの発生した緯度を取得する
//引数 EarthQuake eq: 発生した緯度を取得する対象
//返り値:eqの発生した緯度
//----------------------------------------------------
double getLatitude(EarthQuake eq) {
    return(eq.latitude);
}

//----------------------------------------------------
//機能:eqの発生した緯度を設定する
//引数 EarthQuake *eq : 発生した緯度を設定する対象へのポインタ
//    double latitude: 設定する緯度
//返り値:なし
//----------------------------------------------------
void setLatitude(EarthQuake *eq, double latitude) {
    eq -> latitude = latitude;
    return;
}

//----------------------------------------------------
//機能:eqの発生した経度を取得する
//引数 EarthQuake eq: 発生した経度を取得する対象
//返り値:eqの発生した経度
//----------------------------------------------------
double getLongitude(EarthQuake eq) {
    return(eq.longitude);
}

//----------------------------------------------------
//機能:eqの発生した経度を設定する
//引数 EarthQuake *eq  : 発生した経度を設定する対象へのポインタ
//    double longitude: 設定する経度
//返り値:なし
//----------------------------------------------------
void setLongitude(EarthQuake *eq, double longitude) {
    eq -> longitude = longitude;
    return;
}

//----------------------------------------------------
//機能:eqの震度を取得する
//引数 EarthQuake eq: 震度を取得する対象
//返り値:eqの発生した震度
//----------------------------------------------------
int getEqScale(EarthQuake eq) {
    return(eq.eqScale);
}

//----------------------------------------------------
//機能:eqの震度を設定する
//引数 EarthQuake *eq: 震度を設定する対象へのポインタ
//    int eqScale   : 設定する震度
//返り値:なし
//----------------------------------------------------
void setEqScale(EarthQuake *eq, int eqScale) {
    eq -> eqScale = eqScale;
    return;
}

//----------------------------------------------------
//機能:eqの各パラメータを設定する
//引数 EarthQuake *eq  : パラメータを設定する対象へのポインタ
//    int year        : 設定する発生年(西暦)
//    int month       : 設定する発生月
//    int date        : 設定する発生日
//    double latitude : 設定する緯度
//    double longitude: 設定する経度
//    int eqScale     : 設定する震度
//返り値:なし
//----------------------------------------------------
void setParameter(EarthQuake *eq, int year, int month, int date, double latitude, double longitude, int eqScale) {
    setYear(eq, year);
    setMonth(eq, month);
    setDate(eq, date);
    setLatitude(eq, latitude);
    setLongitude(eq, longitude);
    setEqScale(eq, eqScale);
    return;
}

//----------------------------------------------------
//機能:eqの内容を標準出力に表示する
//引数 EarthQuake *eq: 表示する内容が格納された配列
//    int num       : 表示するデータの個数
//返り値:なし
//----------------------------------------------------
void printEq(EarthQuake *eq, int num) {
    int i;  // カウンタ変数
    
    for(i = 0;i < num;i++){
        printf("%d/%d/%d (%f,%f) %d\n", getYear(eq[i]), getMonth(eq[i]), getDate(eq[i]), getLatitude(eq[i]), getLongitude(eq[i]), getEqScale(eq[i]));
    }
    
    return;
}
