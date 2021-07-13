//
//  main.c
//  prog09
//
//  Created by k19061kk on 2020/01/15.
//  Copyright © 2020 AIT. All rights reserved.
//

/*-----------------------------------------------+
プログラミング及び演習II 第14回
問題9
ユーザからのコマンド入力を任意回数受け付けてその内容をリスト
構造に挿入せよ・削除せよ.
    <ユーザ入力の例>
        ・a kaji,170,80 -> ユーザを新たに挿入
        ・d kaji -> 氏名がkajiの要素を削除
        ・p -> 標準出力に現状を表示
        ・q -> 終了
格納したデータを標準出力に表示すること.
メモリの解放を忘れないこと.
+------------------------------------------------*/

//定義==================================================================================
//インクルード-------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//マクロ-----------------------------------------------------------------------
#define NAME_LEN 256
#define LINE_LEN 256

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
MCell *createMCell(char *name, double height, double weight);                          // 新しい要素を作る
MList *add_mmember_head(MList *head, char *name, double height, double weight);        // リストの先頭に要素を追加する
MList *delete_mmember_head(MList *head);                                               // リストの先頭要素を削除する
void setParameter(MCell *cell, char *name, double height, double weight, MCell *next); // 各パラメータを設定する

//操作関数---------------------------------------------------------------------
void print_mlist(MList *head);                                              // リストの内容を表示する
void free_mlist(MList *head);                                               // リストを解放する
MList *add_mmember(MList *head, char *name, double height, double weight);  // リストに氏名が辞書順になるよう要素を追加する
MList *delete_mmember(MList *head, char *delname);                          // リストから名前がdelnameの要素を削除する

