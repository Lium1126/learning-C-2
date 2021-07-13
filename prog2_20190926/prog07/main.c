//
//  main.c
//  prog07
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------+
プログラミング及び演習II 第1回
問題7
問題4「"hoge"を10回出力する。ただし
改行は3回出力ごとに1回とする」のマジック
ナンバーをマクロ定義で解決する
---------------------------------*/

#include <stdio.h>

#define NUM 10
#define MOD 3

int main(int argc, const char * argv[]) {
    int i;
    for(i = 1;i <= NUM;i++){
        printf("hoge");
        if(i % MOD == 0){
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}
