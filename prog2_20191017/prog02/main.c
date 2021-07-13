//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/10/17.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------+
プログラミング及び演習II 第3回
問題2
2つの変数(int)と、それを指すポインタを用意
する。
 ポインタを用いて2つの変数の値を変更せよ。
+----------------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int a = 10, b = 20;
    int *pa = &a, *pb = &b;
    
    /*---変更前に一度表示---*/
    printf("変更前:a = %d, b = %d\n", a, b);
    
    /*---値の変更---*/
    *pa = 100;
    *pb = 100000;
    
    /*---変更した結果を表示---*/
    printf("変更後:a = %d, b = %d\n", a, b);
    
    return 0;
}
