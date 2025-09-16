#include <stdio.h>
#include <stdlib.h> 
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
    double r;
} RegressionOutput;
//Initialization of the struct
RegressionOutput * initializeOutput(){
    RegressionOutput * results = malloc(sizeof(RegressionOutput));
    results->A = 0.0;
    results->B = 0.0;
    results->sigmaA = 0.0;
    results->sigmaB = 0.0;
    results->sigmay = 0.0;
    results->r = 0.0;

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
    results->r = 0.0;
    free(results);
}

//Function prototypes
RegressionOutput LeastSquares(DataArray x, DataArray y);

int main(){
    //Creating random data
    int len = 100;
    DataArray * x = createArray(len);
    DataArray * y = createArray(len);
    srand(time(NULL));
    for(int i=0; i<len; i++){
        x->data[i] = rand() % 100;
        y->data[i] = x->data[i] * (rand() / RAND_MAX + 8) + rand() % 10; //I don't know how to use it actually
    }

    //Function call and results printing
    RegressionOutput * interpolation = initializeOutput();
    * interpolation = LeastSquares(* x, * y);
    printf("Testing, A: %lf\n", interpolation->A);
    printf("Testing, B: %lf\n", interpolation->B);
    printf("Testing, sigmaA: %lf\n", interpolation->sigmaA);
    printf("Testing, sigmaB: %lf\n", interpolation->sigmaB);
    printf("Testing, sigmay: %lf\n", interpolation->sigmay);
    printf("Testing, r: %lf\n", interpolation->r);
    
    //Freeing allocated memory
    freeArray(x);
    freeArray(y);
    freeRegressionOutput(interpolation);

    return 0;
}

//Linear regression function, least squares method
RegressionOutput LeastSquares(DataArray x, DataArray y){
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
    double sumy2 = 0.0;
    double sumxy = 0.0;

    //Calculations
    for(int i=0; i<N; i++){
        sumx += x.data[i];
        sumx2 += x.data[i] * x.data[i];
        sumy += y.data[i];
        sumy2 += y.data[i] * y.data[i];
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

    //Covariance and linear correlation coefficient r
    double xmean = sumx / N;
    double ymean = sumy / N;
    double diffxy = 0.0;
    double diffx2 = 0.0;
    double diffy2 = 0.0;
    for(int i=0; i<N; i++){
        diffxy += (x.data[i] - xmean) * (y.data[i] - ymean);
        diffx2 += (x.data[i] - xmean) * (x.data[i] - xmean);
        diffy2 += (y.data[i] - ymean) * (y.data[i] - ymean);
    }
    double sigmaxy = diffxy / N;
    double sigmax2 = diffx2 / N;
    double sigmay2 = diffy2 / N;
    results->r = sigmaxy / (sqrt(sigmax2) * sqrt(sigmay2));

    return * results;
}