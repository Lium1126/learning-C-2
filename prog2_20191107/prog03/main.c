//
//  main.c
//  prog03
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-------------------------------------+
プログラミング及び演習II 第6回
問題3
(100,10)から(200,50)までのユークリッド距離を
求めよ
---------------------------------------*/

#include <stdio.h>
#include <math.h>

int main(int argc, const char * argv[]) {
    int x1 = 100; // ---+
    int y1 = 10;  // ---+--1つ目の点の座標
    int x2 = 200; // ---+
    int y2 = 50;  // ---+--2つ目の点の座標
    double dist;  // 2点間のユークリッド距離
    
    /*---2点間のユークリッド距離を計算---*/
    dist = sqrt(pow((double)(x1 - x2), 2.0) + pow((double)(y1 - y2), 2.0));
    
    /*---出力---*/
    printf("(%d,%d)と(%d,%d)のユークリッド距離は %f です\n", x1, y1, x2, y2, dist);
    
    return 0;
}
