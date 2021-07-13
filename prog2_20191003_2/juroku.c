/*-----------------------------+
プログラミング及び演習II 第2回
問題 B-1
キーボード入力された1~255までの数値
(unsigned int型の10進数)を16進数
で表示するプログラムを作れ
+-----------------------------*/

#include <stdio.h>

#define RADIX 16

void print16(int n);

int main(int argc, const char* argv[])
{
  unsigned int n; // 入力値を格納する変数

  printf("1~255の整数値を入力してください: ");
  scanf("%d", &n);

  if(n < 1 || 255 < n){
    printf("入力値が範囲外です");
  }else{
    print16(n / RADIX);
    print16(n % RADIX);
    printf("\n");
  }

  return(0);
}

//--------------------------------
//0~15の10進数nを16進数で表示する関数
//--------------------------------
void print16(int n)
{
  if(n <= 9){
    printf("%d", n);
  }else{
    switch (n) {
      case 10: printf("A"); break;
      case 11: printf("B"); break;
      case 12: printf("C"); break;
      case 13: printf("D"); break;
      case 14: printf("E"); break;
      case 15: printf("F"); break;
    }
  }

  return;
}
