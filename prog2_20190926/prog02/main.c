//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*---------------------------------------+
プログラミング及び演習II 第1回
問題2
"Hello, World!"を10回出力するプログラムを作る
----------------------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int i;
    for(i = 0;i < 10;i++){
        printf("Hello, World!\n");
    }
    return 0;
}
