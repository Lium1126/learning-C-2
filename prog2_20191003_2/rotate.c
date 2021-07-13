/*--------------------------------+
プログラミング及び演習II 第2回
問題 B-4
符号なし整数xを右・左にnビット回転する
関数を作成せよ
+--------------------------------*/

#include <stdio.h>

int searchMostLeft(int x);
void printbin(int x);
void printbin_sub(int x, int i);
unsigned int rrotate(unsigned int x, int n);
unsigned int lrotate(unsigned int x, int n);

int main(int argc, const char* argv[])
{
  unsigned int x; // 入力値を格納する変数
  int n;          // nビット回転する
  unsigned int rotateR, rotateL;

  printf("x n? ");
  scanf("%d %d", &x, &n);

  printf("元の数値:");
  printbin(x);

  rotateR = rrotate(x, n);
  printf("右回転:");
  printbin(rotateR);

  rotateL = lrotate(x, n);
  printf("左回転:");
  printbin(rotateL);

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

//--------------------------------
//xをnビット右回転する
//--------------------------------
unsigned int rrotate(unsigned int x, int n)
{
  unsigned int temp1, temp2;
  temp1 = temp2 = x;
  temp1 >>= n;
  temp2 <<= (32 - n);
  return(temp1 | temp2);
}

//--------------------------------
//xをnビット左回転する
//--------------------------------
unsigned int lrotate(unsigned int x, int n)
{
  unsigned int temp1, temp2;
  temp1 = temp2 = x;
  temp1 <<= n;
  temp2 >>= (32 - n);
  return(temp1 | temp2);
}
