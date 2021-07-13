//
//  main.c
//  prog05
//
//  Created by k19061kk on 2019/12/04.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------------------+
 プログラミング及び演習II
 第10回 問題5
 地震データh2011_eq.csvを構造体の配列として読み込む
 3月11日以降に発生した震度4以上の地震回数を表示する
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
int getYear(EarthQuake eq);                                 // 発生年を取得する
void setYear(EarthQuake *eq, int year);                     // 発生年を設定する
int getMonth(EarthQuake eq);                                // 発生月を取得する
void setMonth(EarthQuake *eq, int month);                   // 発生月を設定する
int getDate(EarthQuake eq);                                 // 発生日を取得する
void setDate(EarthQuake *eq, int date);                     // 発生日を設定する
double getLatitude(EarthQuake eq);                          // 発生場所の緯度を取得する
void setLatitude(EarthQuake *eq, double latitude);          // 発生場所の緯度を設定する
double getLongitude(EarthQuake eq);                         // 発生場所の経度を取得する
void setLongitude(EarthQuake *eq, double longitude);        // 発生場所の経度を設定する
char getEqScale(EarthQuake eq);                             // 震度を取得する
void setEqScale(EarthQuake *eq, char eqScale);              // 震度を設定する
void setEqParameter(EarthQuake *eq, int year, int month, int date, double latitude, double longitude, char eqScale);  // 地震情報を設定する

//その他の関数
int cmpDate(int month1, int date1, int month2, int date2);  // 2つの日付を比較する
int cmpEqScale(char eqScale1, char eqScale2);               // 2つの震度を比較する

//関数群=====================================================================
//main関数------------------------------------------------------
int main(int argc, const char * argv[]) {
    EarthQuake *eq;                                     // 地震情報を格納する構造体の配列(動的に確保)
    EarthQuake *temp;                                   // realloc()で使用する作業用変数
    FILE *fp;                                           // ファイルポインタ
    char line[MAX_LEN];                                 // ファイル入力時のバッファ配列
    int num, i;                                         // カウンタ変数
    int cnt;                                            // 3月11日以降で震度4以上の地震の回数
    int year, month, date;       //------+
    double latitude, longitude;  //------+-----------------入力用変数
    char eqScale;                //------+
    
    /*---ファイルを開く---*/
    fp = fopen("h2011_eq.csv", "r");
    if(fp == NULL) {
        fprintf(stderr, "Cannot open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---eqを動的に確保---*/
    if((eq = (EarthQuake*)malloc(sizeof(EarthQuake))) == NULL) {
        fprintf(stderr, "No enough memory.\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    
    /*---eqを適宜再確保しながらファイルから入力---*/
    num = 0;
    while(fgets(line, MAX_LEN, fp) != NULL) {
        // 動的メモリ領域を拡張
        temp = realloc(eq, sizeof(EarthQuake) * (num + 1));
        if(temp == NULL) {
            fprintf(stderr, "No enough memory.\n");
            fclose(fp);
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
    
    /*---ファイルを閉じる---*/
    fclose(fp);
    
    /*---3月11日以降で震度4以上の地震の回数をカウント---*/
    cnt = 0;
    for(i = 0;i < num;i++) {
        if(cmpDate(getMonth(eq[i]), getDate(eq[i]), 3, 11) >= 0 && cmpEqScale(getEqScale(eq[i]), '4') >= 0) {
            cnt++;
        }
    }
    
    /*---カウントの結果を表示---*/
    printf("3月11日以降に発生した震度4以上の地震の回数: %d回\n", cnt);
    
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
//機能:2つの日付を比較する
//引数 int month1:---+
//    int date1 :---+--1つ目の日付
//    int month2:---+
//    int date2 :---+--2つ目の日付
//返り値:1つ目の日付が2つ目の日付以降なら正の値、
//      1つ目の日付が2つ目の日付以前なら負の値、
//      どちらも同じ日付なら0を返す
//------------------------------------------------------
int cmpDate(int month1, int date1, int month2, int date2) {
    if(month1 != month2) {         // 月が異なるならその差を返す
        return(month1 - month2);
    } else if(date1 != date2) {    // 月が一緒で日にちが異なるならその差を返す
        return(date1 - date2);
    } else {                       // 同じ日付の場合0を返す
        return(0);
    }
}

//------------------------------------------------------
//機能:2つの震度を比較する
//    震度の強さを示す文字は、弱い順に1,2,3,4,A,B,C,D,7である
//引数 char eqScale1:
//    char eqScale2:
//返り値:eqScale1がeqScale2より強い震度なら正の値、
//      eqScale1がeqScale2より弱い震度なら負の値、
//      どちらも同じ震度なら0を返す
//------------------------------------------------------
int cmpEqScale(char eqScale1, char eqScale2) {
    char base[9] = {'1', '2', '3', '4', 'A', 'B', 'C', 'D', '7'};  // 添字が大きいほど震度が大きい
    int p_eqScale1 = 0, p_eqScale2 = 0;                            // eqScale1,eqScale2の対応するbaseの添字
    int i;                                                         // カウンタ変数
    
    for(i = 0;i < sizeof(base);i++) {
        if(eqScale1 == base[i]) {
            p_eqScale1 = i;
        }
        if(eqScale2 == base[i]) {
            p_eqScale2 = i;
        }
    }
    
    return(p_eqScale1 - p_eqScale2);
}
