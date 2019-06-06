#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include <time.h>


double monteCarlo(int iter){
    int i, k = 0;
    double x, y, pi;
    for(i = 0; i < iter;i++){
        x = ((double)rand()/(double)RAND_MAX); 
		y = ((double)rand()/(double)RAND_MAX);
        if(pow(x, 2)+ pow(y, 2) <= 1){
            k++;
        }
    }
    pi = 4*((double)k/(double)i);
    return pi;
}

int main(){
    double p = 1000000;
    srand(time(NULL));
    double pi = monteCarlo(p);
    printf("OLHA QUE VALOR XUXU DE PI: %lf\n", pi);
    return 0;
}