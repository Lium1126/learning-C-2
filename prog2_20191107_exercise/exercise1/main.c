//
//  main.c
//  exercise1
//
//  Created by k19061kk on 2019/11/07.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------------------+
プログラミング及び演習II 第6回
課題
前回課題の文字列ソーティングにかかる時間を出力せよ
 ・配列の要素数は20
 ・適当に文字列を入れて初期化すること
+----------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <time.h>

//関数プロトタイプ宣言============================================================================
void bubble_str_ptr(char **plist, int num);  // 文字列を文字列長が短い順にソートする
void sort_str_ptr(char **pa, char **pb);     // 文字列を文字数でソートする(bubble_str_ptrのサブ関数)
void swap_str_ptr(char **pa, char **pb);     // 2つの文字列を入れ替える(sort_str_ptrのサブ関数)
void printData(char **plist, int num);       // 文字列配列listの中身を表示

//main()関数===================================================================================
int main(int argc, const char * argv[]) {
    char *list[] = {"hoge", "abc", "xy", "fugagaga", "K19061",
                    "algorithm", "bubble", "heap", "merge", "topological",
                    "quick", "Dijkstra", "Union-Find Tree", "Segment Tree", "BIT",
                    "data", "structure", "sort", "Convex hull", "recursion"
    };
    int num_list = (int)(sizeof(list) / sizeof(list[0]));  // listが持つ文字列の個数
    clock_t start, end;                                    // 計測開始/終了の時間
    
    /*---ソート前の状態を一度表示---*/
    printf("ソート前--------------------\n");
    printData(list, num_list);
    
    /*---ソートする---*/
    start = clock();
    bubble_str_ptr(list, num_list);
    end = clock();
    /*---結果を表示---*/
    printf("ソート後--------------------\n");
    printData(list, num_list);

    /*---ソーティングにかかった時間を出力---*/
    printf("ソーティングにかかった時間: %f[sec]\n", (double)(end - start) / CLOCKS_PER_SEC);
    
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
        printf("list[%2d]:%s\n", i, plist[i]);
    }
    
    return;
}
