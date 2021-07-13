//
//  main.c
//  prog10
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------+
プログラミング及び演習II 第1回
問題10
3から5までの乱数を出力しなさい
-------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START 3
#define END 5

int main(int argc, const char * argv[]) {
    int num; // 乱数を格納する変数
    
    printf("3~5の乱数を表示します\n");

    /*---以下で3~5の乱数を生成---*/
    srand((unsigned int)time(NULL));
    num = rand() % (END - START + 1); // 1~3の乱数を生成
    num += START;                     // 3~5の範囲に調整
    
    /*---出力---*/
    printf("%d\n", num);
    
    return 0;
}
