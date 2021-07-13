//
//  main.c
//  prog06
//
//  Created by k19061kk on 2019/10/30.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------+
プログラミング及び演習II 第5回
問題6
char a[128] = "abc";
char b[128];
文字列をコピーするmy_strcpy()を実装せよ
+---------------------------------*/

#include <stdio.h>

#define MAX_LEN (256 + 1)

void my_strcpy(char *dest, char *src);  // srcをdestにコピーする自作関数

int main(int argc, const char * argv[]) {
    char a[128] = "abc";
    char b[128];
    
    /*---aをbにコピー---*/
    my_strcpy(b, a);
    
    /*---結果を表示---*/
    printf("a:%s\n", a);
    printf("b:%s\n", b);
    
    return 0;
}

//-----------------------------------------
//機  能:文字列destに文字列srcをコピーする
//引数 char *dest:コピー先の文字列
//    char *src :コピー元の文字列
//返り値:なし
//-----------------------------------------
void my_strcpy(char *dest, char *src)
{
    int i = 0;  // カウンタ変数
    
    /*---destにsrcを一文字ずつコピー---*/
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // destにヌル文字を付加
    
    return;
}
