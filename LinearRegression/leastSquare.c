#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

//Defining an array paired with its length with a struct
typedef struct{
    int length;
    double * data;
} DataArray;
//Allocating memory with its length parameter
DataArray * createArray(int len){
    DataArray * x = malloc(sizeof(DataArray));
    x->length = len;
    x->data = malloc(sizeof(double) * len);
    return x;
}
//Optimized free-fucntion for the whole structure
void freeArray(DataArray * dataArray){
    if (dataArray == NULL) return;
    free(dataArray->data);
    dataArray->data = NULL;
    dataArray->length = 0;
    free(dataArray);
}

//Defining a struct which contains the final arguments of the regression
typedef struct{
    double A;
    double B;
    double sigmaA;
    double sigmaB;
    double sigmay;
} RegressionOutput;
//Initialization of the struct
RegressionOutput * initializeOutput(){
    RegressionOutput * results = malloc(sizeof(RegressionOutput));
    results->A = 0.0;
    results->B = 0.0;
    results->sigmaA = 0.0;
    results->sigmaB = 0.0;
    results->sigmay = 0.0;

    return results;
}
//Optimized free-fucntion for the RegressionOutput structure
void freeRegressionOutput(RegressionOutput * results){
    if (results == NULL) return;
    results->A = 0.0;
    results->B = 0.0;
    results->sigmaA = 0.0;
    results->sigmaB = 0.0;
    results->sigmay = 0.0;
    free(results);
}

//Function prototypes
RegressionOutput LinearRegression(DataArray x, DataArray y);

int main(){
    //Creating random data
    int len = 100;
    DataArray * x = createArray(len);
    srand(time(NULL));
    for(int i=0; i<len; i++) x->data[i] = rand()/RAND_MAX;
    freeArray(x);

    RegressionOutput * interpolation = initializeOutput();
    printf("Testing initialized values: %lf\n", interpolation->A);

    return 0;
}

RegressionOutput LinearRegression(DataArray x, DataArray y){
    //Equal lengths check
    if(x.length != y.length){
        printf("Different dimension arrays: incompatible datas to interpolate\n");
        exit(1);
    }
    int N = x.length; //Just to be consistent with the book after the length check

    //Initialization results and math variables
    RegressionOutput * results = initializeOutput();
    if(results == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    double sumx = 0.0;
    double sumx2 = 0.0;
    double sumy = 0.0;
    double sumxy = 0.0;

    //Calculations
    for(int i=0; i<N; i++){
        sumx += x.data[i];
        sumx2 += x.data[i] * x.data[i];
        sumy += y.data[i];
        sumxy += x.data[i] * y.data[i];
    }
    double Delta = N * sumx2 - sumx * sumx;
    results->A = ( sumx2 * sumy - sumx * sumxy ) / Delta;
    results->B = ( N * sumxy - sumx * sumy ) / Delta;

    //Further calculations for the errors
    double temp = 0.0;
    for (int i=0; i<N; i++){
        temp += pow(y.data[i] - results->A - results->B * x.data[i], 2);
    }
    results->sigmay = sqrt( temp / (N - 2) );
    results->sigmaA = results->sigmay * sqrt(sumx2 / Delta);
    results->sigmaB = results->sigmay * sqrt(N / Delta);

    return * results;
}