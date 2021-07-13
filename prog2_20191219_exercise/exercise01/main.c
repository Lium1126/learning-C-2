//
//  main.c
//  exercise01
//
//  Created by k19061kk on 2019/12/19.
//  Copyright © 2019 AIT. All rights reserved.
//
/*-----------------------------------------------+
 プログラミング及び演習II 第12回
 課題
 Irisの1-NN分類アルゴリズムを5分割クロスバリテーションで
 評価し、結果を混同行列で表示せよ.
 +-----------------------------------------------*/

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
double getSepalLength(Iris iris);                         // irisからsepal_lengthを取得する
void setSepalLength(Iris *iris, double length);           // irisのsepal_lengthを設定する
double getSepalWidth(Iris iris);                          // irisからsepal_wigthを取得する
void setSepalWidth(Iris *iris, double width);             // irisのsepal_widthを設定する
double getPetalLength(Iris iris);                         // irisからpetal_lengthを取得する
void setPetalLength(Iris *iris, double length);           // irisのpetal_lengthを設定する
double getPetalWidth(Iris iris);                          // irisからpetal_widthを取得する
void setPetalWidth(Iris *iris, double width);             // irisのpetal_widthを設定する
char* getClass(Iris *iris);                               // irisからclassを取得する
void setClass(Iris *iris, char *class);                   // irisのclassを設定する
void setParameter(Iris *iris, double sepal_length, double sepal_width, double petal_length, double petal_width, char *class);   // irisにパラメータを設定する

//その他の関数
void shuffleArray(Iris *a, int n);                        // 要素数n(添字は0~n-1)の配列aをシャッフルする
void swapPtr(Iris *a, Iris *b);                           // aとbを入れ替える(shuffleArrayのサブ関数)
int presumeClass(Iris iris, Iris *dataset, int num);      // irisとデータセットを比べ、クラスを推定する(1-NNを行う)
double seekDist(Iris iris1, Iris iris2);                  // 二つのIris型変数の距離を求める
int convertMacro(char *class);                            // クラスを表す文字列からマクロへ変換する
int judgePresume(Iris iris, int macro);                   // 推定結果が正解か判定する
void initMatrix(double matrix[3][3]);                     // 行列を初期化する
void makeConfusionMatrix(double confusionMatrix[3][3], Iris iris, int result);      // 混同行列を作成する
void printConfusionMatrix(double confusionMatrix[3][3]);  // 混同行列を表示する
void splitData(int n, int k, int num, Iris *array_all, Iris *array_learn, int size_learn, Iris *array_test, int size_test);  // データ分割を行う

