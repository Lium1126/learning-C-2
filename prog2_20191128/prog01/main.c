//
//  main.c
//  prog01
//
//  Created by k19061kk on 2019/11/27.
//  Copyright © 2019 AIT. All rights reserved.
//

/*-----------------------------------+
 プログラミング及び演習II 第9回
 問題1
 学生を一つの構造体で定義する。
    要素は名前、年齢、学籍番号、学年(1~4)
 3人の学生を初期化し、各学生の情報を表示せよ。
 +-----------------------------------*/

//インクルード=====================================================
#include <stdio.h>

//定義============================================================
//マクロ--------------------------------------------------
#define NAME_LEN 64
#define STU_NUM_LEN 64

//構造体--------------------------------------------------
struct student {
    char name[NAME_LEN];           // 名前
    int age;                       // 年齢
    char studentNum[STU_NUM_LEN];  // 学籍番号
    int grade;                     // 学年
};

//関数群===========================================================
//main()関数----------------------------------------------
int main(int argc, const char * argv[]) {
    struct student student1 = {"Suzuki", 19, "K19061", 1};
    struct student student2 = {"Tanaka", 18, "K19065", 1};
    struct student student3 = {"Satou", 21, "K17052", 3};
    
    printf("student1-----------------------\n");
    printf("名前   : %s\n", student1.name);
    printf("年齢   : %d\n", student1.age);
    printf("学籍番号: %s\n", student1.studentNum);
    printf("学年   : %d\n", student1.grade);
    
    printf("student2-----------------------\n");
    printf("名前   : %s\n", student2.name);
    printf("年齢   : %d\n", student2.age);
    printf("学籍番号: %s\n", student2.studentNum);
    printf("学年   : %d\n", student2.grade);
    
    printf("student3-----------------------\n");
    printf("名前   : %s\n", student3.name);
    printf("年齢   : %d\n", student3.age);
    printf("学籍番号: %s\n", student3.studentNum);
    printf("学年   : %d\n", student3.grade);
    
    return 0;
}
