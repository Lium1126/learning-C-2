//
//  main.c
//  prog05
//
//  Created by k19061kk on 2019/10/30.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------------+
プログラミング及び演習II 第5回
問題5
char a[128] = "abc";
char b[128];
・文字列をコピーする関数strcpy()を使って文字列aを
 文字列bにコピーせよ
・コピーした結果を表示して確かめよ
+----------------------------------------*/


#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char a[128] = "abc";
    char b[128];
    
    /*---文字列をコピー---*/
    strcpy(b, a);
    
    /*---結果を表示---*/
    printf("a:%s\n", a);
    printf("b:%s\n", b);
    
    return 0;
}
