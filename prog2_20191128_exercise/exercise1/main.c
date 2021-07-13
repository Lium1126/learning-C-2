//
//  main.c
//  exercise1
//
//  Created by k19061kk on 2019/11/28.
//  Copyright © 2019 AIT. All rights reserved.
//

/*------------------------------------+
 プログラミング及び演習II 第9回
 課題
 以下の3つのサンプルがどのクラスに属しているか
 を推定するプログラムを作成せよ。
 問題7,8と違う方法で推定せよ。
    5.7, 4.0, 1.2, 0.2
    5.9, 2.9, 4.2, 1.5
    5.6, 2.8, 8.4, 2.0
 +------------------------------------*/

//インクルード=====================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

//定義============================================================
//マクロ--------------------------------------------------
#define CLASS_LEN 64
#define DATA_MAX 200
#define LINE_LEN 100
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

typedef struct point {
    double dist;            // 基準点からの距離
    char class[CLASS_LEN];  // クラス
} Point;   // 基準点からの距離とクラスを持つ構造体

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
char* getIrisClass(Iris *iris);                  // irisからclassを取得する
void setIrisClass(Iris *iris, char *class);      // irisのclassを設定する
void setParameter(Iris *iris, double sepal_length, double sepal_width, double petal_length, double petal_width, char *class);   // irisにパラメータを設定する
void initParameter(Iris *iris);                  // irisを初期化する
double getDist(Point point);                     // pointから基準点からの距離を取得する
void setDist(Point *point, double dist);         // pointの基準点からの距離を設定する
char* getPointClass(Point *point);               // pointからクラスを取得する
void setPointClass(Point *point, char *class);   // pointのクラスを設定する

//その他の関数
int presumeClass(Iris iris, Iris *dataset, int num);  // irisとデータセットを比べ、クラスを推定する
double seekDist(Iris iris1, Iris iris2);              // 二つのIris型変数の距離を求める
void swap(Point *p1, Point *p2);                      // 二つの点を入れ替える
void sort(Point *p1, Point *p2);                      // 二つの点を基準点からの距離をキーに昇順にする
void bubbleSort(Point *array, int num);               // 配列arrayを基準点からの距離をキーにソートする

