#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Structured array with its length
typedef struct{
    int length;
    double *data;
} DataArray;
//Allocating memory with its length parameter
DataArray * createArray(int len){
    DataArray * x = malloc(sizeof(DataArray));
    x->length = len;
    x->data = malloc(sizeof(double) * len);
    return x;
}
//Optimized free fucntion for the whole structure
void freeArray(DataArray *dataArray) {
    if (dataArray == NULL) return;
    free(dataArray->data);
    dataArray->data = NULL;
    dataArray->length = 0;
    free(dataArray);
}

//Function prototypes
double mean(const DataArray x);
double stddev(const DataArray x);
double meanstddev(const DataArray x);
DataArray * Gaussfn(const DataArray x);

int main(){
    printf("Test\n");
    double values[] = {86.0, 85.0, 84.0, 89.0, 85.0, 89.0, 87.0, 85.0, 82.0, 85.0};
    int len = sizeof(values) / sizeof(values[0]);
    DataArray * x = createArray(len);
    for(int i=0; i<x->length; i++) x->data[i] = values[i];
    DataArray * gauss = Gaussfn(*x);
    double check = 0.0;
    
    printf("Mean value: %lf\n", mean(*x));
    printf("Standard sample deviation: %lf\n", stddev(*x));
    printf("Standard mean deviation: %lf\n\n", meanstddev(*x));
    for(int i=0; i<gauss->length; i++){
        printf("Gaussian theoretichal value: %lf\n", gauss->data[i]);
    }
    for(int i=0; i<gauss->length; i++) check += gauss->data[i];
    printf("Normalization check: %lf\n", check);
    freeArray(x);
    freeArray(gauss);

    return 0;
}

//Mean value
double mean(const DataArray x){
    double mean = 0.0;
    for(int i=0; i<x.length; i++){
        mean += x.data[i];
    }
    return mean/x.length;
}

//Standard sample deviation
double stddev(const DataArray x){
    double meanvalue = mean(x);
    double stddev = 0.0;
    for(int i=0; i<x.length; i++){
        stddev += pow(meanvalue- x.data[i], 2);
    }
    return sqrt(stddev/(x.length-1));
}

//Mean standard deviation
double meanstddev(const DataArray x){
    return stddev(x)/sqrt(x.length);
}

//Gaussian function using pointers
DataArray * Gaussfn(const DataArray x){
    DataArray * GaussValues = createArray(x.length);
    if(GaussValues == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    double deviation = stddev(x);
    double meanvalue = mean(x);
    double normfactor = 1.0 / (deviation * sqrt(2*M_PI));
    double deNum = 2 * deviation * deviation;
    for(int i=0; i<x.length; i++){
        GaussValues->data[i] = normfactor * exp( - pow(meanvalue - x.data[i], 2) / deNum );
    }
    return GaussValues;
}