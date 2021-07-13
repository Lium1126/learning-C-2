//
//  main.c
//  prog07
//
//  Created by k19061kk on 2019/12/11.
//  Copyright © 2019 AIT. All rights reserved.
//

/*---------------------------------+
プログラミング及び演習II
第11回 問題7
1から100までを標準出力に出力するプログラム
を作成する。
リダイレクトを使ってnumber.txtに出力結果
を書き込め。
+---------------------------------*/

#include <stdio.h>

#define START 1
#define END 100

int main(int argc, const char * argv[]) {
    int i;   // カウンタ変数
    
    for(i = START;i <= END;i++) {
        printf("%d\n", i);
    }
    
    return 0;
}
