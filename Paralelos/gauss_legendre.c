/* ALGORITMO DE CALCULO DO PI - MÉTODO DE GAUSS-LEGENDRE */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include<pthread.h>

#define PRECISION 100000
mpf_t pi;

void *myfunc(void *myvar);

int main (int argc, char* argv[])
{
    int iteracoes = pow(10,2);
    int i, k, j;

    int THREADS_MAX = 10;

    mpf_init2 (pi, PRECISION);
    mpf_set_d (pi, 0.0);


    pthread_t threads[THREADS_MAX];
    double thread_args[THREADS_MAX];

    for(k = 0; k < iteracoes/THREADS_MAX; k++){
        j = THREADS_MAX*k;
        for (i = 0; i < THREADS_MAX; i++){
            thread_args[i] = j;
            j = j + 1.0;
            printf("Valor enviado para a thread: %d\n", i);
            pthread_create(&threads[i], NULL, myfunc, (void *) &thread_args[i]);
        }
        for (i = 0; i < THREADS_MAX; i++){
            pthread_join(threads[i], NULL);
        }
    }


    for(i=0; i<iteracoes; i++)
    {
        mpf_add(a_next, a_current, b_current); // a + b
        mpf_div_ui(a_next, a_next, 2); // (a+b)/2

        mpf_mul(b_next, a_current, b_current); // a * b
        mpf_sqrt(b_next, b_next); // raiz(a*b)

        mpf_sub(float_aux2, a_current, a_next); // a - a_next
        mpf_pow_ui(float_aux2, float_aux2, 2); // (a + a_next)^2
        mpf_mul(float_aux2, float_aux2, p_current);
        mpf_sub(t_next, t_current, float_aux2);

        mpf_mul_ui(p_next, p_current, 2);

        mpf_set(a_current, a_next);
        mpf_set(b_current, b_next);
        mpf_set(t_current, t_next);
        mpf_set(p_current, p_next);
    }
    mpf_init2 (pi, PRECISION);

    mpf_add(float_aux, a_current, b_current);
    mpf_pow_ui(float_aux, float_aux, 2);
    mpf_mul_ui(float_aux2, t_current, 4);
    mpf_div(pi, float_aux, float_aux2);

    printf("VALOR DO PI:");
    mpf_out_str(stdout,10,6,pi);
    printf("\n");

    mpf_clear(a_current);
    mpf_clear(b_current);
    mpf_clear(t_current);
    mpf_clear(p_current);

    mpf_clear(a_next);
    mpf_clear(b_next);
    mpf_clear(t_next);
    mpf_clear(p_next);

    return 0;
}

void *myfunc(void *myvar){
    double* end = (double*)myvar;
    //printf("Valor recibo pela função da thread: %lf\n", *end);
    double k = *end;
    int i;
    


    return NULL;
}