//関数群===========================================================
//main()関数----------------------------------------------
int main(int argc, const char * argv[]) {
    Iris array_all[DATA_MAX];                                 // データすべてを格納する構造体の配列
    Iris *array_learn;                                        // 学習用データ
    Iris *array_test;                                         // 推定対象データ
    double confusion_matrix[3][3] = {{}, {}, {}};             // 混同行列(添字はマクロに準拠)
    double confusion_matrix_tmp[3][3] = {{}, {}, {}};         // 混同行列を求める際の作業用変数
    double sepalLegnth, sepalWidth, petalLength, petalWidth;  // 各パラメータ
    char class[CLASS_LEN];                                    // セットするクラス名
    char line[LINE_LEN];                                      // ファイル入力を一行受け付ける文字配列
    int cnt;                                                  // カウンタ変数(ファイル入力後はarray_allの要素数)
    int i, j;                                                 // カウンタ変数
    int size_learn, size_test;                                // それぞれarray_learn,array_testの要素数
    int estimated_result;                                     // 推定結果を格納する変数
    int num_class[3] = {};                                    // 推定対象のデータのうち、クラスごとのデータ数
    int n = 5;                                                // 分割数
    int k;                                                    // テストデータを何番目にするか
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
    size_learn = cnt * (n - 1) / n;
    size_test = cnt / n;
    
    /*---array_learn,array_testを動的に確保---*/
    if ((array_learn = (Iris*)malloc(sizeof(Iris) * size_learn)) == NULL) {
        fprintf(stderr, "No enough memory.\n");
        exit(EXIT_FAILURE);
    }
    if ((array_test = (Iris*)malloc(sizeof(Iris) * size_test)) == NULL) {
        fprintf(stderr, "No enough memory.\n");
        free(array_learn);
        exit(EXIT_FAILURE);
    }
    
    /*---出力形式の説明---*/
    printf("<出力形式>\n");
    printf("推定データ: 正しいクラス 推定結果 正誤\n");
    
    /*---kを0からn-1にして分割---*/
    for (k = 0;k < n;k++) {
        splitData(n, k, cnt, array_all, array_learn, size_learn, array_test, size_test);
        
        /*---作業用混同行列とnum_classを初期化---*/
        initMatrix(confusion_matrix_tmp);
        for (i = 0;i < 3;i++) {
            num_class[i] = 0;
        }
        
        printf("テストデータ:%d番目---------------------------------------------------------\n", k);
        
        /*---array_testに対して1-NNを行い、推定結果と正誤を出力すると同時に、混同行列を作成---*/
        // 1-NNを行い、推定結果と正誤を出力すると同時に、混同行列(tmp)を作成
        for (i = 0;i < size_test;i++) {
            // 推定結果
            estimated_result = presumeClass(array_test[i], array_learn, size_learn);
            printf("array_test[%2d]: %-15s ", i, getClass(&array_test[i]));
            if (estimated_result == IRIS_SETOSA) {
                printf("%-15s ", "Iris-setosa");
            } else if (estimated_result == IRIS_VERSICOLOR) {
                printf("%-15s ", "Iris-versicolor");
            } else if (estimated_result == IRIS_VIRGINICA) {
                printf("%-15s ", "Iris-virginica");
            }
            makeConfusionMatrix(confusion_matrix_tmp, array_test[i], estimated_result);
            
            // 正誤
            if (judgePresume(array_test[i], estimated_result)) {
                printf("正解\n");
            } else {
                printf("不正解\n");
            }
        }
        
        /*---array_testのクラスごとのデータ数を求める---*/
        for (i = 0;i < size_test;i++) {
            if (convertMacro(getClass(&array_test[i])) != -1) {
                num_class[convertMacro(getClass(&array_test[i]))]++;
            }
        }
        
        /*---作成した混同行列(tmp)の要素を割合に変換---*/
        for (i = 0;i < 3;i++) {
            for (j = 0;j < 3;j++) {
                if (num_class[i] != 0) {
                    confusion_matrix_tmp[i][j] /= (double)num_class[i];
                }
            }
        }
        
        /*---k回目の推定での混同行列を表示---*/
        printf("<混同行列> 行:正解 列:推定\n");
        printConfusionMatrix(confusion_matrix_tmp);
        
        /*---作成した混同行列を最終結果用の混同行列に加算---*/
        for (i = 0;i < 3;i++) {
            for (j = 0;j < 3;j++) {
                confusion_matrix[i][j] += confusion_matrix_tmp[i][j];
            }
        }
    }
    
    /*---最終結果用の混同行列の要素の平均をとる---*/
    for (i = 0;i < 3;i++) {
        for (j = 0;j < 3;j++) {
            confusion_matrix[i][j] /= (double)n;
        }
    }
    
    /*---最終結果を混同行列で表示---*/
    printf("------------------------------------------------------------------------\n");
    printf("<混同行列> 行:正解 列:推定\n");
    printConfusionMatrix(confusion_matrix);
    
    /*---array_learn,array_testを解放---*/
    free(array_learn);
    free(array_test);
    
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
//返り値:推定した結果をマクロで返す。推定結果が
//      Iris-setosaの場合はIRIS_SETOSAを、
//      Iris-versicolorの場合はIRIS_VERSICOLORを、
//      Iris-virginicaの場合はIRIS_VIRGINICAを返す。
//-------------------------------------------------
int presumeClass(Iris iris, Iris *dataset, int num) {
    double dist;                // irisとdataset[i]との距離
    int i;                      // カウンタ変数
    double min_dist = DBL_MAX;  // distの暫定最小値
    int ret = 0;                // 返り値
    int min_index = 0;          // 最小距離のデータの添字
    
    for (i = 0;i < num;i++) {
        dist = seekDist(iris, dataset[i]);
        
        if (dist < min_dist) {
            min_dist = dist;
            min_index = i;
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

//-------------------------------------------------
//機能:推定結果が正しいか判定する
//引数 Iris iris:推定対象のデータ
//    int macro:推定結果を表すマクロ(IRIS_SETOSA,
//              IRIS_VERSICOLOR,IRIS_VIRGINICA
//              のいずれか)
//返り値:推定結果が正解なら1、不正解なら0を返す
//-------------------------------------------------
int judgePresume(Iris iris, int macro) {
    if (strcmp(getClass(&iris), "Iris-setosa") == 0 && macro == IRIS_SETOSA) {
        return(1);
    } else if (strcmp(getClass(&iris), "Iris-versicolor") == 0 && macro == IRIS_VERSICOLOR) {
        return(1);
    } else if (strcmp(getClass(&iris), "Iris-virginica") == 0 && macro == IRIS_VIRGINICA) {
        return(1);
    } else {
        return(0);
    }
}

//-------------------------------------------------
//機能:クラスを表す文字列からマクロへ変換する
//引数 char *class:クラスを表す文字列
//返り値:classを表すマクロ
//-------------------------------------------------
int convertMacro(char *class) {
    if (strcmp(class, "Iris-setosa") == 0) {
        return(IRIS_SETOSA);
    } else if (strcmp(class, "Iris-versicolor") == 0) {
        return(IRIS_VERSICOLOR);
    } else if (strcmp(class, "Iris-virginica") == 0) {
        return(IRIS_VIRGINICA);
    } else {
        return(-1);
    }
}

//-------------------------------------------------
//機能:行列をゼロクリアする
//引数 double matrix[3][3]:初期化する行列
//返り値:なし
//-------------------------------------------------
void initMatrix(double matrix[3][3]) {
    int i, j;
    
    for (i = 0;i < 3;i++) {
        for (j = 0;j < 3;j++) {
            matrix[i][j] = 0;
        }
    }
    
    return;
}

//-------------------------------------------------
//機能:混同行列を作成する
//引数 double confusionMatrix[3][3]:混同行列本体
//    Iris iris                   :推定対象のデータ
//    int result                  :推定結果を表すマクロ
//返り値:なし
//-------------------------------------------------
void makeConfusionMatrix(double confusionMatrix[3][3], Iris iris, int result) {
    if (convertMacro(getClass(&iris)) != -1) {
        confusionMatrix[convertMacro(getClass(&iris))][result]++;
    }
    return;
}

//-------------------------------------------------
//機能:混同行列を表示する
//引数 double confusionMatrix[3][3]:混同行列本体
//返り値:なし
//-------------------------------------------------
void printConfusionMatrix(double confusionMatrix[3][3]) {
    int i;  // カウンタ変数
    
    for (i = 0;i < 16;i++) printf(" ");
    printf("%15s %15s %15s\n", "Iris-setosa", "Iris-versicolor", "Iris-virginica");
    
    printf("%15s ", "Iris-setosa");
    for (i = 0;i < 3;i++) {
        printf("%15.3f", confusionMatrix[IRIS_SETOSA][i]);
        if (i != 3 - 1) printf(" ");
        else printf("\n");
    }
    
    printf("%15s ", "Iris-versicolor");
    for (i = 0;i < 3;i++) {
        printf("%15.3f", confusionMatrix[IRIS_VERSICOLOR][i]);
        if (i != 3 - 1) printf(" ");
        else printf("\n");
    }
    
    printf("%15s ", "Iris-virginica");
    for (i = 0;i < 3;i++) {
        printf("%15.3f", confusionMatrix[IRIS_VIRGINICA][i]);
        if (i != 3 - 1) printf(" ");
        else printf("\n");
    }
    return;
}

//---------------------------------------------
//機能:データを分割する
//引数 int n:分割数
//    int k:テストデータを何番目にするか
//    Iris *array_all:全データ
//    Iris *array_learn:学習用データ
//    int size_learn:array_learnのデータ数
//    Iris *array_test:テストデータ
//    int size_test:array_testのデータ数
//返り値:なし
//---------------------------------------------
void splitData(int n, int k, int num, Iris *array_all, Iris *array_learn, int size_learn, Iris *array_test, int size_test) {
    int i, j, cnt = 0;          // カウンタ変数
    
    for (i = 0;i < n;i++) {
        if (num % n == 0) {
            // すべてのデータの個数がnで割り切れる
            for (j = 0;j < num / n;j++) {
                if (i != k) {
                    array_learn[cnt] = array_all[(num / n) * i + j];
                    cnt++;
                } else {
                    array_test[j] = array_all[(num / n) * i + j];
                }
            }
        }
        
        else {
            // すべてのデータの個数がnで割り切れない
            if (k == n - 1) {
                // テストデータは分割後の最後のデータ群である
                if(i != n - 1) {  // 今見ているのはテストデータでないため、learnに格納する
                    for(j = 0;j < num / n;j++) {
                        array_learn[cnt] = array_all[(num / n) * i + j];
                        cnt++;
                    }
                } else {          // テストデータを見ているため、testに格納する
                    for(j = 0;j < size_test;j++) {
                        array_test[j] = array_all[(num / n) * i + j];
                    }
                }
            }
            
            else {
                // テストデータは分割後の最後のデータ群ではない
                if(i != n - 1) {  // 今見ているのは分割後の最後のデータ群でない
                    for (j = 0;j < num / n;j++) {
                        if (i != k) {
                            array_learn[cnt] = array_all[(num / n) * i + j];
                            cnt++;
                        } else {
                            array_test[j] = array_all[(num / n) * i + j];
                        }
                    }
                } else {         // 今見ているのは分割後の最後のデータ群である
                    for (j = 0;j < (num / n) + (num % n);j++) {
                        array_learn[cnt] = array_all[(num / n) * i + j];
                        cnt++;
                    }
                }
            }
        }
    }
    
    return;
}
