//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/12/11.
//  Copyright © 2019 AIT. All rights reserved.
//

/*---------------------------------+
 プログラミング及び演習II
 第11回 問題1
 ifdef, endifを使ってデバッグメッセージの
 表示・非表示を変更せよ
 +---------------------------------*/

#include <stdio.h>

#define DEBUG_ON

int main(int argc, const char * argv[]) {
    int n = 5;

#ifdef DEBUG_ON
    printf("debug message:n = %d\n", n);
    (void)getchar();
#endif

    printf("n * 3 = %d\n", n * 3);

    return 0;
}
