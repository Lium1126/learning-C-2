//
//  main.c
//  exercise1
//
//  Created by k19061kk on 2019/12/04.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------------------+
 プログラミング及び演習II
 第10回 課題
 地震データh2011_eq.csvを構造体の配列として読み込み、
 緯度でソートした結果をファイルに出力せよ
 +--------------------------------------------*/

//インクルード================================================================
#include <stdio.h>
#include <stdlib.h>

//定義======================================================================
//マクロ--------------------------------------------------------
#define MAX_LEN 256

//構造体--------------------------------------------------------
typedef struct {
    int year, month, date;       // 発生年(西暦),月,日
    double latitude, longitude;  // 発生場所の緯度,経度
    char eqScale;                // 震度
} EarthQuake;

//関数プロトタイプ宣言---------------------------------------------
//基本操作関数(アクセサ)
int getYear(EarthQuake eq);                                  // 発生年を取得する
void setYear(EarthQuake *eq, int year);                      // 発生年を設定する
int getMonth(EarthQuake eq);                                 // 発生月を取得する
void setMonth(EarthQuake *eq, int month);                    // 発生月を設定する
int getDate(EarthQuake eq);                                  // 発生日を取得する
void setDate(EarthQuake *eq, int date);                      // 発生日を設定する
double getLatitude(EarthQuake eq);                           // 発生場所の緯度を取得する
void setLatitude(EarthQuake *eq, double latitude);           // 発生場所の緯度を設定する
double getLongitude(EarthQuake eq);                          // 発生場所の経度を取得する
void setLongitude(EarthQuake *eq, double longitude);         // 発生場所の経度を設定する
char getEqScale(EarthQuake eq);                              // 震度を取得する
void setEqScale(EarthQuake *eq, char eqScale);               // 震度を設定する
void setEqParameter(EarthQuake *eq, int year, int month, int date, double latitude, double longitude, char eqScale);  // 地震情報を設定する

//その他の関数
void sortEqByLatitude(EarthQuake *eq, int num);              // 地震情報を発生場所の緯度をキーにソートする
void sortTwoEqByLatitude(EarthQuake *eq1, EarthQuake *eq2);  // 2つの地震情報を発生場所の緯度をキーにソートする
void swapEqByLatitude(EarthQuake *eq1, EarthQuake *eq2);     // 2つの地震情報を入れ替える

