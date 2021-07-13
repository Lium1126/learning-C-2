//
//  main.c
//  prog02
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------+
プログラミング及び演習II 第6回
問題2
int r=10;
半径rとした時の円の面積と円周の長さを求めよ
-----------------------------------*/

#include <stdio.h>
#include <math.h>

int main(int argc, const char * argv[]) {
    int r = 10;           // 半径
    double circumference; // 円周
    double area;          // 面積
    
    circumference = 2.0 * (double)r * M_PI; // 円周を計算
    area = pow((double)r, 2.0) * M_PI;      // 面積を計算
    
    printf("面積:%f 円周:%f\n", circumference, area);
    return 0;
}