//関数群=================================================================================
//main関数---------------------------------------------------------------------
int main(int argc, const char * argv[]) {
    MList *head;                        // 名簿管理のためのリスト
    char input_c;                       // コマンドの入力用変数
    char input_name[NAME_LEN];          // 名前データの入力用変数
    char input_line[LINE_LEN];          // 入力を一行分受け付けるバッファ配列
    double input_height, input_weight;  // 身長,体重データの入力用変数
    
    /*---リストを初期化する---*/
    initList(&head);
    
    /*---コマンド入力例を表示する---*/
    printf("---\n");
    printf("Command example\n");
    printf("a name,height,weight : Append data\n");
    printf("d name               : Delete data\n");
    printf("p                    : Diplay datas\n");
    printf("q                    : Quite program\n");
    printf("---\n");
    
    /*---コマンド入力を受け付け、リストを操作する---*/
    do {
        printf("command? ");
        fgets(input_line, LINE_LEN, stdin);
        sscanf(input_line, "%c %[^,^\n],%lf,%lf", &input_c, input_name, &input_height, &input_weight);
        
        switch (input_c) {
            case 'a':
                head = add_mmember(head, input_name, input_height, input_weight);
                break;
            case 'd':
                head = delete_mmember(head, input_name);
                break;
            case 'p':
                print_mlist(head);
                break;
            case 'q':
                printf("Finish\n");
                break;
            default:
                printf("No command\n");
                break;
        }
    } while(input_c != 'q');
    
    /*---リストの内容を表示する---*/
    printf("---\n");
    print_mlist(head);
    
    /*---リストを解放する---*/
    free_mlist(head);
    
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
//機能:新しい要素を作る
//    作成した新しい要素の次の要素は空リストである
//    新しい要素の作成に失敗した場合は空リストを返す
//引数 char *name   :新しい要素に設定する名前データ
//    double height:新しい要素に設定する身長データ
//    double weight:新しい要素に設定する体重データ
//返り値:メモリ確保した新しい要素を指すポインタ
//      メモリ確保に失敗した場合空リストを返す
//------------------------------------------------------------------
MCell *createMCell(char *name, double height, double weight) {
    MCell *new_cell;    // 新しいセルへのポインタ
    
    /*---新しいセルを確保する---*/
    new_cell = (MCell*)malloc(sizeof(MCell));
    
    /*---確保に失敗した場合は空リストを返す---*/
    if (new_cell == NULL) {
        return(makeEmptyList());
    }
    
    /*---新しいセルにパラメータを設定する---*/
    setParameter(new_cell, name, height, weight, makeEmptyList());
    
    /*---新しいセルへのポインタを返す---*/
    return(new_cell);
}

//------------------------------------------------------------------
//機能:リストの先頭に要素を追加する
//引数 MList *head  :要素を追加するリストを指すポインタ
//    char *name   :新たに追加する先頭要素の名前データ
//    double height:新たに追加する先頭要素の身長データ
//    double weight:新たに追加する先頭要素の体重データ
//返り値:処理後のリストの先頭要素へのポインタを返す
//------------------------------------------------------------------
MList *add_mmember_head(MList *head, char *name, double height, double weight) {
    MCell *new_cell = createMCell(name, height, weight);  // 新しく作成した要素へのポインタ
    
    /*---new_cellのメモリ確保に失敗している場合は何もしない---*/
    if (isEmptyList(new_cell)) {
        fprintf(stderr, "Memory allocation failed.\n");
        return(head);
    }
    
    /*---new_cellがheadを指すように設定する---*/
    setNextMCell(new_cell, head);
    
    /*---新しい先頭要素へのポインタ(new_cell)を返す---*/
    return(new_cell);
}

//------------------------------------------------------------------
//機能:リストの先頭要素を削除する
//引数 MList *head  :要素を削除するリストを指すポインタ
//返り値:処理後のリストの先頭要素へのポインタを返す
//------------------------------------------------------------------
MList *delete_mmember_head(MList *head) {
    /*---空リストが渡された場合何もしない---*/
    if (isEmptyList(head)) {
        return(makeEmptyList());
    }
    
    MList *next = getNextMCell(*head);  // 削除対象の次の要素へのポインタ
    
    /*---削除対象を解放---*/
    free(head);
    
    /*---処理後の先頭要素へのポインタを返す*/
    return(next);
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

//操作関数---------------------------------------------------------------------
//------------------------------------------------------------------
//機能:リストの内容を表示する
//    空リストの場合は"Empty List"と表示する
//引数 MList *head:表示するリストを指すポインタ
//返り値:なし
//------------------------------------------------------------------
void print_mlist(MList *head) {
    /*---空リストが渡された場合は"Empty List."と表示する---*/
    if (isEmptyList(head)) {
        printf("Empty List\n");
    }
    
    /*---空リストでないなら要素のデータを表示する---*/
    else {
        printf("[%s, %.1f, %.1f]", getName(head), getHeight(*head), getWeight(*head));
        // 末尾の要素でないなら矢印を表示し、再帰呼び出し
        if (!isEmptyList(getNextMCell(*head))){
            printf(" -> ");
            print_mlist(getNextMCell(*head));
        }
        // 末尾の要素なら改行を表示
        else {
            printf("\n");
        }
    }
    
    return;
}

//------------------------------------------------------------------
//機能:リストの全要素を解放する
//引数 MList *head:要素を解放するリストを指すポインタ
//返り値:なし
//------------------------------------------------------------------
void free_mlist(MList *head) {
    /*---空リストなら何もしない---*/
    if (isEmptyList(head)) {
        return;
    }
    
    /*---再帰の帰りがけに要素を解放する---*/
    free_mlist(getNextMCell(*head));
    free(head);
    
    return;
}

//------------------------------------------------------------------
//機能:リストに氏名が辞書順になるよう要素を追加する
//    既存の名前のデータを追加しようとした場合、既存の名前のデータを更新する
//引数 MList *head  :要素を追加するリストを指すポインタ
//    char *name   :新たに追加する先頭要素の名前データ
//    double height:新たに追加する先頭要素の身長データ
//    double weight:新たに追加する先頭要素の体重データ
//返り値:処理後のリストの先頭要素へのポインタを返す
//------------------------------------------------------------------
MList *add_mmember(MList *head, char *name, double height, double weight) {
    /*---空リストなら先頭に要素を追加---*/
    if (isEmptyList(head)) {
        return(add_mmember_head(head, name, height, weight));
    }
    /*---既存の名前のデータを発見した場合、値を更新する---*/
    else if(strcmp(getName(head), name) == 0) {
        setParameter(head, name, height, weight, getNextMCell(*head));
        return(head);
    }
    /*---追加位置を探しながら再起呼び出し---*/
    else if (strcmp(getName(head), name) < 0) {
        setNextMCell(head, add_mmember(getNextMCell(*head), name, height, weight));
        return(head);
    }
    /*---追加すべき位置に要素を追加---*/
    else {
        return(add_mmember_head(head, name, height, weight));
    }
}

//------------------------------------------------------------------
//機能:リストの名前データがdelnameの要素を削除する
//引数 MList *head  :要素を削除するリストを指すポインタ
//    char *delname:削除対象の名前データ
//返り値:処理後のリストの先頭要素へのポインタを返す
//------------------------------------------------------------------
MList *delete_mmember(MList *head, char *delname) {
    /*---空リストなら何もしない---*/
    if (isEmptyList(head)) {
        return(head);
    }
    
    /*---再帰呼び出し---*/
    setNextMCell(head, delete_mmember(getNextMCell(*head), delname));
    
    /*---削除対象なら帰りがけに要素を削除する---*/
    if (strcmp(getName(head), delname) == 0) {
        return(delete_mmember_head(head));
    }
    
    return(head);
}
