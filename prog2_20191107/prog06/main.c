//
//  main.c
//  prog06
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------+
プログラミング及び演習II 第6回
問題6
100回ループして0から99までの数字をnumber.txt
に出力せよ
---------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define START 0
#define END 99

int main(int argc, const char * argv[]) {
    FILE *fp; // ファイルポインタ
    int i;    // カウンタ変数
    
    /*---ファイルオープン---*/
    fp = fopen("number.txt", "w");
    if(fp == NULL){ // ファイルを正しく開けなかった
        fprintf(stderr, "Cannot open the file.\n");
        exit(0);
    }
    
    /*---0~99の数字をファイルに書き込む---*/
    for(i = START;i <= END;i++){
        fprintf(fp, "%d\n", i);
    }
    
    /*---終了処理---*/
    fclose(fp);
    return 0;
}
