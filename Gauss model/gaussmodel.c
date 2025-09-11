#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Function prototypes
double mean(double x[], int len);
double stddev(double x[], int len);
double meanstddev(double x[], int len);
double *Gaussfn(double x[], int len);


int main(){
    printf("Test\n");
    double x[] = {86.0, 85.0, 84.0, 89.0, 85.0, 89.0, 87.0, 85.0, 82.0, 85.0};
    int len = sizeof(x) / sizeof(x[0]);
    double *gauss = Gaussfn(x, len); //uses pointers as necessary
    double check = 0.0;

    printf("Mean value: %lf\n", mean(x, len));
    printf("Standard sample deviation: %lf\n", stddev(x, len));
    printf("Standard mean deviation: %lf\n\n", meanstddev(x,len));
    for(int i=0; i<len; i++) printf("Gaussian theoretichal value: %lf\n", gauss[i]);
    for(int i=0; i<len; i++) check += gauss[i];
    printf("Normalization check: %lf\n", check);    
    free(gauss); //free the allocated memory to avoid memory leaks

    return 0;
}

//Mean value
double mean(double x[], int len){
    double mean = 0.0;
    for(int i=0;i<len;i++){
        mean += x[i];
    }
    return mean/len;
}

//Standard sample deviation
double stddev(double x[], int len){
    double meanvalue = mean(x, len);
    double stddev = 0.0;
    for(int i=0;i<len;i++){
        stddev += pow(meanvalue- x[i], 2);
    }
    return sqrt(stddev/(len-1));
}

//Mean standard deviation
double meanstddev(double x[], int len){
    return stddev(x,len)/sqrt(len);
}

//Gaussian function using pointers
double *Gaussfn(double x[], int len){
    double *Gauss = malloc(len * sizeof(double));
    if(Gauss == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    double deviation = stddev(x,len);
    double meanvalue = mean(x,len);
    double normfactor = 1 / (deviation * sqrt(2*M_PI));
    for(int i=0;i<len;i++){
        Gauss[i] = normfactor * exp( - pow(meanvalue - x[i], 2) / (2 * pow(deviation, 2)) );
    }
    return Gauss;
}