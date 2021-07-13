//
//  main.c
//  exercise2
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*---------------------------------+
プログラミング及び演習II 第1回
課題2
sinの値を10度ずつ0度から360度まで出力する
-----------------------------------*/

#include <stdio.h>
#include <math.h>

#define LIMIT 360
#define DIFF 10

int main(int argc, const char * argv[]) {
    int angle;     // 現在の角度(度数法)
    double radian; // sin()に渡す角度(弧度法)
    
    for(angle = 0;angle <= LIMIT;angle += DIFF){
        radian = (angle * M_PI) / 180.0;  // 度数法から弧度法に変換
        printf("x:%3d, sin(x):%f\n", angle, sin(radian));
    }
    
    return 0;
}
