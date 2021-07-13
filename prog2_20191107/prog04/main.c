//
//  main.c
//  prog04
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------+
プログラミング及び演習II 第6回
問題4
ユーザからの入力文字列を大文字に変換
して出力せよ
------------------------------*/

#include <stdio.h>
#include <ctype.h>

#define LEN 256

int main(int argc, const char * argv[]) {
    char str[LEN];    // 入力文字列
    char upper[LEN];  // 大文字に変換した文字列を格納する文字配列
    int i;            // カウンタ変数
    
    /*---入力---*/
    printf("input: ");
    scanf("%s", str);
    
    /*---小文字を大文字に変換---*/
    i = 0;
    while(str[i] != '\0'){
        upper[i] = (char)toupper((int)str[i]);
        i++;
    }
    
    /*---出力---*/
    printf("output: %s\n", upper);
    
    return 0;
}
