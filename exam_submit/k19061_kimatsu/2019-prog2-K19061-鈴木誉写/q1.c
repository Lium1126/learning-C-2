//
//  main.c
//  prog01
//
//  Created by k19061kk on 2020/01/23.
//  Copyright © 2020 AIT. All rights reserved.
//

/*------------------------------------------------+
 プログラミング及び演習II 期末試験
 第1問
 cars.csvを1行ずつ読み込み、その内容を逐次表示するプログラム
 を作成せよ.
 +------------------------------------------------*/

//定義===================================================================================
//インクルード------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

//マクロ-----------------------------------------------------------------------
#define MAX_LEN 256

//関数===================================================================================
int main(int argc, const char * argv[]) {
    FILE *fp;
    char line[MAX_LEN];
    
    /*---ファイルを開く---*/
    fp = fopen("./cars.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---ファイルから入力しながら表示---*/
    while (fgets(line, MAX_LEN, fp) != NULL) {
        printf("%s", line);
    }
    
    /*---ファイルを閉じる---*/
    fclose(fp);
    
    return 0;
}
