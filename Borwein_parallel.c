#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
 
double pi = 0.0;

void *myfunc(void *myvar);

int main(){
    double *iter;
    int ret1, ret2;
    double p = 10000000;
    int THREADS_MAX = 1000;

    pthread_t threads[THREADS_MAX];
    double thread_args[THREADS_MAX];
    int i, k, j, aux = 0;

    for(k = 0; k < p/1000; k++){
        j = 1000*k;
        for (i = 0; i < THREADS_MAX; i++){
            thread_args[i] = j;
            j = j + 1.0;
            //printf("Valor enviado para a thread: %lf\n", thread_args[i]);
            pthread_create(&threads[i], NULL, myfunc, (void *) &thread_args[i]);
        }
        for (i = 0; i < THREADS_MAX; i++){
            pthread_join(threads[i], NULL);
        }
    }

    printf("OLHA QUE VALOR XUXU DE PI: %lf\n", pi);
    return 0;
}

void *myfunc(void *myvar){
    double* end = (double*)myvar;
    //printf("Valor recibo pela função da thread: %lf\n", *end);
    double k = *end;
    double pi_aux;
    pi_aux = (1/pow(16, k))*((4/(8*k+1))-(2/(8*k+4))-(1/(8*k+5))-(1/(8*k+6)));
    pi += pi_aux;
    return NULL;
}