//
//  main.c
//  prog06
//
//  Created by k19061kk on 2019/12/18.
//  Copyright © 2019 AIT. All rights reserved.
//

/*---------------------------------------------+
 プログラミング及び演習II 第12回
 問題6
 array_testの各要素に対して、array_learnを用いた1-NN
 を行い、推定結果を出力せよ.
 +---------------------------------------------*/

//インクルード=====================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

//定義============================================================
//マクロ--------------------------------------------------
#define CLASS_LEN 64
#define DATA_MAX 200
#define LINE_LEN 100
#define LEARN_MAX (DATA_MAX * 4 / 5)
#define TEST_MAX (DATA_MAX * 1 / 5)
#define IRIS_SETOSA 0
#define IRIS_VERSICOLOR 1
#define IRIS_VIRGINICA 2


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
double getSepalLength(Iris iris);                     // irisからsepal_lengthを取得する
void setSepalLength(Iris *iris, double length);       // irisのsepal_lengthを設定する
double getSepalWidth(Iris iris);                      // irisからsepal_wigthを取得する
void setSepalWidth(Iris *iris, double width);         // irisのsepal_widthを設定する
double getPetalLength(Iris iris);                     // irisからpetal_lengthを取得する
void setPetalLength(Iris *iris, double length);       // irisのpetal_lengthを設定する
double getPetalWidth(Iris iris);                      // irisからpetal_widthを取得する
void setPetalWidth(Iris *iris, double width);         // irisのpetal_widthを設定する
char* getClass(Iris *iris);                           // irisからclassを取得する
void setClass(Iris *iris, char *class);               // irisのclassを設定する
void setParameter(Iris *iris, double sepal_length, double sepal_width, double petal_length, double petal_width, char *class);   // irisにパラメータを設定する

//その他の関数
void shuffleArray(Iris *a, int n);                    // 要素数n(添字は0~n-1)の配列aをシャッフルする
void swapPtr(Iris *a, Iris *b);                       // aとbを入れ替える(shuffleArrayのサブ関数)
int presumeClass(Iris iris, Iris *dataset, int num);  // irisとデータセットを比べ、クラスを推定する
double seekDist(Iris iris1, Iris iris2);              // 二つのIris型変数の距離を求める

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
    int estimated_result;                                     // 推定結果を格納する変数
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
    
    /*---array_testに対して、1-NNを行い、推定結果を出力---*/
    // 出力形式の説明
    printf("<出力形式>\n");
    printf("推定データ: 正しいクラス 推定結果\n");
    printf("-----\n");
    
    // 1-NNを行い、推定結果を出力
    for (i = 0;i < size_test;i++) {
        estimated_result = presumeClass(array_test[i], array_learn, size_learn);
        printf("array_test[%2d]: %-15s ", i, getClass(&array_test[i]));
        if (estimated_result == IRIS_SETOSA) {
            printf("Iris-setosa\n");
        } else if (estimated_result == IRIS_VERSICOLOR) {
            printf("Iris-versicolor\n");
        } else if (estimated_result == IRIS_VIRGINICA) {
            printf("Iris-virginica\n");
        }
    }
    
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

//その他の関数---------------------------------------------
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

//-------------------------------------------------
//機能:irisのクラスをデータセットとの距離から推定する
//    プロットされたデータセットとの1-NNでクラスを推定する
//引数 Iris iris    : クラスを調べる対象
//    Iris *dataset: データセット
//    int num      : データセットのデータ数
//返り値:推定した結果を定数で返す。推定結果が
//      Iris-setosaの場合はIRIS_SETOSAを、
//      Iris-versicolorの場合はIRIS_VERSICOLORを、
//      Iris-virginicaの場合はIRIS_VIRGINICAを返す。
//-------------------------------------------------
int presumeClass(Iris iris, Iris *dataset, int num) {
    double dist;                // irisとdataset[i]との距離
    int i;                      // カウンタ変数
    double min_dist = DBL_MAX;  // distの暫定最小値
    int ret = 0;                // 返り値
    
    for (i = 0;i < num;i++) {
        dist = seekDist(iris, dataset[i]);
        
        if (dist < min_dist) {
            min_dist  = dist;
            if (strcmp(getClass(&dataset[i]), "Iris-setosa") == 0) {
                ret = IRIS_SETOSA;
            } else if(strcmp(getClass(&dataset[i]), "Iris-versicolor") == 0) {
                ret = IRIS_VERSICOLOR;
            } else if(strcmp(getClass(&dataset[i]), "Iris-virginica") == 0) {
                ret = IRIS_VIRGINICA;
            }
        }
    }
    
    return(ret);
}

//-------------------------------------------------
//機能:2つのIris型変数iris1,iris2のユークリッド距離を求める
//引数 Iris iris1:---+
//    Iris iris2:---+--距離を求める二つの変数
//返り値:iris1とiris2のユークリッド距離を返す
//-------------------------------------------------
double seekDist(Iris iris1, Iris iris2) {
    double dist = 0;
    
    dist += pow(getSepalLength(iris1) - getSepalLength(iris2), 2.0);
    dist += pow(getSepalWidth(iris1) - getSepalWidth(iris2), 2.0);
    dist += pow(getPetalLength(iris1) - getPetalLength(iris2), 2.0);
    dist += pow(getPetalWidth(iris1) - getPetalWidth(iris2), 2.0);
    dist = sqrt(dist);
    
    return(dist);
}
