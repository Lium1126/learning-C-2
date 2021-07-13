/*-------------------------+
プログラミング及び演習II 第2回
分割コンパイルの練習
---------------------------*/

#include <stdio.h>

// プロトタイプ宣言
// 「extern」とは「別ファイルに定義本体があるよ」という意味
extern int sub(int);

int b;

int main(int argc, const char* argv[])
{
  b = 10;
  printf("%d\n", sub(5)); // 別ファイルで定義される関数 sub を呼ぶ
  return(0);
}
