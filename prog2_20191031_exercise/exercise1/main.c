//
//  main.c
//  exercise1
//
//  Created by k19061kk on 2019/10/31.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------------------+
プログラミング及び演習II 第5回
課題
文字配列を以下のように定義する
    char *list[] = {"hoge", "abc", "xy", "fugagaga"};
文字列長が短い順にソートするbubble_str_ptr()を実装せよ
 -swap_str_ptr(),sort_str_ptr()はそのまま使うこと
+----------------------------------------------------*/

#include <stdio.h>
#include <string.h>

//関数プロトタイプ宣言============================================================================
void bubble_str_ptr(char **plist, int num);  // 文字列を文字列長が短い順にソートする
void sort_str_ptr(char **pa, char **pb);     // 文字列を文字数でソートする(bubble_str_ptrのサブ関数)
void swap_str_ptr(char **pa, char **pb);     // 2つの文字列を入れ替える(sort_str_ptrのサブ関数)
void printData(char **plist, int num);       // 文字列配列listの中身を表示

//main()関数===================================================================================
int main(int argc, const char * argv[]) {
    char *list[] = {"hoge", "abc", "xy", "fugagaga"};
    int num_list = (int)(sizeof(list) / sizeof(list[0]));  // listが持つ文字列の個数
    
    /*---ソート前の状態を一度表示---*/
    printf("ソート前--------------------\n");
    printData(list, num_list);
    
    /*---ソートする---*/
    bubble_str_ptr(list, num_list);
    
    /*---結果を表示---*/
    printf("ソート後--------------------\n");
    printData(list, num_list);
    
    return 0;
}

//関数群=======================================================================================
//---------------------------------------------
//機  能:複数の文字列を文字列長の短い順にソートする
//引数 char **plist:ソート対象の文字列群
//    int num     :ソート対象の文字列の個数
//返り値:なし
//---------------------------------------------
void bubble_str_ptr(char **plist, int num)
{
    int i, j;  // カウンタ変数
    
    /*---バブルソート---*/
    for(i = 0;i < num - 1;i++){
        for(j = num - 1;j > i;j--){
            sort_str_ptr(&plist[j - 1], &plist[j]);
        }
    }
    
    return;
}

//---------------------------------------------
//機  能:2つの文字列を文字数の小さい順にソートする
//引数 char **pa:---+
//    char **pb:---+--ソートする文字列を指すポインタ
//返り値:なし
//---------------------------------------------
void sort_str_ptr(char **pa, char **pb)
{
    /*---文字列長を比べて、必要なら入れ替える---*/
    if(strlen(*pa) > strlen(*pb)){
        swap_str_ptr(pa, pb);
    }
    
    return;
}

//---------------------------------------------
//機  能:2つの文字列を入れ替える
//引数 char **pa:---+
//    char **pb:---+--入れ替える文字列を指すポインタ
//返り値:なし
//---------------------------------------------
void swap_str_ptr(char **pa, char **pb)
{
    char *temp; // 作業用変数
    
    /*---ポインタの指す先を入れ替え---*/
    temp = *pa;
    *pa = *pb;
    *pb = temp;
    
    return;
}

//---------------------------------------------
//機  能:文字列群を表示する
//引数 char **plist:表示対象の文字列群
//    int num     :表示する文字列の個数
//返り値:なし
//---------------------------------------------
void printData(char **plist, int num)
{
    int i;  // カウンタ変数
    
    /*---listの内容を表示---*/
    for(i = 0;i < num;i++){
        printf("list[%d]:%s\n", i, plist[i]);
    }
    
    return;
}
