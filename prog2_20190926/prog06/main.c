//
//  main.c
//  prog06
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*---------------------------------------+
プログラミング及び演習II 第1回
問題6
問題2「"Hello, World!"を10回出力するプログラム
を作る」のマジックナンバーをマクロ定義で解消する
----------------------------------------*/

#include <stdio.h>

#define NUM 10

int main(int argc, const char * argv[]) {
    int i;
    for(i = 0;i < NUM;i++){
        printf("Hello, World!\n");
    }
    return 0;
}
