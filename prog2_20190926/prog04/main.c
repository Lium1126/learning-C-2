//
//  main.c
//  prog04
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*---------------------------+
プログラミング及び演習II 第1回
問題4
"hoge"を10回出力する
ただし改行は3回出力ごとに1回とする
-----------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int i;
    for(i = 1;i <= 10;i++){
        printf("hoge");
        if(i % 3 == 0){
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}
