//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/11/21.
//  Copyright © 2019 AIT. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int seekMin(int a, int b);                   // 引数のうち、小さい方の値を返す
void swap_str(char *s1, char *s2);           // 問題となっている関数

int main(int argc, const char * argv[]) {
    char str1[] = "abcde";
    char str2[] = "xyz";
    
    printf("Before swapping...\n");
    printf("str1 = %s\n", str1);
    printf("str2 = %s\n", str2);
    
    swap_str(str1, str2);
    
    printf("After swapping...\n");
    printf("str1 = %s\n", str1);
    printf("str2 = %s\n", str2);
    
    return 0;
}

//-----------------------------------
//機能:引数のうち、小さい方の値を返す
//引数 int a:---+
//    int b:---+--比較する整数値
//返り値:a,bの小さい方の値
//-----------------------------------
int seekMin(int a, int b) {
    if(a < b){
        return(a);
    }else{
        return(b);
    }
}

//-----------------------------------
//機能:2つの文字列を、文字数を文字列長の
//    短い方に合わせて入れ替える
//引数 char *s1:---+
//    char *s2:---+--入れ替える文字列
//返り値:なし
//-----------------------------------
void swap_str(char *s1, char *s2) {
    int len = seekMin((int)strlen(s1), (int)strlen(s2));  // 入れ替える文字列の文字列長
    char temp;                                            // 作業用変数
    int i;                                                // カウンタ変数
    
    /*---len文字分s1とs2を入れ替え---*/
    for(i = 0;i < len;i++){
        temp = s1[i];
        s1[i] = s2[i];
        s2[i] = temp;
    }
    
    /*---ヌル文字を付加---*/
    s1[i] = '\0';
    s2[i] = '\0';
    
    return;
}
