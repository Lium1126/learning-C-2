//
//  main.c
//  prog05
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------+
プログラミング及び演習II 第1回
問題5
"hoge"を100回出力する
ただし2の倍数の時は"foo"も出力する
3の倍数の時は"bar"も出力する
------------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int i;
    for(i = 1;i <= 100;i++){
        printf("hoge");
        if(i % 2 == 0){
            printf("foo");
        }
        if(i % 3 == 0){
            printf("bar");
        }
        printf("\n");
    }
    return 0;
}
