#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Structured array with its length
typedef struct{
    int length;
    double *data;
} Data;
//Allocating memory with its length parameter
Data createArray(int len){
    Data x;
    x.length = len;
    x.data = malloc(sizeof(double) * len);
    return x;
}
//Optimized free fucntion
void freeArray(Data *dataArray) {
    free(dataArray->data);
    dataArray->data = NULL;  //For dangling pointer
    dataArray->length = 0;
}

//Function prototypes
double mean(const Data x);
double stddev(const Data x);
double meanstddev(const Data x);
double * Gaussfn(const Data x);

int main(){
    printf("Test\n");
    double x[] = {86.0, 85.0, 84.0, 89.0, 85.0, 89.0, 87.0, 85.0, 82.0, 85.0};
    int len = sizeof(x) / sizeof(x[0]);
    Data * gauss = Gaussfn(x); //uses pointers as necessary
    double check = 0.0;
    
    printf("Mean value: %lf\n", mean(test));
    printf("Standard sample deviation: %lf\n", stddev(x));
    printf("Standard mean deviation: %lf\n\n", meanstddev(x));
    for(int i=0; i<len; i++) printf("Gaussian theoretichal value: %lf\n", gauss[i]);
    for(int i=0; i<len; i++) check += gauss[i];
    printf("Normalization check: %lf\n", check);
    free(gauss); //free the allocated memory to avoid memory leaks
    freeArray(&test);

    return 0;
}

//Mean value
double mean(const Data x){
    double mean = 0.0;
    for(int i=0; i<x.length; i++){
        mean += x.data[i];
    }
    return mean/x.length;
}

//Standard sample deviation
double stddev(const Data x){
    double meanvalue = mean(x);
    double stddev = 0.0;
    for(int i=0; i<x.length; i++){
        stddev += pow(meanvalue- x.data[i], 2);
    }
    return sqrt(stddev/(x.length-1));
}

//Mean standard deviation
double meanstddev(const Data x){
    return stddev(x)/sqrt(x.length);
}

//Gaussian function using pointers
Data * Gaussfn(const Data x){
    Data * Gauss = createArray(x.length);
    if(Gauss == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    double deviation = stddev(x);
    double meanvalue = mean(x);
    double normfactor = 1.0 / (deviation * sqrt(2*M_PI));
    double deNum = 2 * deviation * deviation;
    for(int i=0; i<x.length; i++){
        Gauss.data[i] = normfactor * exp( - pow(meanvalue - x.data[i], 2) / deNum );
    }
    return Gauss;
}