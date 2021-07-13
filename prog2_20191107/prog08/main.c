//
//  main.c
//  prog08
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------+
プログラミング及び演習II 第6回
問題8
100以下の素数を発見するプログラムを作成し、発見
された素数をprime.txtに出力せよ
---------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define LIMIT 100

int main(int argc, const char * argv[]) {
    FILE *fp;                  // ファイルポインタ
    int i, j;                  // カウンタ変数
    int prime[LIMIT + 1] = {}; // 添え字が素数か否かのフラグを持つ配列
                               // 素数:0 素数でない:1
    
    /*---ファイルオープン---*/
    fp = fopen("prime.txt", "w");
    if(fp == NULL){ // ファイルを正しく開けなかった
        fprintf(stderr, "Cannot open the file.\n");
        exit(0);
    }
    
    /*---エラトステネスの篩による素数生成---*/
    for(i = 2;i <= LIMIT;i++){
        if(prime[i] == 0){
            for(j = i * 2;j <= LIMIT;j += i){
                prime[j] = 1;
            }
        }
    }
    
    /*---素数をファイルに書き込む---*/
    for(i = 2;i <= LIMIT;i++){
        if(prime[i] == 0){ // iが素数である
            fprintf(fp, "%d\n", i);
        }
    }
    
    /*---終了処理---*/
    fclose(fp);
    return 0;
}
