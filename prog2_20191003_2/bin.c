/*-----------------------------+
プログラミング及び演習II 第2回
問題 B-3
unsigned int型の値xを2進数で表示
する関数printbin(int x)と、それを
呼び出すmain()関数からなるプログラム
を作りなさい
+-----------------------------*/

#include <stdio.h>

int searchMostLeft(int x);
void printbin(int x);
void printbin_sub(int x, int i);

int main(int argc, const char* argv[])
{
  unsigned int x; // 入力値を格納する変数

  printf("x? ");
  scanf("%d", &x);

  printbin(x);

  return(0);
}

//--------------------------------
//1となる最も左のビット数を求める関数
//--------------------------------
int searchMostLeft(int x)
{
  int i;        // カウンタ変数
  int rec = 0;  // 返り値を随時更新する変数
  int mask = 1; // アンドマスク

  for(i = 1;i <= 32;i++){
    if((x & mask) != 0){
      rec = i;
    }
    mask <<= 1;
  }

  return(rec);
}

//--------------------------------
//xを2進数で表示する関数
//--------------------------------
void printbin(int x)
{
  int i;            // カウンタ変数
  int mostLeft = 0; // 1となる最も左のビット数

  mostLeft = searchMostLeft(x);

  for(int i = mostLeft;i > 0;i--){
    printbin_sub(x, i);
  }
  printf("\n");

  return;
}

//--------------------------------
//xのiビット目を表示する関数
//--------------------------------
void printbin_sub(int x, int i)
{
  printf("%d", (x >> (i - 1)) & 1);
  return;
}
