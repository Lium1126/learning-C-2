//
//  main.c
//  prog06
//
//  Created by k19061kk on 2019/11/13.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------------+
プログラミング及び演習II 第7回
問題6
char str1[] = "ABCDE";
char str2[] = "XYZ";
char *str;
2つの文字列を連結した文字列strを作れ。
 ※malloc()を使うこと
+------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char str1[] = "ABCDE";  //---+
    char str2[] = "XYZ";    //---+--連結前の文字列
    char *str;              // str1とstr2を連結した文字列
    int len;                // strに必要な文字変数の領域の個数
    
    /*---連結文字列を格納するためのメモリ領域を動的に確保---*/
    len = (int)strlen(str1) + (int)strlen(str2) + 1;   // 連結文字列+ヌル文字
    if((str = (char*)malloc(sizeof(char) * len)) == NULL){
        fprintf(stderr, "No enough memory.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---strが指す領域に連結文字列を格納---*/
    strcpy(str, str1);
    strcat(str, str2);
    
    /*---結果を出力---*/
    printf("str:%s\n", str);
    
    /*---後処理---*/
    free(str);
    
    return 0;
}
