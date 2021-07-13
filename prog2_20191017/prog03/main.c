//
//  main.c
//  prog03
//
//  Created by k19061kk on 2019/10/17.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------+
プログラミング及び演習II 第3回
問題3
ダメな例(20191017.pdf参照)をポインタを
用いて解決せよ。
+--------------------------------*/

#include <stdio.h>

void getSumDiff(int num1, int num2, int *psum, int *pdiff){
    *psum = num1 + num2;
    *pdiff = num1 - num2;
    return;
}

int main(int argc, const char * argv[]) {
    int num1 = 10, num2 = 5, sum = 0, diff = 0;
    getSumDiff(num1, num2, &sum, &diff);
    printf("sum = %d, diff = %d\n", sum, diff);
    return 0;
}
