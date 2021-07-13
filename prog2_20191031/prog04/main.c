//
//  main.c
//  prog04
//
//  Created by k19061kk on 2019/10/30.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------+
プログラミング及び演習II 第5回
問題4
char *str = "abcd";
strの文字を一文字ずつ縦に並べて出力せよ
+---------------------------------*/


#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char *str = "abcd";
    int i;                       // カウンタ変数
    int len = (int)strlen(str);  // strの文字数
    
    /*---ポインタstrを使って一文字ずつ表示---*/
    for(i = 0;i < len;i++){
        printf("%c\n", *(str + i));
    }
    
    return 0;
}
