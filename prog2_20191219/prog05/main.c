//
//  main.c
//  prog05
//
//  Created by k19061kk on 2019/12/18.
//  Copyright © 2019 AIT. All rights reserved.
//

/*--------------------------------------------+
 プログラミング及び演習II 第12回
 問題5
 Irisデータをarray_all配列のすべて読み込む.
 ランダムに並び替える.
 そのうち4/5をarray_learnに入れる.
 残りの1/5をarray_testに入れる.
 +--------------------------------------------*/

//インクルード=====================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//定義============================================================
//マクロ--------------------------------------------------
#define CLASS_LEN 64
#define DATA_MAX 200
#define LINE_LEN 100
#define LEARN_MAX (DATA_MAX * 4 / 5)
#define TEST_MAX (DATA_MAX * 1 / 5)

//構造体--------------------------------------------------
typedef struct iris {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char class[CLASS_LEN];
} Iris;

//関数プロトタイプ宣言---------------------------------------
//基本操作関数
double getSepalLength(Iris iris);                // irisからsepal_lengthを取得する
void setSepalLength(Iris *iris, double length);  // irisのsepal_lengthを設定する
double getSepalWidth(Iris iris);                 // irisからsepal_wigthを取得する
void setSepalWidth(Iris *iris, double width);    // irisのsepal_widthを設定する
double getPetalLength(Iris iris);                // irisからpetal_lengthを取得する
void setPetalLength(Iris *iris, double length);  // irisのpetal_lengthを設定する
double getPetalWidth(Iris iris);                 // irisからpetal_widthを取得する
void setPetalWidth(Iris *iris, double width);    // irisのpetal_widthを設定する
char* getClass(Iris *iris);                      // irisからclassを取得する
void setClass(Iris *iris, char *class);          // irisのclassを設定する
void setParameter(Iris *iris, double sepal_length, double sepal_width, double petal_length, double petal_width, char *class);   // irisにパラメータを設定する

//操作関数
void printIris(Iris *iris, int num);             // iris配列の内容を出力する

//その他の関数
int seekDigit(int n);                            // nの桁数を求める(printIrisのサブ関数)
void shuffleArray(Iris *a, int n);               // 要素数n(添字は0~n-1)の配列aをシャッフルする
void swapPtr(Iris *a, Iris *b);                  // aとbを入れ替える(shuffleArrayのサブ関数)

