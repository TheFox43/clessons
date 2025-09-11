#include <stdio.h>
#include <math.h>

//Function prototypes
double mean(double x[], int len);
double stddev(double x[], int len);

int main(){
    printf("Test\n");
    double x[] = {86.0, 85.0, 84.0, 89.0, 85.0, 89.0, 87.0, 85.0, 82.0, 85.0};
    int len = sizeof(x)/sizeof(x[0]);

    printf("Mean value: %lf\n", mean(x, len));
    printf("Standard sample deviation: %lf", stddev(x, len));

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