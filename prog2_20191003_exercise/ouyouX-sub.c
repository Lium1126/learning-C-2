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

long long reverse(long long n); // nを左右反転する
void printJap(long long n);     // 10進数一桁を漢字で表示する

//-----------------------------------
//機能  :nを感じで読み上げる
//関数名:yomiage
//引数 long long n:読み上げる10進数
//返り値:なし
//-----------------------------------
void yomiage(long long n)
{
  int numOfDigit = 0;     // nの桁数を格納する変数
  long long temp;         // 作業用変数
  long long reverseN = 0; // nを10進数で左右反転したもの
  int i;                  // カウンタ変数

  /*---桁数を求める---*/
  temp = n;
  do{
    numOfDigit++;
    temp /= 10;
  }while(temp > 0);

  /*---読み上げ---*/
  if(numOfDigit >= 13){
    printf("読めません");
  }else if(n == 0){
    printf("零");
  }else{
    reverseN = reverse(n); // nの左右反転したものを準備する
    for(i = numOfDigit;i >= 1;i--, reverseN /= 10){
      /*---数を表示---*/
      temp = (reverseN % 10); // 1桁抽出
      if(temp != 1 || (temp == 1 && i % 4 == 1)){
        printJap(temp);
      }

      /*---桁を表示---*/
      if(temp != 0){
        switch(i % 4){
          case 2: printf("十"); break;
          case 3: printf("百"); break;
          case 0: printf("千"); break;
        }
      }

      /*---万/億を表示---*/
      if(i % 4 == 1){
        if(i / 4 == 1 && !(reverseN == 0 && numOfDigit >= 9)){
          printf("万");
        }else if(i / 4 == 2){
          printf("億");
        }
      }

    }
  }

  return;
}

//-----------------------------------
//機能  :nを10進数で左右反転したものを返す
//関数名:reverse
//引数 long long n:左右反転する対象の
//                10進数
//返り値:nを10進数として左右反転した値
//      例)123->321
//-----------------------------------
long long reverse(long long n)
{
  long long temp = 0; // nの反転したものを格納する変数

  /*---反転する---*/
  while(n > 0){
    temp *= 10;
    temp += (n % 10);
    n /= 10;
  }

  return(temp);
}

//-----------------------------------
//機能  :一桁の整数n(0以外)を漢字で表示する
//関数名:printJap
//引数 long long n:感じで表示する一桁の
//                10進数
//返り値:なし
//-----------------------------------
void printJap(long long n)
{
  switch(n){
    case 1: printf("一"); break;
    case 2: printf("二"); break;
    case 3: printf("三"); break;
    case 4: printf("四"); break;
    case 5: printf("五"); break;
    case 6: printf("六"); break;
    case 7: printf("七"); break;
    case 8: printf("八"); break;
    case 9: printf("九"); break;
  }

  return;
}
