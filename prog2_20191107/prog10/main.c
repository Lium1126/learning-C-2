//
//  main.c
//  prog10
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------+
プログラミング及び演習II 第6回
問題10
コンマ区切りの文字列を、コンマで分割せよ
---------------------------------*/

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char str[128] = "foo,bar,hoge,fuga"; // 分割対象文字列
    char *ptr;                           // 分割後の文字列を指すポインタ変数
    
    /*---1回目の分割---*/
    ptr = strtok(str, ",");
    printf("%s\n", ptr);
    
    /*---2回目以降の分割---*/
    while(ptr != NULL){
        ptr = strtok(NULL, ",");  // strtok()で変更されたNULLポインタを先頭とする
        
        // ptrがNULL以外の場合エラーとなるのでその場合を弾く
        if(ptr != NULL){
            printf("%s\n", ptr);
        }
    }
    
    return 0;
}