//関数群===========================================================
//main()関数----------------------------------------------
int main(int argc, const char * argv[]) {
    Iris array_all[DATA_MAX];                                 // データすべてを格納する構造体の配列
    Iris array_learn[LEARN_MAX];                              // 学習用データ
    Iris array_test[TEST_MAX];                                // 推定対象データ
    double sepalLegnth, sepalWidth, petalLength, petalWidth;  // 各パラメータ
    char class[CLASS_LEN];                                    // セットするクラス名
    char line[LINE_LEN];                                      // ファイル入力を一行受け付ける文字配列
    int cnt;                                                  // カウンタ変数(ファイル入力後はarray_allの要素数)
    int i, j;                                                 // カウンタ変数
    int size_learn, size_test;                                // それぞれarray_learn,array_testの要素数
    FILE *fp;                                                 // ファイルポインタ
    
    /*---ファイルを開く---*/
    fp = fopen("iris.data", "r");
    if (fp == NULL) {
        fprintf(stderr, "Can not open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---ファイルの各行からデータを入力---*/
    cnt = 0;
    while (fgets(line, LINE_LEN, fp) != NULL) {
        /*---入力文字列から各パラメータに分割---*/
        sscanf(line, "%lf,%lf,%lf,%lf,%s", &sepalLegnth, &sepalWidth, &petalLength, &petalWidth, class);
        
        /*---各パラメータをiris[cnt]にセット---*/
        setParameter(&array_all[cnt], sepalLegnth, sepalWidth, petalLength, petalWidth, class);
        cnt++;
    }
    
    /*---ファイルを閉じる---*/
    fclose(fp);
    
    /*---ランダムに並び替える---*/
    shuffleArray(array_all, cnt);
    
    /*---array_learn,array_testの要素数を求める---*/
    size_learn = cnt * 4 / 5;
    size_test = cnt / 5;
    
    /*---array_allの4/5をarray_learnに格納する---*/
    for (i = 0;i < size_learn;i++) {
        array_learn[i] = array_all[i];
    }
    
    /*---残っているarray-allの1/5をarray_testに格納する---*/
    for (j = 0;j < size_test;j++) {
        array_test[j] = array_all[i + j];
    }
    
    /*---格納した内容を出力----*/
    // 出力形式の説明
    printf("<format>\n");
    printf("index: sepal_length, sepal_width, petal_length, petal_width, class\n");
    
    // array_learnの内容を表示
    printf("-----array_learn-----\n");
    printIris(array_learn, size_learn);
    
    // array_testの内容を表示
    printf("-----array_test-----\n");
    printIris(array_test, size_test);
    
    return 0;
}

//基本操作関数---------------------------------------------
//-------------------------------------------------
//機能:irisのsepal_lengthを取得する
//引数 Iris iris: sepal_lengthを取得する対象
//返り値:irisのsepal_lengthの値
//-------------------------------------------------
double getSepalLength(Iris iris) {
    return(iris.sepal_length);
}

//-------------------------------------------------
//機能:irisのsepal_lengthを設定する
//引数 Iris iris    : sepal_lengthを設定する対象
//    double length: sepal_lengthに設定する値
//返り値:なし
//-------------------------------------------------
void setSepalLength(Iris *iris, double length) {
    iris -> sepal_length = length;
    return;
}

//-------------------------------------------------
//機能:irisのsepal_widthを取得する
//引数 Iris iris: sepal_widthを取得する対象
//返り値:irisのsepal_widthの値
//-------------------------------------------------
double getSepalWidth(Iris iris) {
    return(iris.sepal_width);
}

//-------------------------------------------------
//機能:irisのsepal_widthを設定する
//引数 Iris iris    : sepal_widthを設定する対象
//    double length: sepal_widthに設定する値
//返り値:なし
//-------------------------------------------------
void setSepalWidth(Iris *iris, double width) {
    iris -> sepal_width = width;
}

//-------------------------------------------------
//機能:irisのpetal_lengthを取得する
//引数 Iris iris: petal_lengthを取得する対象
//返り値:irisのpetal_lengthの値
//-------------------------------------------------
double getPetalLength(Iris iris) {
    return(iris.petal_length);
}

//-------------------------------------------------
//機能:irisのpetal_lengthを設定する
//引数 Iris iris    : petal_lengthを設定する対象
//    double length: petal_lengthに設定する値
//返り値:なし
//-------------------------------------------------
void setPetalLength(Iris *iris, double length) {
    iris -> petal_length = length;
    return;
}

//-------------------------------------------------
//機能:irisのpetal_widthを取得する
//引数 Iris iris: petal_widthを取得する対象
//返り値:irisのpetal_widthの値
//-------------------------------------------------
double getPetalWidth(Iris iris) {
    return(iris.petal_width);
}

//-------------------------------------------------
//機能:irisのpetal_widthを設定する
//引数 Iris iris    : petal_widthを設定する対象
//    double length: petal_widthに設定する値
//返り値:なし
//-------------------------------------------------
void setPetalWidth(Iris *iris, double width) {
    iris -> petal_width = width;
    return;
}

//-------------------------------------------------
//機能:irisのclassを取得する
//引数 Iris *iris: classを取得する対象へのポインタ
//返り値:irisのclassを文字列で返す
//-------------------------------------------------
char* getClass(Iris *iris) {
    return(iris -> class);
}

//-------------------------------------------------
//機能:irisのclassを設定する
//引数 Iris iris  : classを設定する対象へのポインタ
//    char *class: classに設定する文字列
//返り値:なし
//-------------------------------------------------
void setClass(Iris *iris, char *class) {
    strcpy(iris -> class, class);
    return;
}

//-------------------------------------------------
//機能:irisの各パラメータを設定する
//引数 Iris iris          : パラメータを設定する対象
//    double sepal_length: sepal_lengthに設定する値
//    double sepal_width : sepal_widthに設定する値
//    double petal_length: petal_lengthに設定する値
//    double petal_width : petal_widthに設定する値
//    char class         : classに設定する文字列
//返り値:なし
//-------------------------------------------------
void setParameter(Iris *iris, double sepal_length, double sepal_width, double petal_length, double petal_width, char *class) {
    setSepalLength(iris, sepal_length);
    setSepalWidth(iris, sepal_width);
    setPetalLength(iris, petal_length);
    setPetalWidth(iris, petal_width);
    setClass(iris, class);
    return;
}

//操作関数-------------------------------------------------
//-------------------------------------------------
//機能:配列irisの内容を標準出力に出力する
//引数 Iris iris: 内容を出力するIris型配列
//    int num  : 配列の要素数
//返り値:なし
//-------------------------------------------------
void printIris(Iris *iris, int num) {
    int i, j;  // カウンタ変数
    
    /*---配列の内容を出力---*/
    for (i = 0;i < num;i++) {
        // 見やすいように空白で行頭を調整
        for (j = 0;j < seekDigit(num) - seekDigit(i);j++) {
            printf(" ");
        }
        printf("%d: ", i);
        printf("%.1f, ", getSepalLength(iris[i]));
        printf("%.1f, ", getSepalWidth(iris[i]));
        printf("%.1f, ", getPetalLength(iris[i]));
        printf("%.1f, ", getPetalWidth(iris[i]));
        printf("%s\n", getClass(&iris[i]));
    }
    
    return;
}

//その他の関数---------------------------------------------
//-------------------------------------------------
//機能:整数nの桁数を求める
//引数 int n: 桁数を求める対象の整数値
//返り値:nの桁数
//-------------------------------------------------
int seekDigit(int n) {
    int i;  // カウンタ変数
    
    /*---前処理---*/
    i = 0;
    n = abs(n);
    
    /*---nの桁数を求める---*/
    do {
        i++;
        n /= 10;
    } while(n != 0);
    
    return(i);
}

//----------------------------------------------
//機能:要素数n(添字は0~n-1)の配列aをシャッフルする
//引数 Iris *a:シャッフルする対象の配列
//    int n  :配列aの要素数
//返り値:なし
//----------------------------------------------
void shuffleArray(Iris *a, int n) {
    int i;       // カウンタ変数
    int j;       // ランダムに入れ替える要素の添字
    
    /*---rand関数のシード値を変更する---*/
    srand((unsigned)time(NULL));
    
    /*---aをシャッフルする---*/
    for (i = n - 1;i >= 1;i--) {     // iをn-1から1まで減少させながら、以下を実行する
        j = rand() % (i + 1);       // jに0以上i以下のランダムな整数を代入する
        if (i != j) {
            swapPtr(&a[i], &a[j]);  // a[j]とa[i]を交換する
        }
    }
    
    return;
}

//---------------------------------------------
//機能:aとbを入れ替える
//引数 Iris a:---+
//    Iris b:---+--入れ替える対象へのポインタ
//返り値:なし
//---------------------------------------------
void swapPtr(Iris *a, Iris *b) {
    Iris temp;    // 作業用変数
    
    /*---aとbを入れ替える---*/
    temp = *a;
    *a = *b;
    *b = temp;
    
    return;
}
