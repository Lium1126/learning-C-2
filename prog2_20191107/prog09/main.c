//
//  main.c
//  prog09
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------------+
プログラミング及び演習II 第6回
問題9
meibo.txtを追記モードで開き、ユーザから任意回数
入力される人物名をmeibo.txtに追記せよ
----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define LEN 256

int main(int argc, const char * argv[]) {
    FILE *fp;       // ファイルポインタ
    int n;          // 新規登録する人数
    char name[LEN]; // 新規登録する名前を格納する文字列配列
    int i;          // カウンタ変数
    
    /*---ファイルオープン---*/
    fp = fopen("meibo.txt", "a");
    if(fp == NULL){ // ファイルが正しく開けなかった
        fprintf(stderr, "Cannot open the file.\n");
        exit(0);
    }
    
    /*---新規登録する情報を入力し、meibo.txtに追記---*/
    printf("新規登録する人の数を入力してください: ");
    scanf("%d", &n);
    
    if(n < 0){
        fprintf(stderr, "入力値が不適です\n");
    }else{
        for(i = 1;i <= n;i++){
            printf("%d人目の名前を入力してください: ", i);
            scanf("%s", name);
            fprintf(fp, "%s\n", name);
        }
    }
    
    /*---終了処理---*/
    fclose(fp);
    return 0;
}
