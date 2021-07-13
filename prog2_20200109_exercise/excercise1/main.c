//
//  main.c
//  excercise1
//
//  Created by k19061kk on 2019/12/31.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------------------+
 プログラミング及び演習II 第13回
 課題
 問題8を発展させる.
    ・ファイル読み込み後、ユーザからの入力を任意回数受け付けて
    　要素を追加/削除できるようにする
    ・リスト構造の中身を同名ファイルに出力する
 +-------------------------------------------------*/

//定義=============================================================================
//インクルード---------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//マクロ----------------------------------------------------------------
#define MAX_LEN 256

//データ構造----------------------------------------------------------------
typedef struct cell {
    int num;            // データ部
    struct cell *next;  // ポインタ部
} Cell;

typedef Cell List;   // 意味合いによってリストとセルを使い分け

//関数プロトタイプ宣言================================================================
//基本操作関数--------------------------------------------------------------
int getCellData(Cell cell);                   // cellからデータを取得する
void setCellData(Cell *cell, int num);        // cellのデータ部にnumを設定する
Cell *getNextCell(Cell cell);                 // cellから次のセルへのポインタを取得する
void setNextCell(Cell *cell, Cell *next);     // cellのポインタ部にnextを設定する
List *makeEmptyList(void);                    // 空リストを作る
int isEmptyList(List *list);                  // listが空リストか判定する
void initList(List **head);                   // リストを空リストで初期化する
Cell *createCell(int num);                    // データにnumを持つ新たなセルを作る

//操作関数------------------------------------------------------------------
void print_list(List *head);                  // リストの内容を表示する
void fprint_list(List *head, FILE *outfile);  // リストの内容をファイルに出力する
List *add_member(List *head, int num);        // リストに小さい順になるよう要素を追加する
List *add_member_head(List *head, int num);   // リストの先頭に要素を追加する
void free_list(List *head);                   // リストの全要素を解放する
List *delete_member(List *head, int delnum);  // データがdelnumの要素を解放する
List *delete_member_head(List *head);         // リストの先頭要素を解放する

