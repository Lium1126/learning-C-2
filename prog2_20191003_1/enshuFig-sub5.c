/*-------------------------+
プログラミング及び演習II 第2回
分割コンパイルの練習
---------------------------*/

#include <stdio.h>

int draw_figure(int size){
  int i, j; // カウンタ変数

  for(i = size;i > 0;i--){
    for(j = 1;j <= i;j++){
      if(i == j){
        printf("*");
      }else{
        printf(" ");
      }
    }
    printf("\n");
  }

  return(0);
}