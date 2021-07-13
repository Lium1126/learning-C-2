//
//  main.c
//  prog03
//
//  Created by k19061kk on 2019/10/30.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------+
プログラミング及び演習II 第5回
問題3
授業資料11スライド目のプログラムをマジックナンバー
"3"を使わない方式に書き換えなさい
+----------------------------------------*/

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int i;
    char a[][5] = {"LISP", "C", "Ada"};
    char *p[]   = {"PAUL", "X", "MAC"};
    
    int size_a = (int)(sizeof(a) / sizeof(a[0]));
    int size_p = (int)(sizeof(p) / sizeof(p[0]));
    
    for(i = 0;i < size_a;i++){
        printf("a[%d] = \"%s\"\n", i, a[i]);
    }
    
    for(i = 0;i < size_p;i++){
        printf("p[%d] = \"%s\"\n", i, p[i]);
    }
    
    return 0;
}
