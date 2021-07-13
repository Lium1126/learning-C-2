//
//  main.c
//  exercise1
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*------------------------------+
 プログラミング及び演習II 第1回
 課題1
 円の半径を入力し、円周と面積を表示する
 -------------------------------*/

#include <stdio.h>
#include <math.h>

int main(int argc, const char * argv[]) {
    double radius; // 円の半径を格納する変数
    
    /*---入力---*/
    printf("円の半径を入力してください: ");
    scanf("%lf", &radius);
    
    /*---出力---*/
    printf("円周は %f です\n", 2.0 * radius * M_PI);
    printf("面積は %f です\n", pow(radius, 2.0) * M_PI);
    
    return 0;
}
