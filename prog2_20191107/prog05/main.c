//
//  main.c
//  prog05
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------+
プログラミング及び演習II 第6回
問題5
ファイルを読み込んでその内容を標準出力に表示せよ
---------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define LEN 256

int main(int argc, const char * argv[]) {
    FILE *fp;       // ファイルポインタ
    char line[LEN]; // 1行分を読み込むための配列
    
    /*---ファイルオープン---*/
    fp = fopen("meibo.txt", "r");
    if(fp == NULL){ // ファイルを正しく開けなかった
        fprintf(stderr, "Cannot open the file.\n");
        exit(0);
    }
    
    /*---1行ずつ読み込んで表示---*/
    while(fgets(line, LEN, fp) != NULL){
        printf("%s", line);
    }
    
    /*---終了処理---*/
    fclose(fp);
    return 0;
}
