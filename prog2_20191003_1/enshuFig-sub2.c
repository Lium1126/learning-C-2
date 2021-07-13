/*-------------------------+
プログラミング及び演習II 第2回
分割コンパイルの練習
---------------------------*/

#include <stdio.h>

int draw_figure(int size)
{
  int i, j; // カウンタ変数

  for(i = 1;i <= size;i++){
    for(j = 1;j <= i;j++){
      printf("*");
    }
    printf("\n");
  }

  return(0);
}
