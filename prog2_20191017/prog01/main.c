//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/10/17.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------+
 プログラミング及び演習II 第3回
 問題1
 char,intの変数を2つずつ定義し、それぞれ
 の変数のアドレスを表示せよ。　
 +--------------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int a, b;
    char c, d;
    
    printf("1つ目のint型変数のアドレス: %p\n", &a);
    printf("2つ目のint型変数のアドレス: %p\n", &b);
    printf("1つ目のchar型変数のアドレス: %p\n", &c);
    printf("2つ目のchar型変数のアドレス: %p\n", &d);
    
    return 0;
}
