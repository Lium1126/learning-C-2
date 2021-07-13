//
//  main.c
//  prog06
//
//  Created by k19061kk on 2019/11/27.
//  Copyright © 2019 AIT. All rights reserved.
//

/*----------------------------------+
 プログラミング及び演習II 第9回
 問題6
 classごとに各特微量の平均値と標準偏差を
 合わせて出力せよ。
 +----------------------------------*/

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

//操作関数
void printIrisAvgSD(Iris avg, Iris sd);          // avg及びsdの内容を表示する

//その他の関数
void seekAvg(Iris *iris, Iris *avg, int num);           // irisのclassごとの各特微量の平均をavgに格納する
void seekSD(Iris *iris, Iris *sd, int num, Iris *avg);  // irisのclassごとの各特微量の標準偏差をsdに格納する

//関数群===========================================================
//main()関数----------------------------------------------
int main(int argc, const char * argv[]) {
    Iris iris[DATA_MAX];                                      // パラメータをセットする構造体の配列
    double sepalLegnth, sepalWidth, petalLength, petalWidth;  // 各パラメータ
    char class[CLASS_LEN];                                    // セットするクラス名
    char line[LINE_LEN];                                      // ファイル入力を一行受け付ける文字配列
    int cnt;                                                  // カウンタ変数
    FILE *fp;                                                 // ファイルポインタ
    Iris avg[3];                                              // irisのclassごとの各特微量の平均
    Iris sd[3];                                               // irisのclassごとの各特微量の標準偏差
    // index 0:Iris-setosa, 1:Iris-versicolor, 2:Iris-virginica
    
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
    seekSD(iris, sd, cnt, avg);
    
    /*---結果の出力---*/
    printf("Iris-setosa(avg, sd)\n");
    printIrisAvgSD(avg[IRIS_SETOSA], sd[IRIS_SETOSA]);
    
    printf("Iris-versicolor(avg, sd)\n");
    printIrisAvgSD(avg[IRIS_VERSICOLOR], sd[IRIS_VERSICOLOR]);
    
    printf("Iris-virginica(avg, sd)\n");
    printIrisAvgSD(avg[IRIS_VIRGINICA], sd[IRIS_VIRGINICA]);
    
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
//引数 Iris iris    : classを設定する対象
//    double length: classに設定する文字列
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

//操作関数-------------------------------------------------
//-------------------------------------------------
//機能:avg及びsdの内容を標準出力に出力する
//    出力フォーマットは、各行の行頭にタブを入れ、その後特微量
//    をカンマ区切りで表示する
//引数 Iris avg:---+
//    Iris sd :---+--内容を出力するIris型変数
//    それぞれデータセットの平均、標準偏差である
//返り値:なし
//-------------------------------------------------
void printIrisAvgSD(Iris avg, Iris sd) {
    printf("\tsepal_length:(%.2f, %.2f)\n", getSepalLength(avg), getSepalLength(sd));
    printf("\tsepal_width :(%.2f, %.2f)\n", getSepalWidth(avg), getSepalWidth(sd));
    printf("\tpetal_length:(%.2f, %.2f)\n", getPetalLength(avg), getPetalLength(sd));
    printf("\tpetal_width :(%.2f, %.2f)\n", getPetalWidth(avg), getPetalWidth(sd));
    
    return;
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
    int i;                                                   // カウンタ変数
    int numIrisSetosa, numIrisVersicolor, numIrisVirginica;  // クラスごとのデータ数

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
//機能:Iris型配列の各特微量ごとの標準偏差を、sdに格納する
//引数 Iris *iris  : 標準偏差を求めるデータ集合
//    Iris *avg   : 標準偏差を格納するIris型配列
//    int num     : データの個数
//    Iris *avg   : irisに対するclassごとの各特微量の平均
//返り値:なし
//-------------------------------------------------
void seekSD(Iris *iris, Iris *sd, int num, Iris *avg) {
    int i;                                                   // カウンタ変数
    double temp;                                             // 作業用変数
    int numIrisSetosa, numIrisVersicolor, numIrisVirginica;  // クラスごとのデータ数

    /*---前処理---*/
    for(i = IRIS_SETOSA;i <= IRIS_VIRGINICA;i++){
        initParameter(&sd[i]);
    }
    numIrisSetosa = numIrisVersicolor = numIrisVirginica = 0;
    
    /*---平均との差の2乗の総和を求める---*/
    for(i = 0;i < num;i++){
        if(strcmp(getClass(&iris[i]), "Iris-setosa") == 0){
            temp = pow(getSepalLength(iris[i]) - getSepalLength(avg[IRIS_SETOSA]), 2.0);
            setSepalLength(&sd[IRIS_SETOSA], getSepalLength(sd[IRIS_SETOSA]) + temp);
            temp = pow(getSepalWidth(iris[i]) - getSepalWidth(avg[IRIS_SETOSA]), 2.0);
            setSepalWidth(&sd[IRIS_SETOSA], getSepalWidth(sd[IRIS_SETOSA]) + temp);
            temp = pow(getPetalLength(iris[i]) - getPetalLength(avg[IRIS_SETOSA]), 2.0);
            setPetalLength(&sd[IRIS_SETOSA], getPetalLength(sd[IRIS_SETOSA]) + temp);
            temp = pow(getPetalWidth(iris[i]) - getPetalWidth(avg[IRIS_SETOSA]), 2.0);
            setPetalWidth(&sd[IRIS_SETOSA], getPetalWidth(sd[IRIS_SETOSA]) + temp);
            numIrisSetosa++;
        }
        else if(strcmp(getClass(&iris[i]), "Iris-versicolor") == 0){
            temp = pow(getSepalLength(iris[i]) - getSepalLength(avg[IRIS_VERSICOLOR]), 2.0);
            setSepalLength(&sd[IRIS_VERSICOLOR], getSepalLength(sd[IRIS_VERSICOLOR]) + temp);
            temp = pow(getSepalWidth(iris[i]) - getSepalWidth(avg[IRIS_VERSICOLOR]), 2.0);
            setSepalWidth(&sd[IRIS_VERSICOLOR], getSepalWidth(sd[IRIS_VERSICOLOR]) + temp);
            temp = pow(getPetalLength(iris[i]) - getPetalLength(avg[IRIS_VERSICOLOR]), 2.0);
            setPetalLength(&sd[IRIS_VERSICOLOR], getPetalLength(sd[IRIS_VERSICOLOR]) + temp);
            temp = pow(getPetalWidth(iris[i]) - getPetalWidth(avg[IRIS_VERSICOLOR]), 2.0);
            setPetalWidth(&sd[IRIS_VERSICOLOR], getPetalWidth(sd[IRIS_VERSICOLOR]) + temp);
            numIrisVersicolor++;
        }
        else if(strcmp(getClass(&iris[i]), "Iris-virginica") == 0){
            temp = pow(getSepalLength(iris[i]) - getSepalLength(avg[IRIS_VIRGINICA]), 2.0);
            setSepalLength(&sd[IRIS_VIRGINICA], getSepalLength(sd[IRIS_VIRGINICA]) + temp);
            temp = pow(getSepalWidth(iris[i]) - getSepalWidth(avg[IRIS_VIRGINICA]), 2.0);
            setSepalWidth(&sd[IRIS_VIRGINICA], getSepalWidth(sd[IRIS_VIRGINICA]) + temp);
            temp = pow(getPetalLength(iris[i]) - getPetalLength(avg[IRIS_VIRGINICA]), 2.0);
            setPetalLength(&sd[IRIS_VIRGINICA], getPetalLength(sd[IRIS_VIRGINICA]) + temp);
            temp = pow(getPetalWidth(iris[i]) - getPetalWidth(avg[IRIS_VIRGINICA]), 2.0);
            setPetalWidth(&sd[IRIS_VIRGINICA], getPetalWidth(sd[IRIS_VIRGINICA]) + temp);
            numIrisVirginica++;
        }
    }
    
    /*---分散を求め、その平方根をsdに格納する---*/
    // Iris-setosa
    setSepalLength(&sd[IRIS_SETOSA], sqrt(getSepalLength(sd[IRIS_SETOSA]) / (double)numIrisSetosa));
    setSepalWidth(&sd[IRIS_SETOSA], sqrt(getSepalWidth(sd[IRIS_SETOSA]) / (double)numIrisSetosa));
    setPetalLength(&sd[IRIS_SETOSA], sqrt(getPetalLength(sd[IRIS_SETOSA]) / (double)numIrisSetosa));
    setPetalWidth(&sd[IRIS_SETOSA], sqrt(getPetalWidth(sd[IRIS_SETOSA]) / (double)numIrisSetosa));
    // Iris-versicolor
    setSepalLength(&sd[IRIS_VERSICOLOR], sqrt(getSepalLength(sd[IRIS_VERSICOLOR]) / (double)numIrisVersicolor));
    setSepalWidth(&sd[IRIS_VERSICOLOR], sqrt(getSepalWidth(sd[IRIS_VERSICOLOR]) / (double)numIrisVersicolor));
    setPetalLength(&sd[IRIS_VERSICOLOR], sqrt(getPetalLength(sd[IRIS_VERSICOLOR]) / (double)numIrisVersicolor));
    setPetalWidth(&sd[IRIS_VERSICOLOR], sqrt(getPetalWidth(sd[IRIS_VERSICOLOR]) / (double)numIrisVersicolor));
    // Iris-virginica
    setSepalLength(&sd[IRIS_VIRGINICA], sqrt(getSepalLength(sd[IRIS_VIRGINICA]) / (double)numIrisVirginica));
    setSepalWidth(&sd[IRIS_VIRGINICA], sqrt(getSepalWidth(sd[IRIS_VIRGINICA]) / (double)numIrisVirginica));
    setPetalLength(&sd[IRIS_VIRGINICA], sqrt(getPetalLength(sd[IRIS_VIRGINICA]) / (double)numIrisVirginica));
    setPetalWidth(&sd[IRIS_VIRGINICA], sqrt(getPetalWidth(sd[IRIS_VIRGINICA]) / (double)numIrisVirginica));
    
    return;
}
