//
//  main.c
//  prog07
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------+
プログラミング及び演習II 第6回
問題7
number.txtを追記モードで読み込んで100~199を
追加せよ
---------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define START 100
#define END 199

int main(int argc, const char * argv[]) {
    FILE *fp; // ファイルポインタ
    int i;    // カウンタ変数
    
    /*---ファイルオープン---*/
    fp = fopen("number.txt", "a");
    if(fp == NULL){ // ファイルを正しく開けなかった
        fprintf(stderr, "Cannot open the file.\n");
        exit(0);
    }
    
    /*---100~199を追記---*/
    for(i = START;i <= END;i++){
        fprintf(fp, "%d\n", i);
    }
    
    /*---終了処理---*/
    fclose(fp);
    return 0;
}
