//
//  main.c
//  prog07
//
//  Created by k19061kk on 2019/10/17.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------------------+
プログラミング及び演習II 第3回
問題7
int型の変数aとそれへのポインタpaを用意し、
「aの格納されているアドレス」と
「paが格納されているアドレス」を表示しなさい。
+------------------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int a;
    int *pa = &a;
    
    printf("aのアドレス :%p\n", pa);
    printf("pxのアドレス:%p\n", &pa);
    
    return 0;
}
