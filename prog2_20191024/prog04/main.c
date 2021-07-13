//
//  main.c
//  prog04
//
//  Created by k19061kk on 2019/10/23.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------------------+
プログラミング及び演習II 第4回
問題4
要素数5のint型配列aと、その先頭を指すポインタ
paを用意する
 ・pa,pa+1,pa+2,...のアドレスの値を表示せよ
 ・a[0],a[1],...のアドレスを表示せよ
+------------------------------------*/

#include <stdio.h>

#define NUM 5

int main(int argc, const char * argv[]) {
    int a[NUM];
    int *pa = a; // paは配列aの先頭を指す
    int i;       // カウンタ変数
    
    /*---ポインタ変数の指すアドレス値を表示---*/
    printf("pa,pa+1,pa+2,...を表示---------\n");
    for(i = 0;i < NUM;i++){
        if(i == 0){
            printf("pa  :%p\n", pa);
        }else{
            printf("pa+%d:%p\n", i, pa + i);
        }
    }
    
    /*---配列の各要素のアドレスを表示---*/
    printf("a[0],a[1],...のアドレスを表示----\n");
    for(i = 0;i < NUM;i++){
        printf("a[%d]:%p\n", i, &a[i]);
    }
    
    return 0;
}
