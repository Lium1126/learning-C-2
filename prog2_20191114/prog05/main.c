//
//  main.c
//  prog05
//
//  Created by k19061kk on 2019/11/13.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------------------+
プログラミング及び演習II 第7回
問題5
ユーザから数字を入力させ、その数だけ整数値を入力させる。
入力された整数値を逆順で表示せよ。
 ※malloc()を使うこと
+--------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    int num;  // 入力する整数値の個数
    int *p;   // 動的に確保するメモリ領域の先頭を指すポインタ
    int i;    // カウンタ変数
    
    /*---整数値の個数を入力---*/
    printf("入力する整数値の個数を入力してください:");
    scanf("%d", &num);
    
    /*---int型のメモリ領域をnum個分確保---*/
    if((p = (int*)malloc(sizeof(int) * num)) == NULL){
        fprintf(stderr, "No enough memory.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---num個の整数値を入力---*/
    for(i = 0;i < num;i++){
        printf("%d個目の整数値:", i + 1);
        scanf("%d", &p[i]);
    }
    
    /*---入力された整数値を逆順で表示---*/
    printf("逆順で出力---------------------------\n");
    for(i = num - 1;i >= 0;i--){
        printf("%d個目の整数値:%d\n", i + 1, p[i]);
    }
    
    /*---後処理---*/
    free(p);
    
    return 0;
}
