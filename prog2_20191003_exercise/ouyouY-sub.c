/*-------------------------------+
プログラミング及び演習II 第2回
応用演習 Y
ビット演算を行うプログラムを作りなさい
関数 setBit8(), resetBit8(),
printbin8() は ouyouY-sub.c に定義
する
+--------------------------------*/

#include <stdio.h>

// サブ関数群の宣言=======================================
unsigned char lrotate(unsigned char x, int n);
int searchMostLeft(int x);
void printbin_sub(int x, int i);

// 問題で定められた関数===================================
//-------------------------------------------------
//機能  :8ビット2進数bitsの下からi(0~7)ビット目を1にする
//関数名:setBit8
//引数 unsigned char bits:ビット操作をする値
//    int i             :1にするビット(0~7)
//返り値:ビット操作をした結果をint型で返す
//-------------------------------------------------
int setBit8(unsigned char bits, int i)
{
  int mask = 1; // マスク

  if(0 <= i && i <= 7){
    mask = lrotate(mask, i);
    bits |= mask;
  }

  return(bits);
}

//-------------------------------------------------
//機能  :8ビット2進数bitsの下からi(0~7)ビット目を0にする
//関数名:resetBit8
//引数 unsigned char bits:ビット操作をする値
//    int i             :0にするビット(0~7)
//返り値:ビット操作をした結果をint型で返す
//-------------------------------------------------
int resetBit8(unsigned char bits, int i)
{
  int mask = 0xFE; // アンドマスク(0ビット目のみ0)

  if(0 <= i && i <= 7){
    mask = lrotate(mask, i);
    bits &= mask;
  }

  return(bits);
}

//-------------------------------------------------
//機能  :10進数xを最大8ビットの2進数で表示する
//関数名:printbin8
//引数 unsigned char x:2進数として表示する8ビットの値
//-------------------------------------------------
int printbin8(unsigned char x)
{
  int i;            // カウンタ変数
  int mostLeft = 0; // 1となる最も左のビット数

  mostLeft = searchMostLeft(x);

  if(mostLeft == 0){
      printf("0\n");
  }else{
    for(i = mostLeft;i > 0;i--){
      printbin_sub(x, i);
    }
    printf("\n");
  }

  return(0);
}

// サブ関数群の本体=======================================
//-------------------------------------------------
//機能  :8ビットの値xをnビット左回転する
//関数名:lrotate
//引数 unsigned char x:左回転する対象の8ビット2進数
//    int n          :左回転させるビット数
//返り値:xをnビット左回転させた値を返す
//-------------------------------------------------
unsigned char lrotate(unsigned char x, int n)
{
  unsigned char temp1, temp2;
  temp1 = temp2 = x;
  temp1 <<= n;
  temp2 >>= (8 - n);
  return(temp1 | temp2);
}

//------------------------------------------------
//機能  :1となる最も左のビット数を求める関数
//関数名:searchMostLeft
//引数 int x:1となる最も左のビットを探索する2進数
//返り値:求めたビット数
//------------------------------------------------
int searchMostLeft(int x)
{
  int i;        // カウンタ変数
  int rec = 0;  // 返り値を随時更新する変数
  int mask = 1; // アンドマスク

  for(i = 1;i <= 8;i++){
    if((x & mask) != 0){
      rec = i;
    }
    mask <<= 1;
  }

  return(rec);
}

//----------------------------------------------
//機能  :xのiビット目を表示する関数
//関数名:printbin_sub
//引数 int x:iビット目を表示する対象の2進数
//    int i:表示するビット
//返り値:なし
//----------------------------------------------
void printbin_sub(int x, int i)
{
  printf("%d", (x >> (i - 1)) & 1);
  return;
}
