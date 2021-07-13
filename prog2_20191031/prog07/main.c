//
//  main.c
//  prog07
//
//  Created by k19061kk on 2019/10/30.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------+
プログラミング及び演習II 第5回
問題7
char a[128] = "abcde";
char b[128] = "xyz";
・前回実装したswap()関数の文字列版swap_str()を
 実装せよ
・文字列2つが与えられた時、それら2つの文字列を入れ
 替える
    -swap_str()の中でstrcpy()を使用する
+----------------------------------------*/

#include <stdio.h>
#include <string.h>

void swap_str(char *a, char *b);  // 2つの文字列aとbを入れ替える

int main(int argc, const char * argv[]) {
    char a[128] = "abcde";
    char b[128] = "xyz";
    
    /*---入れ替え前の状態を一度表示---*/
    printf("入れ替え前-----------------\n");
    printf("a:%s\n", a);
    printf("b:%s\n", b);

    /*---文字列の入れ替え---*/
    swap_str(a, b);
    
    /*---結果を表示---*/
    printf("入れ替え後-----------------\n");
    printf("a:%s\n", a);
    printf("b:%s\n", b);
    
    return 0;
}

//-----------------------------------------
//機  能:文字列aとbを入れ替える
//引数 char *a:---+
//    char *b:---+--入れ替える文字列
//返り値:なし
//-----------------------------------------
void swap_str(char *a, char *b)
{
    char temp[128];  // 交換する文字列を一時保管する配列
    
    /*---文字列を入れ替える---*/
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
    
    return;
}
