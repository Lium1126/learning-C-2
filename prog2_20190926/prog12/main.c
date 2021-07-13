//
//  main.c
//  prog12
//
//  Created by k19061kk on 2019/09/26.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------------+
プログラミング及び演習II 第1回
問題12
身長体重をユーザーに入力させてBMIを計算し、肥満度を出力する
 プログラムを作成しなさい
------------------------------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int height;           // 身長
    int weight;           // 体重
    double bmi;           // BMI
    double HeightToMeter; // 身長をメートル単位に正す際に使用する作業用変数
    
    /*---入力---*/
    // 身長・体重のどちらかが0以下の間入力を待ち続ける
    do{
        printf("身長を入力してください(cm): ");
        scanf("%d", &height);
        printf("体重を入力してください(kg): ");
        scanf("%d", &weight);
        if(height <= 0 || weight <= 0){
            printf("適切な値を入力してください\n");
        }
    }while(height <= 0 || weight <= 0);
    
    /*---BMIを計算し、出力---*/
    HeightToMeter = (double)height / 100.0;
    bmi = (double)weight / (HeightToMeter * HeightToMeter);
    printf("BMIは %f です\n", bmi);
    
    /*---肥満度を判定し、出力---*/
    printf("肥満度は ");
    if(bmi < 18.5){
        printf("やせ");
    }else if(bmi < 25.0){
        printf("標準");
    }else if(bmi < 30.0){
        printf("肥満");
    }else{
        printf("高度肥満");
    }
    printf(" です\n");
    
    return(0);
}
