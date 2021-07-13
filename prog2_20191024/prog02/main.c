//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/10/23.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------------------+
プログラミング及び演習II 第4回
問題2
要素数3のint型配列を作成し、各要素のアドレス
を表示せよ
+------------------------------------*/

#include <stdio.h>

#define NUM 3

int main(int argc, const char * argv[]) {
    int a[NUM];
    int i;    // カウンタ変数
    
    for(i = 0;i < NUM;i++){
        printf("a[%d]:%p\n", i, &a[i]);
    }
    
    return 0;
}