//関数群===========================================================================
//main関数-----------------------------------------------------------------
int main(int argc, const char * argv[]) {
    List *head;               // 先頭のポインタを用意
    FILE *fp;                 // ファイルポインタ
    char line[MAX_LEN];       // ファイルから1行分入力を受け付ける文字列バッファ
    char input_str[MAX_LEN];  // コマンド入力用変数(文字)
    int input_num;            // 入力用変数(整数)
    
    /*---リストを初期化---*/
    initList(&head);
    
    /*---入力ファイルを開く---*/
    fp = fopen("./numlist.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open the input file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---ファイル入力を受け付け、リストに格納---*/
    while (fgets(line, MAX_LEN, fp) != NULL) {
        sscanf(line, "%d", &input_num);
        head = add_member(head, input_num);
    }
    
    /*---入力ファイルを閉じる---*/
    fclose(fp);
    
    /*---操作前のリストの内容を表示---*/
    print_list(head);
    
    /*---ユーザからのコマンドに応じて必要な処理をする---*/
    do {
        // ユーザからのコマンド入力
        printf("command? ");
        fgets(line, MAX_LEN, stdin);
        sscanf(line, "%s %d", input_str, &input_num);
        
        // コマンドに応じた処理をする
        if (strlen(input_str) == 1) {   // 入力されたコマンドの文字部分が一文字なら
            switch (input_str[0]) {
                case 'a':
                    head = add_member(head, input_num);
                    break;
                case 'd':
                    head = delete_member(head, input_num);
                    break;
                case 'p':
                    print_list(head);
                    break;
                case 'q':
                    printf("Finish.\n");
                    break;
                default:
                    printf("No such command exists.\n");
                    break;
            }
        } else {
            printf("No such command exists.\n");
        }
    } while (strlen(input_str) != 1 || input_str[0] != 'q');  // 入力された文字が'q'なら終了
    
    /*---リストの内容を表示---*/
    print_list(head);
    
    /*---出力ファイルを閉じる---*/
    fp = fopen("numlist.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open the output file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---リストの内容をファイルに出力---*/
    fprint_list(head, fp);
    
    /*--出力ファイルを閉じる---*/
    fclose(fp);
    
    /*---リストの全要素を解放する---*/
    free_list(head);
    initList(&head);
    
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
//機能:リストを空リストで初期化する
//引数 List **head:初期化するリストを指すポインタへのポインタ
//返り値:なし
//---------------------------------------------------------
void initList(List **head) {
    *head = makeEmptyList();
    return;
}

//---------------------------------------------------------
//機能:新しくセルを生成する
//引数 int num:新しく生成したセルのデータ
//返り値:新しく生成したセルを指すポインタを返す
//      新しいセルの生成に失敗した場合は空リストを返す
//---------------------------------------------------------
Cell *createCell(int num) {
    Cell *new_cell;   // 新しく作成するセルを指すポインタ
    
    /*---新しいセルを動的に確保---*/
    new_cell = (Cell*)malloc(sizeof(Cell));
    
    /*---確保に失敗した場合は空リストを返す---*/
    if (new_cell == NULL) {
        return(makeEmptyList());
    }
    
    /*---新しいセルのデータ部にnumを、ポインタ部に空リストを設定---*/
    setCellData(new_cell, num);
    setNextCell(new_cell, makeEmptyList());
    
    return(new_cell);
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
    
    /*---末尾のセルでないなら矢印を表示---*/
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

//---------------------------------------------------------
//機能:リストの内容をファイルに出力する
//引数 List *head   :リストの先頭要素を指すポインタ
//    FILE *outfile:出力ファイルへのファイルポインタ
//返り値:なし
//---------------------------------------------------------
void fprint_list(List *head, FILE *outfile) {
    /*---空リストであったら何もしない(基底条件)---*/
    if (isEmptyList(head)) {
        return;
    }
    
    /*---データをファイルに出力---*/
    fprintf(outfile, "%d\n", getCellData(*head));
    
    /*---再帰呼び出し---*/
    fprint_list(getNextCell(*head), outfile);
    
    return;
}

//---------------------------------------------------------
//機能:リストに小さい順になるよう要素を追加する
//    要素の追加に失敗した場合はリストに変更を加えない
//引数 List *head:リストの先頭要素を指すポインタ
//    int num   :新たに追加する要素のデータ
//返り値:処理後のリストの先頭要素を指すポインタを返す
//---------------------------------------------------------
List *add_member(List *head, int num) {
    /*---空リストなら先頭に要素を追加---*/
    if (isEmptyList(head)) {
        return(add_member_head(head, num));
    }
    /*---要素を追加する箇所を探しながら再帰呼び出し---*/
    else if (getCellData(*head) < num) {
        setNextCell(head, add_member(getNextCell(*head), num));
        return(head);
    }
    /*---小さい順になるように要素を追加---*/
    else {
        return(add_member_head(head, num));
    }
}

//---------------------------------------------------------
//機能:リストの先頭に要素を追加する
//    要素の追加に失敗した場合はリストに変更を加えない
//引数 List *head:リストの先頭要素を指すポインタ
//    int num   :新たに追加する要素のデータ
//返り値:処理後のリストの先頭要素を指すポインタを返す
//---------------------------------------------------------
List *add_member_head(List *head, int num) {
    Cell *new_cell;     // 新しいセルへのポインタ
    
    /*---新しいセルを生成---*/
    new_cell = createCell(num);
    
    /*---新しいセルの生成に失敗した場合は何もしない---*/
    if (isEmptyList(new_cell)) {
        return(head);
    }
    
    /*---新しいセルをリストの先頭に追加---*/
    setNextCell(new_cell, head);
    
    return(new_cell);
}

//---------------------------------------------------------
//機能:リストの全要素を解放する
//引数 List *head:リストの先頭要素を指すポインタ
//返り値:なし
//---------------------------------------------------------
void free_list(List *head) {
    /*--空リストが渡された時は何もしない---*/
    if (isEmptyList(head)) {
        return;
    }
    
    /*---最後の要素でない限り再起呼び出し---*/
    if (!isEmptyList(getNextCell(*head))) {
        free_list(getNextCell(*head));
    }
    
    /*---要素を解放---*/
    free(head);
    
    return;
}

//---------------------------------------------------------
//機能:リスト内のdelnumをデータとする要素を解放する
//引数 List *head:リストの先頭要素を指すポインタ
//    int delnum:解放する要素の持つデータ
//返り値:処理後のリストの先頭要素を指すポインタを返す
//---------------------------------------------------------
List *delete_member(List *head, int delnum) {
    /*---空リストなら何もしない---*/
    if (isEmptyList(head)) {
        return(head);
    }
    /*---末尾のセルでない限り再帰呼び出し---*/
    if (!isEmptyList(getNextCell(*head))) {
        setNextCell(head, delete_member(getNextCell(*head), delnum));
    }
    /*---今見ているセルが削除対象なら削除する---*/
    if (!isEmptyList(head) && getCellData(*head) == delnum) {
        return(delete_member_head(head));
    }
    return(head);
}

//---------------------------------------------------------
//機能:リストの先頭要素を解放する
//引数 List *head:リストの先頭要素を指すポインタ
//返り値:処理後のリストの先頭要素を指すポインタを返す
//---------------------------------------------------------
List *delete_member_head(Cell *head) {
    Cell *next = getNextCell(*head);  // 削除対象の次のセルへのポインタ
    
    /*---解放---*/
    free(head);
        
    return(next);
}
