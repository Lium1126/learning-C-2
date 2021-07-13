//
//  main.c
//  prog11
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------------+
プログラミング及び演習II 第1回
問題11
問題10「3から5までの乱数を出力しなさい」を拡張し、
 乱数の最小値・最大値をユーザーから入力させるようにしなさい
------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    int num;   // 乱数を格納する変数
    int start; // 乱数の最小値
    int end;   // 乱数の最大値
    
    /*---入力---*/
    printf("乱数の最小値を入力してください: ");
    scanf("%d", &start);
    printf("乱数の最大値を入力してください: ");
    scanf("%d", &end);
    
    if(start > end){
        printf("乱数の範囲が不適です\n");
    }else{
        /*---以下で乱数を生成---*/
        srand((unsigned int)time(NULL));
        num = rand() % (end - start + 1); // 0~(startからendまでの数の個数)の乱数を生成
        num += start;                     // 乱数の範囲の開始をstartに合わせる
        
        /*---出力---*/
        printf("%d\n", num);
    }
    
    return 0;
}
