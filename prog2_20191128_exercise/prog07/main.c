//
//  main.c
//  prog07
//
//  Created by k19061kk on 2019/11/28.
//  Copyright © 2019 AIT. All rights reserved.
//

/*------------------------------------+
 プログラミング及び演習II 第9回
 問題7
 以下の3つのサンプルがどのクラスに属しているか
 を推定するプログラムを作成せよ。
 平均値との距離を測って最も近いクラスとみなせ。
    5.7, 4.0, 1.2, 0.2
    5.9, 2.9, 4.2, 1.5
    5.6, 2.8, 8.4, 2.0
 +------------------------------------*/

//インクルード=====================================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
void initParameter(Iris *iris);                  // irisを初期化する

//その他の関数
void seekAvg(Iris *iris, Iris *avg, int num);    // irisの各パラメータごとの平均をavgに格納する
int presumeClass(Iris iris, Iris *avg);          // irisと平均値を比べ、クラスを推定する
double seekDist(Iris iris1, Iris iris2);         // 二つのIris型変数の距離を求める

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
    Iris avg[3];                                              // irisの各パラメータごとの平均
    //avg[0]:Iris-setosa, avg[1]:Iris-versicolor, avg[2]:Iris-virginica
    
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
    
    /*---各特微量の平均を求める---*/
    seekAvg(iris, avg, cnt);
    
    /*---サンプルデータを問題に指定されたように設定する---*/
    setParameter(&sample[0], 5.7, 4.0, 1.2, 0.2, "");
    setParameter(&sample[1], 5.9, 2.9, 4.2, 1.5, "");
    setParameter(&sample[2], 5.6, 2.8, 4.8, 2.0, "");
    
    /*---それぞれのサンプルについてクラスを推定---*/
    for(i = 0;i < 3;i++){
        result = presumeClass(sample[i], avg);
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
char* getClass(Iris *iris) {
    return(iris -> class);
}

//-------------------------------------------------
//機能:irisのclassを設定する
//引数 Iris iris  : classを設定する対象
//    char *calss: classに設定する文字列
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

//-------------------------------------------------
//機能:irisの各パラメータを初期化する
//    具体的に、すべての特微量を0にし、classを空文字列にする
//引数 Iris iris          : パラメータを初期化する対象
//返り値:なし
//-------------------------------------------------
void initParameter(Iris *iris) {
    setParameter(iris, 0.0, 0.0, 0.0, 0.0, "");
}

//その他の関数---------------------------------------------
//-------------------------------------------------
//機能:Iris型配列の各特微量ごとの平均を、avgに格納する
//引数 Iris *iris  : 平均を求めるデータ集合
//    Iris *avg   : 平均を求めた結果を格納するIris型配列
//    int num     : データの個数
//返り値:なし
//-------------------------------------------------
void seekAvg(Iris *iris, Iris *avg, int num) {
    int i;                                               // カウンタ変数
    int numIrisSetosa, numIrisVersicolor, numIrisVirginica;  // 各クラスごとのデータ数
    
    /*---前処理---*/
    for(i = IRIS_SETOSA;i <= IRIS_VIRGINICA;i++){
        initParameter(&avg[i]);
    }
    numIrisSetosa = numIrisVersicolor = numIrisVirginica = 0;
    
    /*---各パラメータの総和をavgの中に格納する---*/
    for(i = 0;i < num;i++){
        if(strcmp(getClass(&iris[i]), "Iris-setosa") == 0){
            setSepalLength(&avg[IRIS_SETOSA], getSepalLength(avg[IRIS_SETOSA]) + getSepalLength(iris[i]));
            setSepalWidth(&avg[IRIS_SETOSA], getSepalWidth(avg[IRIS_SETOSA]) + getSepalWidth(iris[i]));
            setPetalLength(&avg[IRIS_SETOSA], getPetalLength(avg[IRIS_SETOSA]) + getPetalLength(iris[i]));
            setPetalWidth(&avg[IRIS_SETOSA], getPetalWidth(avg[IRIS_SETOSA]) + getPetalWidth(iris[i]));
            numIrisSetosa++;
        }
        else if(strcmp(getClass(&iris[i]), "Iris-versicolor") == 0){
            setSepalLength(&avg[IRIS_VERSICOLOR], getSepalLength(avg[IRIS_VERSICOLOR]) + getSepalLength(iris[i]));
            setSepalWidth(&avg[IRIS_VERSICOLOR], getSepalWidth(avg[IRIS_VERSICOLOR]) + getSepalWidth(iris[i]));
            setPetalLength(&avg[IRIS_VERSICOLOR], getPetalLength(avg[IRIS_VERSICOLOR]) + getPetalLength(iris[i]));
            setPetalWidth(&avg[IRIS_VERSICOLOR], getPetalWidth(avg[IRIS_VERSICOLOR]) + getPetalWidth(iris[i]));
            numIrisVersicolor++;
        }
        else if(strcmp(getClass(&iris[i]), "Iris-virginica") == 0){
            setSepalLength(&avg[IRIS_VIRGINICA], getSepalLength(avg[IRIS_VIRGINICA]) + getSepalLength(iris[i]));
            setSepalWidth(&avg[IRIS_VIRGINICA], getSepalWidth(avg[IRIS_VIRGINICA]) + getSepalWidth(iris[i]));
            setPetalLength(&avg[IRIS_VIRGINICA], getPetalLength(avg[IRIS_VIRGINICA]) + getPetalLength(iris[i]));
            setPetalWidth(&avg[IRIS_VIRGINICA], getPetalWidth(avg[IRIS_VIRGINICA]) + getPetalWidth(iris[i]));
            numIrisVirginica++;
        }
    }
    
    /*---求めた総和をもとに平均をavgに格納---*/
    // Iris-setosa
    setSepalLength(&avg[IRIS_SETOSA], getSepalLength(avg[IRIS_SETOSA]) / (double)numIrisSetosa);
    setSepalWidth(&avg[IRIS_SETOSA], getSepalWidth(avg[IRIS_SETOSA]) / (double)numIrisSetosa);
    setPetalLength(&avg[IRIS_SETOSA], getPetalLength(avg[IRIS_SETOSA]) / (double)numIrisSetosa);
    setPetalWidth(&avg[IRIS_SETOSA], getPetalWidth(avg[IRIS_SETOSA]) / (double)numIrisSetosa);
    // Iris-versicolor
    setSepalLength(&avg[IRIS_VERSICOLOR], getSepalLength(avg[IRIS_VERSICOLOR]) / (double)numIrisVersicolor);
    setSepalWidth(&avg[IRIS_VERSICOLOR], getSepalWidth(avg[IRIS_VERSICOLOR]) / (double)numIrisVersicolor);
    setPetalLength(&avg[IRIS_VERSICOLOR], getPetalLength(avg[IRIS_VERSICOLOR]) / (double)numIrisVersicolor);
    setPetalWidth(&avg[IRIS_VERSICOLOR], getPetalWidth(avg[IRIS_VERSICOLOR]) / (double)numIrisVersicolor);
    // Iris-virginica
    setSepalLength(&avg[IRIS_VIRGINICA], getSepalLength(avg[IRIS_VIRGINICA]) / (double)numIrisVirginica);
    setSepalWidth(&avg[IRIS_VIRGINICA], getSepalWidth(avg[IRIS_VIRGINICA]) / (double)numIrisVirginica);
    setPetalLength(&avg[IRIS_VIRGINICA], getPetalLength(avg[IRIS_VIRGINICA]) / (double)numIrisVirginica);
    setPetalWidth(&avg[IRIS_VIRGINICA], getPetalWidth(avg[IRIS_VIRGINICA]) / (double)numIrisVirginica);
    
    return;
}

//-------------------------------------------------
//機能:irisのクラスを平均値avg[3]との距離から推定する
//    avgの3つのデータから、1-NNで判断する
//引数 Iris iris   : クラスを調べる対象
//    Iris *avg   : クラスごとの各特微量の平均
//返り値:推定した結果を定数で返す。推定結果が
//      Iris-setosaの場合はIRIS_SETOSAを、
//      Iris-versicolorの場合はIRIS_VERSICOLORを、
//      Iris-virginicaの場合はIRIS_VIRGINICAを返す。
//-------------------------------------------------
int presumeClass(Iris iris, Iris *avg) {
    double dist[3] = {};   // irisとavg[i]とのユークリッド距離
    int i;                 // カウンタ変数
    
    for(i = IRIS_SETOSA;i <= IRIS_VIRGINICA;i++){
        dist[i] = seekDist(iris, avg[i]);
    }
    
    if(dist[IRIS_SETOSA] < dist[IRIS_VERSICOLOR] && dist[IRIS_SETOSA] < dist[IRIS_VIRGINICA]){
        return(IRIS_SETOSA);
    }else if(dist[IRIS_VERSICOLOR] < dist[IRIS_SETOSA] && dist[IRIS_VERSICOLOR] < dist[IRIS_VIRGINICA]){
        return(IRIS_VERSICOLOR);
    }else{
        return(IRIS_VIRGINICA);
    }
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
