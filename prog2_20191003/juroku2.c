/*-----------------------------+
プログラミング及び演習II 第2回
問題 B-2
問題B-1を拡張し、より大きな整数に対応
させよ
+-----------------------------*/

#include <stdio.h>

void print16(int n);
char change16(int n);

int main(int argc, const char* argv[])
{
  unsigned int n; // 入力値を格納する変数

  printf("整数値を入力してください: ");
  scanf("%d", &n);

  print16(n);

  return(0);
}

//-----------------------------
//10進数nを16進数で表示する
//-----------------------------
void print16(int n)
{
  int i;       // カウンタ変数
  char str[8]; // 変換した16進数を格納する配列

  for(i = 7;i >= 0;i--){
      str[i] = change16(n % 16);
      n /= 16;
  }

  printf("%s\n", str);

  return;
}

//-----------------------------
//0~15の10進数nを16進数に変換する
//-----------------------------
char change16(int n)
{
  if(n <= 9){
    return('0' + n);
  }else{
    switch (n) {
      case 10: return('A');
      case 11: return('B');
      case 12: return('C');
      case 13: return('D');
      case 14: return('E');
      case 15: return('F');
    }
  }

  return('0');
}
