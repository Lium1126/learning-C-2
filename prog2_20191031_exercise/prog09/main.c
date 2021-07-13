//
//  main.c
//  prog09
//
//  Created by k19061kk on 2019/10/30.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------------+
プログラミング及び演習II 第5回
問題9
char *a = "abcde";
char *b = "xyz";
2つの文字列を比べて文字数でソートするsort_str_ptr()
を実装せよ
 -ポインタのポインタを使用
 -swap_str_ptr()を使用
+-------------------------------------------*/


#include <stdio.h>
#include <string.h>

void sort_str_ptr(char **pa, char **pb);  // 文字列を文字数でソートする
void swap_str_ptr(char **pa, char **pb);  // 2つの文字列を入れ替える(sort_str_ptrのサブ関数)

int main(int argc, const char * argv[]) {
    char *a = "abcde";
    char *b = "xyz";
    
    /*---ソート前の状態を一度表示---*/
    printf("ソート前-----------------\n");
    printf("a:%s\n", a);
    printf("b:%s\n", b);

    /*---文字列のソート---*/
    sort_str_ptr(&a, &b);
    
    /*---結果を表示---*/
    printf("ソート後-----------------\n");
    printf("a:%s\n", a);
    printf("b:%s\n", b);
    
    return 0;
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
