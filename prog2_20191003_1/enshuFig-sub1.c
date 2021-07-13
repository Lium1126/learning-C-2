/*-------------------------+
プログラミング及び演習II 第2回
分割コンパイルの練習
---------------------------*/

#include <stdio.h>

int draw_figure(int size)
{
  int i, j; // カウンタ変数

  for(i = 0;i < size;i++){
    for(j = 0;j < size;j++){
      printf("*");
    }
    printf("\n");
  }

  return(0);
}
