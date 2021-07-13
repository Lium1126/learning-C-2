//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/12/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*------------------------------------------+
 プログラミング及び演習II 第13回
 問題2
 リストの各要素の内容を標準出力に表示する関数
 print_list(List *head)を実装せよ.
 +------------------------------------------*/

//定義=============================================================================
//インクルード---------------------------------------------------------------
#include <stdio.h>

//データ構造----------------------------------------------------------------
typedef struct cell {
    int num;            // データ部
    struct cell *next;  // ポインタ部
} Cell;

typedef Cell List;   // 意味合いによってリストとセルを使い分け

//関数プロトタイプ宣言================================================================
//基本操作関数--------------------------------------------------------------
int getCellData(Cell cell);                 // cellからデータを取得する
void setCellData(Cell *cell, int num);      // cellのデータ部にnumを設定する
Cell *getNextCell(Cell cell);               // cellから次のセルへのポインタを取得する
void setNextCell(Cell *cell, Cell *next);   // cellのポインタ部にnextを設定する
List *makeEmptyList(void);                  // 空リストを作る
int isEmptyList(List *list);                // listが空リストか判定する
void initList(List **head);                 // listがリストを初期化する

//操作関数-----------------------------------------------------------------
void print_list(List *head);                // リストの内容を表示する

//関数群===========================================================================
//main関数-----------------------------------------------------------------
int main(int argc, const char * argv[]) {
    List *head;          // 先頭のポインタを用意
    Cell l1, l2, l3;     // リストに追加するセル
    
    /*---リストを初期化する---*/
    initList(&head);
    
    /*---リストを準備する(授業資料p.30~33と同様の処理)---*/
    setCellData(&l1, 10);
    setNextCell(&l1, head);
    head = &l1;
    setCellData(&l2, 7);
    setNextCell(&l2, head);
    head = &l2;
    setCellData(&l3, 4);
    setNextCell(&l3, head);
    head = &l3;
    
    /*---リストの内容を表示する---*/
    print_list(head);
    
    return 0;
}

//基本操作関数----------------------------------------------------------------
//---------------------------------------------------------
//機能:cellからデータを取得する
//引数 Cell cell:データを取得する対象
//返り値:cellのデータ部の値
//---------------------------------------------------------
int getCellData(Cell cell) {
    return(cell.num);
}

//---------------------------------------------------------
//機能:cellのデータ部にnumを設定する
//引数 Cell *cell:データを設定する対象へのポインタ
//    int num   :cellのデータ部に設定する値
//返り値:なし
//---------------------------------------------------------
void setCellData(Cell *cell, int num) {
    cell -> num = num;
    return;
}

//---------------------------------------------------------
//機能:cellから次のセルへのポインタを取得する
//引数 Cell cell:次のセルへのポインタを取得する対象
//返り値:cellの次のセルへのポインタ
//---------------------------------------------------------
Cell *getNextCell(Cell cell) {
    return(cell.next);
}

//---------------------------------------------------------
//機能:cellのポインタ部にnextを設定する
//引数 Cell *cell:ポインタ部にnextを設定する対象へのポインタ
//    Cell *next:cellの次の要素へのポインタ
//返り値:なし
//---------------------------------------------------------
void setNextCell(Cell *cell, Cell *next) {
    cell -> next = next;
    return;
}

//---------------------------------------------------------
//機能:空リストを作る
//返り値:空リストへのポインタ
//---------------------------------------------------------
List *makeEmptyList(void) {
    return((List*)NULL);
}

//---------------------------------------------------------
//機能:listが空リストか判定する
//引数 List *list:空リストか判定するリストへのポインタ
//返り値:listが指す先が空リストなら1,空リストでないなら0を返す
//---------------------------------------------------------
int isEmptyList(List *list) {
    if (list == makeEmptyList()) {
        return(1);
    } else {
        return(0);
    }
}

//---------------------------------------------------------
//機能:リストを初期化する
//引数 List **head:初期化するリストを指すポインタへのポインタ
//返り値:なし
//---------------------------------------------------------
void initList(List **head) {
    *head = makeEmptyList();
    return;
}


//操作関数--------------------------------------------------------------------
//---------------------------------------------------------
//機能:リストの内容を表示する
//    空リストが渡された場合、"Empty list"と表示する
//引数 List *head:リストの先頭要素を指すポインタ
//返り値:なし
//---------------------------------------------------------
void print_list(List *head) {
    /*---空リストが渡された時は何もしない---*/
    if (isEmptyList(head)) {
        printf("Empty list\n");
        return;
    }
    
    /*---要素の内容を表示---*/
    printf("%d", getCellData(*head));
    
    /*---末尾のセルでないなら矢印を表示し、再帰呼び出し---*/
    if (!isEmptyList(getNextCell(*head))) {
        printf(" -> ");
        print_list(getNextCell(*head));
    }
    /*---末尾のセルであるなら改行を表示---*/
    else {
        printf("\n");
    }
    
    return;
}