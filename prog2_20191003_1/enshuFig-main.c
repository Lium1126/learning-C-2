/*-------------------------+
プログラミング及び演習II 第2回
分割コンパイルの練習
---------------------------*/

#include <stdio.h>

extern int draw_figure(int n);

int main(int argc, const char* argv[])
{
  int size;

  printf("Size of figure? ");
  scanf("%d", &size);

  draw_figure(size);

  return(0);
}