//関数群=====================================================================
//main関数------------------------------------------------------
int main(int argc, const char * argv[]) {
    EarthQuake *eq;                                     // 地震情報を格納する構造体の配列(動的に確保)
    EarthQuake *temp;                                   // realloc()で使用する作業用変数
    FILE *in_fp, *out_fp;                               // ファイルポインタ
    char line[MAX_LEN];                                 // ファイル入力時のバッファ配列
    int num, i;                                         // カウンタ変数
    int year, month, date;       //------+
    double latitude, longitude;  //------+-----------------入力用変数
    char eqScale;                //------+
    
    /*---入力ファイルを開く---*/
    in_fp = fopen("h2011_eq.csv", "r");
    if(in_fp == NULL) {
        fprintf(stderr, "Cannot open the input file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---eqを動的に確保---*/
    if((eq = (EarthQuake*)malloc(sizeof(EarthQuake))) == NULL) {
        fprintf(stderr, "No enough memory.\n");
        fclose(in_fp);
        exit(EXIT_FAILURE);
    }
    
    /*---eqを適宜再確保しながらファイルから入力---*/
    num = 0;
    while(fgets(line, MAX_LEN, in_fp) != NULL) {
        // 動的メモリ領域を拡張
        temp = realloc(eq, sizeof(EarthQuake) * (num + 1));
        if(temp == NULL) {
            fprintf(stderr, "No enough memory.\n");
            fclose(in_fp);
            free(eq);
            exit(EXIT_FAILURE);
        } else {
            eq = temp;
        }
        
        // ファイルから1行分を構造体に格納
        sscanf(line, "%d,%d,%d,%lf,%lf,%c", &year, &month, &date, &latitude, &longitude, &eqScale);
        setEqParameter(&eq[num], year, month, date, latitude, longitude, eqScale);
        
        num++;
    }
    
    /*---入力ファイルを閉じる---*/
    fclose(in_fp);
    
    /*---配列eqをソートする---*/
    sortEqByLatitude(eq, num);
    
    /*---出力ファイルを開く---*/
    out_fp = fopen("output.txt", "w");
    if(out_fp == NULL) {
        fprintf(stderr, "Cannot open the output file.\n");
        free(eq);
        exit(EXIT_FAILURE);
    }
    
    /*---ソート後の配列を出力ファイルに書き出す---*/
    for(i = 0;i < num;i++) {
        fprintf(out_fp, "発生日:%d/%2d/%2d 発生場所(%f, %f) 震度:%c\n", getYear(eq[i]), getMonth(eq[i]), getDate(eq[i]), getLatitude(eq[i]), getLongitude(eq[i]), getEqScale(eq[i]));
    }
    
    /*---出力ファイルを閉じる---*/
    fclose(out_fp);
    
    /*---メモリを解放---*/
    free(eq);
    
    return 0;
}

//その他の関数---------------------------------------------------
//基本操作関数(アクセサ)
//------------------------------------------------------
//機能:eqの発生年(西暦)を取得する
//引数 EarthQuake eq:発生年を取得する対象の地震情報
//返り値:eqの発生年
//------------------------------------------------------
int getYear(EarthQuake eq) {
    return(eq.year);
}

//------------------------------------------------------
//機能:eqの発生年(西暦)を設定する
//引数 EarthQuake *eq:発生年を設定する対象の地震情報へのポインタ
//    int year      :eqに設定する発生年(西暦)
//返り値:なし
//------------------------------------------------------
void setYear(EarthQuake *eq, int year) {
    eq -> year = year;
    return;
}

//------------------------------------------------------
//機能:eqの発生月を取得する
//引数 EarthQuake eq:発生月を取得する対象の地震情報
//返り値:eqの発生月
//------------------------------------------------------
int getMonth(EarthQuake eq) {
    return(eq.month);
}

//------------------------------------------------------
//機能:eqの発生月を設定する
//引数 EarthQuake *eq:発生月を設定する対象の地震情報へのポインタ
//    int month     :eqに設定する発生月
//返り値:なし
//------------------------------------------------------
void setMonth(EarthQuake *eq, int month) {
    eq -> month = month;
    return;
}

//------------------------------------------------------
//機能:eqの発生日を取得する
//引数 EarthQuake eq:発生日を取得する対象の地震情報
//返り値:eqの発生日
//------------------------------------------------------
int getDate(EarthQuake eq) {
    return(eq.date);
}

//------------------------------------------------------
//機能:eqの発生日を設定する
//引数 EarthQuake *eq:発生日を設定する対象の地震情報へのポインタ
//    int date      :eqに設定する発生日
//返り値:なし
//------------------------------------------------------
void setDate(EarthQuake *eq, int date) {
    eq -> date = date;
    return;
}

//------------------------------------------------------
//機能:eqの発生場所の緯度を取得する
//引数 EarthQuake eq:緯度を取得する対象の地震情報
//返り値:eqの発生場所の緯度
//------------------------------------------------------
double getLatitude(EarthQuake eq) {
    return(eq.latitude);
}

//------------------------------------------------------
//機能:eqの発生場所の緯度を設定する
//引数 EarthQuake *eq:緯度を設定する対象の地震情報へのポインタ
//    int latitude  :eqに設定する緯度
//返り値:なし
//------------------------------------------------------
void setLatitude(EarthQuake *eq, double latitude) {
    eq -> latitude = latitude;
    return;
}

//------------------------------------------------------
//機能:eqの発生場所の経度を取得する
//引数 EarthQuake eq:経度を取得する対象の地震情報
//返り値:eqの発生場所の経度
//------------------------------------------------------
double getLongitude(EarthQuake eq) {
    return(eq.longitude);
}

//------------------------------------------------------
//機能:eqの発生場所の経度を設定する
//引数 EarthQuake *eq:経度を設定する対象の地震情報へのポインタ
//    int longitude :eqに設定する経度
//返り値:なし
//------------------------------------------------------
void setLongitude(EarthQuake *eq, double longitude) {
    eq -> longitude = longitude;
    return;
}

//------------------------------------------------------
//機能:eqの震度を取得する
//引数 EarthQuake eq:震度を取得する対象の地震情報
//返り値:eqの震度
//------------------------------------------------------
char getEqScale(EarthQuake eq) {
    return(eq.eqScale);
}

//------------------------------------------------------
//機能:eqの震度を設定する
//引数 EarthQuake *eq:震度を設定する対象の地震情報へのポインタ
//    char eqScale  :eqに設定する震度
//返り値:なし
//------------------------------------------------------
void setEqScale(EarthQuake *eq, char eqScale) {
    eq -> eqScale = eqScale;
    return;
}

//------------------------------------------------------
//機能:eqの各パラメータを設定する
//引数 EarthQuake *eq:パラメータを設定する対象の地震情報のポインタ
//    その他         :各パラメータに設定する値
//返り値:なし
//------------------------------------------------------
void setEqParameter(EarthQuake *eq, int year, int month, int date, double latitude, double longitude, char eqScale) {
    setYear(eq, year);
    setMonth(eq, month);
    setDate(eq, date);
    setLatitude(eq, latitude);
    setLongitude(eq, longitude);
    setEqScale(eq, eqScale);
    return;
}

//その他の関数
//------------------------------------------------------
//機能:num個の地震情報を、発生場所の緯度でソートする
//引数 EarthQuake *eq:ソートする対象の地震情報の配列
//    int num       :ソートする配列の要素数
//返り値:なし
//------------------------------------------------------
void sortEqByLatitude(EarthQuake *eq, int num) {
    int i, j;  // カウンタ変数
    
    for(i = 0;i < num - 1;i++) {
        for(j = num - 1;j > i;j--) {
            sortTwoEqByLatitude(&eq[j - 1], &eq[j]);
        }
    }
    
    return;
}

//------------------------------------------------------
//機能:2個の地震情報を、発生場所の緯度,経度,震度の順でキーにして
//    ソートする
//引数 EarthQuake eq1:---+
//    EarthQuake eq2:---+--ソートする対象の地震情報
//返り値:なし
//------------------------------------------------------
void sortTwoEqByLatitude(EarthQuake *eq1, EarthQuake *eq2) {
    if(getLatitude(*eq1) > getLatitude(*eq2)) {                 // 緯度が異なる場合
        swapEqByLatitude(eq1, eq2);
    } else if(getLatitude(*eq1) == getLatitude(*eq2)) {         // 緯度が同じで
        if(getLongitude(*eq1) > getLongitude(*eq2)) {           // 経度が異なる場合
            swapEqByLatitude(eq1, eq2);
        } else if(getLongitude(*eq1) == getLongitude(*eq2)) {   // 経度も同じで
            if(getEqScale(*eq1) > getEqScale(*eq2)) {           // 震度が異なる場合
                swapEqByLatitude(eq1, eq2);
            }
        }
    }
    return;
}

//------------------------------------------------------
//機能:2個の地震情報を入れ替える
//引数 EarthQuake eq1:---+
//    EarthQuake eq2:---+--入れ替える対象の地震情報
//返り値:なし
//------------------------------------------------------
void swapEqByLatitude(EarthQuake *eq1, EarthQuake *eq2) {
    EarthQuake temp;  // 作業用変数
    
    temp = *eq1;
    *eq1 = *eq2;
    *eq2 = temp;
    
    return;
}
