//
//  main.c
//  prog05
//
//  Created by k19061kk on 2019/10/23.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------------------+
プログラミング及び演習II 第4回
問題5
要素数5のint型配列を用意する
    int a[5] = {10, 20, 30, 40, 50};
上記配列の先頭要素へのポインタpを用意する
    int *p = a;
pを用いて配列の各要素の値を1プラスせよ
+------------------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int a[5] = {10, 20, 30, 40, 50};
    int *p = a;
    int i;  // カウンタ変数
    
    for(i = 0;i < 5;i++){
        *(p + i) += 1;
    }
    
    for(i = 0;i < 5;i++){
        printf("a[%d]:%d\n", i, a[i]);
    }
    
    return 0;
}
