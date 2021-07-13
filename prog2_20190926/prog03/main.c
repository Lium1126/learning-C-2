//
//  main.c
//  prog03
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------------------+
プログラミング及び演習II 第1回
問題3
標準入力で数字を入力させて、その数だけ
"Hello, World!"を出力するプログラムを作る
エラー処理は不要
-------------------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int i, n;
    
    // input
    printf("n? ");
    scanf("%d", &n);
    
    // output
    for(i = 0;i < n;i++){
        printf("Hello, World!\n");
    }
    return 0;
}