//関数群===========================================================
//main()関数----------------------------------------------
int main(int argc, const char * argv[]) {
    Iris iris[DATA_MAX];                                      // パラメータをセットする構造体の配列
    double sepalLegnth, sepalWidth, petalLength, petalWidth;  // 各パラメータ
    char class[CLASS_LEN];                                    // セットするクラス名
    char line[LINE_LEN];                                      // ファイル入力を一行受け付ける文字配列
    int cnt, i;                                               // カウンタ変数
    int result;                                               // クラスの推定結果を格納する変数
    FILE *fp;                                                 // ファイルポインタ
    Iris sample[3];                                           // 問題に指定されたサンプルデータ
        
    /*---ファイルを開く---*/
    fp = fopen("iris.data", "r");
    if(fp == NULL){
        fprintf(stderr, "Can not open the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*---ファイルの各行からデータを入力---*/
    cnt = 0;
    while(fgets(line, LINE_LEN, fp) != NULL){
        /*---入力文字列から各パラメータに分割---*/
        sscanf(line, "%lf,%lf,%lf,%lf,%s", &sepalLegnth, &sepalWidth, &petalLength, &petalWidth, class);
        
        /*---各パラメータをirisにセット---*/
        setParameter(&iris[cnt], sepalLegnth, sepalWidth, petalLength, petalWidth, class);
        cnt++;
    }
    
    /*---サンプルデータを問題に指定されたように設定する---*/
    setParameter(&sample[0], 5.7, 4.0, 1.2, 0.2, "");
    setParameter(&sample[1], 5.9, 2.9, 4.2, 1.5, "");
    setParameter(&sample[2], 5.6, 2.8, 4.8, 2.0, "");
    
    /*---それぞれのサンプルについてクラスを推定---*/
    for(i = 0;i < 3;i++){
        result = presumeClass(sample[i], iris, cnt);
        printf("sample%d: ", i + 1);
        if(result == IRIS_SETOSA){
            printf("Iris-setosa\n");
        }else if(result == IRIS_VERSICOLOR){
            printf("Iris-versicolor\n");
        }else if(result == IRIS_VIRGINICA){
            printf("Iris-virginica\n");
        }
    }
    
    /*---ファイルの後処理---*/
    fclose(fp);
    
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
char* getIrisClass(Iris *iris) {
    return(iris -> class);
}

//-------------------------------------------------
//機能:irisのclassを設定する
//引数 Iris iris  : classを設定する対象
//    char *calss: classに設定する文字列
//返り値:なし
//-------------------------------------------------
void setIrisClass(Iris *iris, char *class) {
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
    setIrisClass(iris, class);
    return;
}

//-------------------------------------------------
//機能:irisの各パラメータを初期化する
//    具体的に、すべての特微量を0にし、classを空文字列にする
//引数 Iris iris          : パラメータを初期化する対象
//返り値:なし
//-------------------------------------------------
void initParameter(Iris *iris) {
    setParameter(iris, 0.0, 0.0, 0.0, 0.0, "");
}

//-------------------------------------------------
//機能:pointの基準点からの距離を取得する
//引数 Point point: 基準点からの距離を取得する対象
//返り値:pointの基準点からの距離
//-------------------------------------------------
double getDist(Point point) {
    return(point.dist);
}

//-------------------------------------------------
//機能:irisの基準点からの距離を設定する
//引数 Point point: 基準点からの距離を設定する対象
//    double dist: 基準点からの距離に設定する値
//返り値:なし
//-------------------------------------------------
void setDist(Point *point, double dist) {
    point -> dist = dist;
    return;
}

//-------------------------------------------------
//機能:pointのクラスを取得する
//引数 Point *point: クラスを取得する対象へのポインタ
//返り値:pointのクラスを文字列で返す
//-------------------------------------------------
char* getPointClass(Point *point) {
    return(point -> class);
}

//-------------------------------------------------
//機能:pointのクラスを設定する
//引数 Point point: クラスを設定する対象
//    char *class: クラスに設定する文字列
//返り値:なし
//-------------------------------------------------
void setPointClass(Point *point, char *class) {
    strcpy(point -> class, class);
    return;
}

//その他の関数---------------------------------------------
//-------------------------------------------------
//機能:irisのクラスをデータセットとの距離から推定する
//    プロットされたデータセットとのk-NNでクラスを推定する
//    kはnumの平方根
//引数 Iris iris    : クラスを調べる対象
//    Iris *dataset: データセット
//    int num      : データセットのデータ数
//返り値:推定した結果を定数で返す。推定結果が
//      Iris-setosaの場合はIRIS_SETOSAを、
//      Iris-versicolorの場合はIRIS_VERSICOLORを、
//      Iris-virginicaの場合はIRIS_VIRGINICAを返す。
//-------------------------------------------------
int presumeClass(Iris iris, Iris *dataset, int num) {
    Point min_dists[DATA_MAX];      // distの暫定最小値とクラスを合わせ持つ(k+1個分の領域を使用)
    double dist;                    // irisとdataset[i]の距離
    int i;                          // カウンタ変数
    int ret = 0;                    // 返り値
    int k = (int)round(sqrt(num));  // 調べる近傍の点の個数
    int cnt[3] = {};                // k個のうち、クラスごとのデータの個数
    //avg[0]:Iris-setosa, avg[1]:Iris-versicolor, avg[2]:Iris-virginica
    
    /*---前処理---*/
    for(i = 0;i <= k;i++){
        setDist(&min_dists[i], DBL_MAX);
    }
    
    /*---irisと各データとの距離をとり、k+1個の近傍を得る---*/
    for(i = 0;i < num;i++){
        dist = seekDist(iris, dataset[i]);
        
        if(dist < getDist(min_dists[k])){
            setDist(&min_dists[k], dist);
            setPointClass(&min_dists[k], getIrisClass(&dataset[i]));
            bubbleSort(min_dists, k + 1);
        }
    }
    
    /*---min_distsのk個の要素からクラスを推定する---*/
    for(i = 0;i < k;i++){
        if(strcmp(getPointClass(&min_dists[i]), "Iris-setosa") == 0){
            cnt[IRIS_SETOSA]++;
        }else if(strcmp(getPointClass(&min_dists[i]), "Iris-versicolor") == 0){
            cnt[IRIS_VERSICOLOR]++;
        }else if(strcmp(getPointClass(&min_dists[i]), "Iris-virginica") == 0){
            cnt[IRIS_VIRGINICA]++;
        }
    }
    
    /*---返り値を確定---*/
    if(cnt[IRIS_SETOSA] > cnt[IRIS_VERSICOLOR] && cnt[IRIS_SETOSA] > cnt[IRIS_VIRGINICA]){
        ret = IRIS_SETOSA;
    }else if(cnt[IRIS_VERSICOLOR] > cnt[IRIS_SETOSA] && cnt[IRIS_VERSICOLOR] > cnt[IRIS_VIRGINICA]){
        ret = IRIS_VERSICOLOR;
    }else if(cnt[IRIS_VIRGINICA] > cnt[IRIS_SETOSA] && cnt[IRIS_VIRGINICA] > cnt[IRIS_VERSICOLOR]){
        ret = IRIS_VIRGINICA;
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

//-------------------------------------------------
//機能:2つの点を入れ替える
//引数 Point *p1:---+
//    Point *p2:---+--入れ替える2点へのポインタ
//返り値:なし
//-------------------------------------------------
void swap(Point *p1, Point *p2) {
    Point temp;
    
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    
    return;
}

//-------------------------------------------------
//機能:2つの点を基準点からの距離をキーに昇順ソートする
//引数 Point *p1:---+
//    Point *p2:---+--ソートする2点へのポインタ
//返り値:なし
//-------------------------------------------------
void sort(Point *p1, Point *p2) {
    if(getDist(*p1) > getDist(*p2)){
        swap(p1, p2);
    }
}

//-------------------------------------------------
//機能:num個の点arrayを基準点からの距離をキーに昇順ソートする
//引数 Point *array: ソートする対象のデータ配列
//    int num     : データの個数
//返り値:なし
//-------------------------------------------------
void bubbleSort(Point *array, int num) {
    int i, j;
    
    for(i = 0;i < num - 1;i++){
        for(j = num - 1;j > i;j--){
            sort(&array[j - 1], &array[j]);
        }
    }
    
    return;
}
