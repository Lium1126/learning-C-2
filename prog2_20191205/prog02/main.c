//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/12/04.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------------+
 プログラミング及び演習II
 第10回 問題2
 地震という構造体を定義する
    ・年  ・月  ・日
    ・緯度 ・経度 ・震度
 h2011_eq.csvからどこか1行コピーする
    char line[] = "2011,3,11,...";
 この文字列の持つ情報で構造体を初期化し、その地震情報を
 表示する
 +-------------------------------------------*/

//インクルード================================================================
#include <stdio.h>

//定義======================================================================
//構造体--------------------------------------------------------
typedef struct {
    int year, month, date;       // 発生年(西暦),月,日
    double latitude, longitude;  // 発生場所の緯度,経度
    char eqScale;                // 震度
} EarthQuake;

//関数プロトタイプ宣言---------------------------------------------
//基本操作関数(アクセサ)
int getYear(EarthQuake eq);                            // 発生年を取得する
void setYear(EarthQuake *eq, int year);                // 発生年を設定する
int getMonth(EarthQuake eq);                           // 発生月を取得する
void setMonth(EarthQuake *eq, int month);              // 発生月を設定する
int getDate(EarthQuake eq);                            // 発生日を取得する
void setDate(EarthQuake *eq, int date);                // 発生日を設定する
double getLatitude(EarthQuake eq);                     // 発生場所の緯度を取得する
void setLatitude(EarthQuake *eq, double latitude);     // 発生場所の緯度を設定する
double getLongitude(EarthQuake eq);                    // 発生場所の経度を取得する
void setLongitude(EarthQuake *eq, double longitude);   // 発生場所の経度を設定する
char getEqScale(EarthQuake eq);                        // 震度を取得する
void setEqScale(EarthQuake *eq, char eqScale);         // 震度を設定する
void setEqParameter(EarthQuake *eq, int year, int month, int date, double latitude, double longitude, char eqScale);  // 地震情報を設定する

//操作関数
void printEarthQuake(EarthQuake eq);                   // 地震情報を表示する

//関数群=====================================================================
//main関数------------------------------------------------------
int main(int argc, const char * argv[]) {
    EarthQuake eq;                                      // 地震情報を格納する構造体
    char line[] = "2011,1,1,41.085667,141.266667,1";    // 問題に指定された文字列
    int year, month, date;       //------+
    double latitude, longitude;  //------+-----------------入力用変数
    char eqScale;                //------+
    
    /*---lineから地震情報を取得---*/
    sscanf(line, "%d,%d,%d,%lf,%lf,%c", &year, &month, &date, &latitude, &longitude, &eqScale);
    
    /*---入力された情報を構造体にセット---*/
    setEqParameter(&eq, year, month, date, latitude, longitude, eqScale);
    
    /*---セットした情報を表示---*/
    printEarthQuake(eq);
    
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

//操作関数
//------------------------------------------------------
//機能:地震情報eqを標準出力に表示する
//引数 EarthQuake eq:表示する対象の地震情報
//返り値:なし
//------------------------------------------------------
void printEarthQuake(EarthQuake eq) {
    printf("発生日:%d/%d/%d 発生場所:(%f, %f) 震度:%c\n", getYear(eq), getMonth(eq), getDate(eq), getLatitude(eq), getLongitude(eq), getEqScale(eq));
    return;
}
