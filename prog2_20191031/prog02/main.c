//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/10/30.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------------+
プログラミング及び演習II 第5回
問題2
文字列長を知る関数my_strlen()を実装しなさい
文字列長が正確に返されるかを確認しなさい
+--------------------------------------*/

#include <stdio.h>
#include <string.h>

#define MAX_LEN (256 + 1)

int my_strlen(char *str);  // 文字列長を求める自作関数

int main(int argc, const char * argv[]) {
    char str1[128] = "abc";
    char str2[] = "cde";
    char *str = "fgh";
    
    /*---文字列長を表示---*/
    printf("my_strlen------------------\n");
    printf("str1[128] = \"abc\":%d\n", my_strlen(str1));
    printf("str2[] = \"cde\"   :%d\n", my_strlen(str2));
    printf("*str = \"fgh\"     :%d\n", my_strlen(str));
    
    /*---上記が正しいか確認---*/
    printf("strlen---------------------\n");
    printf("str1[128] = \"abc\":%d\n", (int)strlen(str1));
    printf("str2[] = \"cde\"   :%d\n", (int)strlen(str2));
    printf("*str = \"fgh\"     :%d\n", (int)strlen(str));
    
    return 0;
}

//-----------------------------------------
//機  能:文字列strの文字列長を求める
//引数 char *str:文字列長を求める対象の文字配列
//返り値:strの文字列長をint型で返す
//-----------------------------------------
int my_strlen(char *str)
{
    int cnt = 0;  // 文字数をカウントする変数
    
    /*---ヌル文字を発見するまで文字数をカウント---*/
    while(str[cnt] != '\0'){
        cnt++;
    }
    
    return(cnt);
}
