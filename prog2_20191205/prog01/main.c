//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/12/04.
//  Copyright © 2019 AIT. All rights reserved.
//

/*------------------------------------------+
 プログラミング及び演習II
 第10回 問題1
 場所を構造体で定義する
    ・緯度  ・経度  ・住所
 場所を2つ用意し、愛工大と愛工大名電の情報で初期化する
 各場所の情報を表示する
 +------------------------------------------*/

//インクルード================================================================
#include <stdio.h>
#include <string.h>

//定義======================================================================
//マクロ--------------------------------------------------------
#define MAX_LEN 256

//構造体--------------------------------------------------------
typedef struct {
    double latitude;        // 緯度
    double longitude;       // 経度
    char address[MAX_LEN];  // 住所
} Place;

//関数プロトタイプ宣言---------------------------------------------
//基本操作関数(アクセサ)
double getLatitude(Place place);                                                         // 緯度を取得する
void setLatitude(Place *place, double latitude);                                         // 緯度を設定する
double getLongitude(Place place);                                                        // 経度を取得する
void setLongitude(Place *place, double longitude);                                       // 経度を設定する
char *getAddress(Place *place);                                                          // 住所を取得する
void setAddress(Place *place, char *address);                                            // 住所を設定する
void setPlaceParameter(Place *place, double latitude, double longitude, char *address);  // 各パラメータを設定する

//操作関数
void printPlace(Place place);                       // 場所の情報を表示する

//関数群=====================================================================
//main()関数
int main(int argc, const char * argv[]) {
    Place AIT;   // 愛工大(Aichi Institute of Technology)
    Place AMHS;  // 愛工大名電高校(Aikodai Meiden High Shcool)
    
    /*---愛工大と愛工大名電の情報で初期化---*/
    setPlaceParameter(&AIT, 35.1834166, 137.1108532, "1247 Yakusa, Yakusacho, Toyota City, Aichi Prefecture");
    setPlaceParameter(&AMHS, 35.1783684, 136.9467452, "3-12 Wakamizu, Chikusa-ku, Nagoya, Aichi Prefecture");
    
    /*---格納した情報を表示---*/
    printf("施設:(緯度, 経度) 住所\n");
    printf("愛工大:");
    printPlace(AIT);
    printf("愛工大名電:");
    printPlace(AMHS);
    
    return 0;
}

//基本操作関数(アクセサ)
//------------------------------------------------------
//機能:placeの緯度を取得する
//引数 Place place:緯度を取得する対象の構造体
//返り値:placeの緯度
//------------------------------------------------------
double getLatitude(Place place) {
    return(place.latitude);
}

//------------------------------------------------------
//機能:placeの緯度を設定する
//引数 Place *place   :緯度を設定する対象の構造体へのポインタ
//    double latitude:設定する緯度の値
//返り値:なし
//------------------------------------------------------
void setLatitude(Place *place, double latitude) {
    place -> latitude = latitude;
    return;
}

//------------------------------------------------------
//機能:placeの経度を取得する
//引数 Place place:経度を取得する対象の構造体
//返り値:placeの経度
//------------------------------------------------------
double getLongitude(Place place) {
    return(place.longitude);
}

//------------------------------------------------------
//機能:placeの経度を設定する
//引数 Place *place    :経度を設定する対象の構造体へのポインタ
//    double longitude:設定する経度の値
//返り値:なし
//------------------------------------------------------
void setLongitude(Place *place, double longitude) {
    place -> longitude = longitude;
    return;
}

//------------------------------------------------------
//機能:placeの住所を取得する
//引数 Place *place:住所を取得する対象の構造体へのポインタ
//返り値:placeの住所
//------------------------------------------------------
char *getAddress(Place *place) {
    return(place -> address);
}

//------------------------------------------------------
//機能:placeの住所を設定する
//引数 Place *place:住所を設定する対象の構造体へのポインタ
//    char *address:住所として設定する文字列
//返り値:なし
//------------------------------------------------------
void setAddress(Place *place, char *address) {
    strcpy(place -> address, address);
    return;
}

//------------------------------------------------------
//機能:placeの各パラメータを設定する
//引数 Place *place    :パラメータを設定する対象の構造体へのポインタ
//    double latitude :設定する緯度の値
//    double longitude:設定する軽度の値
//    char *address   :住所として設定する文字列
//返り値:なし
//------------------------------------------------------
void setPlaceParameter(Place *place, double latitude, double longitude, char *address) {
    setLatitude(place, latitude);
    setLongitude(place, longitude);
    setAddress(place, address);
    return;
}

//操作関数
//------------------------------------------------------
//機能:placeの情報を標準出力に表示する
//引数 Place place:場所の情報を表示する対象の構造体
//返り値:なし
//------------------------------------------------------
void printPlace(Place place) {
    printf("(%f, %f) %s\n", getLatitude(place), getLongitude(place), getAddress(&place));
    return;
}
