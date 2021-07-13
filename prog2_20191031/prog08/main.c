//
//  main.c
//  prog08
//
//  Created by k19061kk on 2019/10/30.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------------+
プログラミング及び演習II 第5回
問題8
char *a = "AB";
char *b = "XY";
・前回実装したswap()関数の文字列版swap_str_ptr()を
 実装せよ
・文字列2つが与えられた時、それら2つの文字列を入れ
 替える
  -ポインタのポインタを使用
  -ポインタの指し先を入れ替える
+-------------------------------------------*/

#include <stdio.h>

void swap_str_ptr(char **pa, char **pb);   // 2つの文字列を入れ替える

int main(int argc, const char * argv[]) {
    char *a = "AB";
    char *b = "XY";
    
    /*---入れ替え前の状態を一度表示---*/
    printf("入れ替え前-----------------\n");
    printf("a:%s\n", a);
    printf("b:%s\n", b);

    /*---文字列の入れ替え---*/
    swap_str_ptr(&a, &b);
    
    /*---結果を表示---*/
    printf("入れ替え後-----------------\n");
    printf("a:%s\n", a);
    printf("b:%s\n", b);
    
    return 0;
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
