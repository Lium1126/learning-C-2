/*-------------------------------+
プログラミング及び演習II 第2回
応用演習 X
0以上の整数を入力したときに、その読み方
を表示する関数 yomiage() を作りなさい
ただし、10^13以上の大きな入力値に対して
は「読めません」と答えてよい
yomiage()はouyouX-sub.cに定義する
+--------------------------------*/

#include <stdio.h>
#include <stdlib.h>

extern void yomiage(long long n);

int main(int argc, const char* argv[])
{
  char ss[256]; // 入力用の文字列配列
  long long n;  // 入力値を整数として扱うための変数

  /*---input---*/
  printf("Number ? ");
  fgets(ss, sizeof(ss), stdin); // 入力を文字列で受け付ける
  n = atoll(ss);                // ssを数値に変換

  /*---output---*/
  if(n < 0){
    printf("不正な入力です\n");
  }else{
    printf("%lld = ", n);
    yomiage(n);
    printf("\n");
  }

  return(0);
}
