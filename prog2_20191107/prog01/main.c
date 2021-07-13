//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------+
 プログラミング及び演習II 第6回
 問題1
 ・char* str1="hoge"
 ・char* str2="hage"
 の2つの文字列を比較せよ
 同じ場合は"SAME",違う場合は"DIFF"と出力
 -----------------------------------*/

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char* str1 = "hoge"; // ---+
    char* str2 = "hage"; // ---+--比較対象の文字列
    
    if(strcmp(str1, str2) == 0){ // str1とstr2は一致
        printf("SAME\n");
    }else{                       // str1とstr2は不一致
        printf("DIFF\n");
    }
    
    return 0;
}
