//
//  main.c
//  prog01
//
//  Created by k19061kk on 2020/01/30.
//  Copyright © 2020 AIT. All rights reserved.
//

/*-----------------------------------------+
 プログラミング及び演習II
 第15回 期末試験解答 問題1
 cars.csvを1行ずつ読み込み、その内容を逐次表示する
 プログラムを作成せよ.
 +-----------------------------------------*/

//定義======================================================================================
//インクルード------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

//マクロ-----------------------------------------------------------------
#define MAX_LEN 256

//関数群====================================================================================
int main(int argc, const char * argv[]) {
    FILE *fp;               // cars.csvのファイルポインタ
    char line[MAX_LEN];     // ファイル入力を1行受け付けるバッファ配列
    
    /*---ファイルを開く---*/
    fp = fopen("./cars.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---ファイルから1行ずつ読み込んで逐次表示する---*/
    while (fgets(line, MAX_LEN, fp) != NULL) {
        printf("%s", line);
    }
    
    /*---ファイルを閉じる---*/
    fclose(fp);
    
    return 0;
}
