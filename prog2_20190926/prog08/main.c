//
//  main.c
//  prog08
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------+
プログラミング及び演習II 第1回
問題8
問題5「"hoge"を100回出力する。
ただし2の倍数の時は"foo"も出力する。
3の倍数の時は"bar"も出力する」のマジック
ナンバーをマクロ定義で解決する
----------------------------------*/

#include <stdio.h>

#define NUM 100
#define TWO 2
#define THREE 3

int main(int argc, const char * argv[]) {
    int i;
    for(i = 1;i <= NUM;i++){
        printf("hoge");
        if(i % TWO == 0){
            printf("foo");
        }
        if(i % THREE == 0){
            printf("bar");
        }
        printf("\n");
    }
    return 0;
}
