#include<stdio.h>
#include<math.h>
 
double pi = 0.0;
double k, p = 100;

int main(){
    for(k = 0; k < p; k++){
        pi += (1/pow(16, k))*((4/(8*k+1))-(2/(8*k+4))-(1/(8*k+5))-(1/(8*k+6)));
    }
    printf("%.6lf\n", pi);

    return 0;
}