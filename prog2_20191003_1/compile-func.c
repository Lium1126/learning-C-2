/*-------------------------+
プログラミング及び演習II 第2回
分割コンパイルの練習
---------------------------*/

// 「extern int b;」は
// 「int 型 変数 b は別ファイルに書いてある定義を使ってね」という意味
extern int b;

int sub(int a)
{
  return(a * b);
}
