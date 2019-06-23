#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <gmp.h>


#define PRECISION 256

mpf_t pi;
mpf_t ki;

void *myfunc(void *myvar);

int main()
{
    srand(time(NULL));
<<<<<<< HEAD
    int iteracoes = pow(10,7);
=======
    int iteracoes = pow(10,3);
>>>>>>> 352503e1aafc650171aaaf975daae4f91a704caf
    int i, k, j;
    int THREADS_MAX = 1000;

    pthread_t threads[THREADS_MAX];
    double thread_args[THREADS_MAX];

    mpf_init2 (pi, PRECISION);
    mpf_set_d (pi, 0.0);

    mpf_init2 (ki, PRECISION);
    mpf_set_d (ki, 0.0);

    mpf_init2 (pi, PRECISION);
    mpf_set_d (pi, 0.0);


    for(k = 0; k < iteracoes/THREADS_MAX; k++){
        j = THREADS_MAX*k;
        for (i = 0; i < THREADS_MAX; i++){
            thread_args[i] = j;
            j = j + 1.0;
           // printf("Valor enviado para a thread: %d\n", i);
            pthread_create(&threads[i], NULL, myfunc, (void *) &thread_args[i]);
        }
        for (i = 0; i < THREADS_MAX; i++){
            pthread_join(threads[i], NULL);
        }
    }

    mpf_div_ui (pi, ki, iteracoes);
    mpf_mul_ui (pi, pi, 4.0);

    printf("VALOR DO PI:");
    mpf_out_str(stdout,10,6,pi);
    printf("\n");

    return 0;
}


void *myfunc(void *myvar){
    double* end = (double*)myvar;
    //printf("Valor recibo pela função da thread: %lf\n", *end);
    double k = *end;
    int i;


    mpf_t x;
    mpf_init2 (x, PRECISION);
    mpf_set_d (x, 0.0);
    
    mpf_t y;
    mpf_init2 (y, PRECISION);
    mpf_set_d (y, 0.0);

    mpf_t aux_0;
    mpf_init2 (aux_0, PRECISION);
    mpf_set_d (aux_0, 0.0);

    mpf_t aux_x;
    mpf_init2 (aux_x, PRECISION);
    mpf_set_d (aux_x, 0.0);

    mpf_t aux_y;
    mpf_init2 (aux_y, PRECISION);
    mpf_set_d (aux_y, 0.0);

    mpf_set_d (x, (double)rand()/(double)RAND_MAX);
    mpf_set_d (y, (double)rand()/(double)RAND_MAX);

    mpf_pow_ui (aux_x, x, 2.0);
    mpf_pow_ui (aux_y, y, 2.0);
    mpf_add (aux_0, aux_x, aux_y);

    if ( mpf_cmp_ui (aux_0, 1.0) <= 0 )
        mpf_add_ui (ki, ki, 1.0);

    return NULL;
}