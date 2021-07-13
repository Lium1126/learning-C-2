//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/10/30.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------+
 プログラミング及び演習II 第5回
 問題1
 char str1[128] = "abc";
 char str2[] = "cde";
 char *str = "fgh";
 ・文字列長を求める関数strlen()を使って文字列長を
 求めなさい
 ・sizeofを使ってそれぞれのサイズを求めなさい
 +----------------------------------------*/

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char str1[128] = "abc";
    char str2[] = "cde";
    char *str = "fgh";
    
    printf("str1[128]-----------------\n");
    printf("strlen:%d\n", (int)strlen(str1));
    printf("sizeof:%d\n", (int)sizeof(str1));  // 128:1byte * 128
    
    printf("str2[]--------------------\n");
    printf("strlen:%d\n", (int)strlen(str2));
    printf("sizeof:%d\n", (int)sizeof(str2));  // 4:1byte * 4
    
    printf("*str----------------------\n");
    printf("strlen:%d\n", (int)strlen(str));
    printf("sizeof:%d\n", (int)sizeof(str));   // 8:ポインタのサイズ
    
    return 0;
}
