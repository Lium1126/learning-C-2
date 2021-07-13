/*-------------------------------+
プログラミング及び演習II 第2回
応用演習 Y
ビット演算を行うプログラムを作りなさい
関数 setBit8(), resetBit8(),
printbin8() は ouyouY-sub.c に定義
する
+--------------------------------*/

#include <stdio.h>

extern int setBit8(unsigned char bits, int i);   // bitsの下からi(0~7)ビット目を1にする
extern int resetBit8(unsigned char bits, int i); // bitsの下からi(0~7)ビット目を0にする
extern int printbin8(unsigned char x);           // 10進数xを8ビットの2進数で表示する

int main(int argc, const char* argv[])
{
  unsigned char bits = 123; // 123_10 = (01111011)_2
  bits = resetBit8(setBit8(bits, 7), 3);
  printf("実行結果: ");
  printbin8(bits);

  return(0);
}
