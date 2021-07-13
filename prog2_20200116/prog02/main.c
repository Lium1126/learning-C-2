//
//  main.c
//  prog02
//
//  Created by k19061kk on 2020/01/15.
//  Copyright © 2020 AIT. All rights reserved.
//

/*-----------------------------------------------+
 プログラミング及び演習II 第14回
 問題2
 3人分の要素を初期化し、それぞれリストの先頭に追加していく.
 リストへの追加が完了したらすべて表示せよ.
 +-----------------------------------------------*/

//定義==================================================================================
//インクルード-------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

//マクロ-----------------------------------------------------------------------
#define NAME_LEN 256

//データ構造--------------------------------------------------------------------
typedef struct mmember {
    char name[NAME_LEN];   // 名前
    double height;         // 身長
    double weight;         // 体重
    struct mmember *next;  // 次のセルへのポインタ
} MList;

typedef MList MCell;      // 意味合いによって使い分け

//関数プロトタイプ宣言=====================================================================
//基本操作関数-------------------------------------------------------------------
MList *makeEmptyList(void);                    // 空リストを作る
void initList(MList **head);                   // リストを空リストで初期化する
int isEmptyList(MList *head);                  // リストが空リストか判定する
char *getName(MCell *person);                  // personから名前データを取得する
void setName(MCell *person, char *name);       // personに名前データを設定する
double getHeight(MCell person);                // personから身長データを取得する
void setHeight(MCell *person, double height);  // personに身長データを設定する
double getWeight(MCell person);                // personから体重データを取得する
void setWeight(MCell *person, double weight);  // personに体重データを設定する
MCell *getNextMCell(MCell cell);               // cellから次のセルへのポインタを取得する
void setNextMCell(MCell *cell, MCell *next);   // cellの次のセルをnextに設定する
void setParameter(MCell *cell, char *name, double height, double weight, MCell *next);  // 各パラメータを設定する

//関数群=================================================================================
//main関数---------------------------------------------------------------------
int main(int argc, const char * argv[]) {
    MList *head;       // 名簿管理のためのリスト
    MCell *current;    // 現在見ているセルへのポインタ
    MCell p1, p2, p3;  // リストへ追加する3人分の要素
    
    /*---リストを初期化する---*/
    initList(&head);
    
    /*---3人分の要素を初期化し、リストの先頭に追加する---*/
    // 1人目
    setParameter(&p1, "satou", 172.7, 52.3, head);
    head = &p1;
    // 2人目
    setParameter(&p2, "suzuki", 169.8, 47.9, head);
    head = &p2;
    // 3人目
    setParameter(&p3, "tanaka", 165.3, 63.7, head);
    head = &p3;
    
    /*---表示する---*/
    current = head;
    if (isEmptyList(current)) {
        printf("Empty List\n");
    } else {
        while (!isEmptyList(current)) {
            // データを表示する
            printf("[%s,%.1f,%.1f]", getName(current), getHeight(*current), getWeight(*current));
            // currentが末尾のセルでなかったら" -> "を表示
            if (!isEmptyList(getNextMCell(*current))) {
                printf(" -> ");
            }
            // currentが末尾のセルだったら改行を表示
            else {
                printf("\n");
            }
            current = getNextMCell(*current);
        }
    }
    
    return 0;
}

//基本操作関数-------------------------------------------------------------------
//------------------------------------------------------------------
//機能:空リストを作る
//引数:なし
//返り値:空リストへのポインタを返す
//------------------------------------------------------------------
MList *makeEmptyList(void) {
    return((MList*)NULL);
}

//------------------------------------------------------------------
//機能:リストを空リストで初期化する
//引数 MList **head:初期化するリストを指すポインタへのポインタ
//返り値:なし
//------------------------------------------------------------------
void initList(MList **head) {
    *head = makeEmptyList();
    return;
}

//------------------------------------------------------------------
//機能:リストが空リストか判定する
//引数 MList *head:空リストか判定するリストの先頭要素へのポインタ
//返り値:headが指すリストが空リストなら1、空リストでないなら0を返す
//------------------------------------------------------------------
int isEmptyList(MList *head) {
    if (head == makeEmptyList()) {
        return(1);
    } else {
        return(0);
    }
}

//------------------------------------------------------------------
//機能:リストの要素から名前データを取得する
//引数 MCell person:名前データを取得する対象のリスト要素
//返り値:personの名前データ
//------------------------------------------------------------------
char *getName(MCell *person) {
    return(person -> name);
}

//------------------------------------------------------------------
//機能:リストの要素に名前データを設定する
//引数 MCell *person:名前データを設定する対象のリスト要素を指すポインタ
//    char *name   :設定する名前を表す文字列
//返り値:なし
//------------------------------------------------------------------
void setName(MCell *person, char *name) {
    strcpy(person -> name, name);
    return;
}

//------------------------------------------------------------------
//機能:リストの要素から身長データを取得する
//引数 MCell person:身長データを取得する対象のリスト要素
//返り値:personの身長データ
//------------------------------------------------------------------
double getHeight(MCell person) {
    return(person.height);
}

//------------------------------------------------------------------
//機能:リストの要素に身長データを設定する
//引数 MCell *person:身長データを設定する対象のリスト要素を指すポインタ
//    double height:設定する身長データ
//返り値:なし
//------------------------------------------------------------------
void setHeight(MCell *person, double height) {
    person -> height = height;
    return;
}

//------------------------------------------------------------------
//機能:リストの要素から体重データを取得する
//引数 MCell *person:体重データを取得する対象のリスト要素
//返り値:personの体重データ
//------------------------------------------------------------------
double getWeight(MCell person) {
    return(person.weight);
}

//------------------------------------------------------------------
//機能:リストの要素に体重データを設定する
//引数 MCell *person:体重データを設定する対象のリスト要素を指すポインタ
//    double weight:設定する体重データ
//返り値:なし
//------------------------------------------------------------------
void setWeight(MCell *person, double weight) {
    person -> weight = weight;
    return;
}

//------------------------------------------------------------------
//機能:リストの要素から次の要素を取得する
//引数 MCell cell:次の要素を取得する対象のリスト要素
//返り値:cellの次の要素へのポインタ
//------------------------------------------------------------------
MCell *getNextMCell(MCell cell) {
    return(cell.next);
}

//------------------------------------------------------------------
//機能:リストの要素に次の要素を設定する
//引数 MCell *cell:次の要素を設定する対象のリスト要素を指すポインタ
//    MCell *next:設定する次の要素を指すポインタ
//返り値:なし
//------------------------------------------------------------------
void setNextMCell(MCell *cell, MCell *next) {
    cell -> next = next;
    return;
}

//------------------------------------------------------------------
//機能:リストの要素に各パラメータを設定する
//引数 MCell *cell  :各パラメータを設定する対象のリスト要素を指すポインタ
//    char *name   :設定する名前データを表す文字列
//    double height:設定する身長データ
//    double weight:設定する体重データ
//    MCell *next  :設定する次の要素を指すポインタ
//返り値:なし
//------------------------------------------------------------------
void setParameter(MCell *cell, char *name, double height, double weight, MCell *next) {
    setName(cell, name);
    setHeight(cell, height);
    setWeight(cell, weight);
    setNextMCell(cell, next);
    return;
}
