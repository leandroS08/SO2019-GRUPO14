#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include<pthread.h>
 
#define PRECISION 256

mpf_t pi;


void *myfunc(void *myvar);

int main()
{
    int k, i, j;

    int iteracoes = pow(10,5);
    int THREADS_MAX = 1000;


    mpf_init2 (pi, PRECISION);
    mpf_set_d (pi, 0.0);

    pthread_t threads[THREADS_MAX];
    double thread_args[THREADS_MAX];

    for(k = 0; k < iteracoes/THREADS_MAX; k++){
        j = THREADS_MAX*k;
        for (i = 0; i < THREADS_MAX; i++){
            thread_args[i] = j;
            j = j + 1.0;
            //printf("Valor enviado para a thread: %d\n", i);
            pthread_create(&threads[i], NULL, myfunc, (void *) &thread_args[i]);
        }
        for (i = 0; i < THREADS_MAX; i++){
            pthread_join(threads[i], NULL);
        }
    }

    printf("VALOR DO PI:");
    mpf_out_str(stdout,10,7,pi);
    printf("\n");
    
    return 0;
}

void *myfunc(void *myvar){
    double* end = (double*)myvar;
    //printf("Valor recibo pela função da thread: %lf\n", *end);
    double k = *end;
    int i;

    mpf_t aux_0;
    mpf_init2 (aux_0, PRECISION);
    mpf_set_d (aux_0, 0.0);
    
    mpf_t aux_1;
    mpf_init2 (aux_1, PRECISION);
    mpf_set_d (aux_1, 0.0);

    mpf_t aux_2;
    mpf_init2 (aux_2, PRECISION);
    mpf_set_d (aux_2, 0.0);

    mpf_t aux_3;
    mpf_init2 (aux_3, PRECISION);
    mpf_set_d (aux_3, 0.0);

    mpf_t aux_4;
    mpf_init2 (aux_4, PRECISION);
    mpf_set_d (aux_4, 0.0);

    mpf_t aux_5;
    mpf_init2 (aux_5, PRECISION);
    mpf_set_d (aux_5, 0.0);

    mpf_t aux_6;
    mpf_init2 (aux_6, PRECISION);
    mpf_set_d (aux_6, 0.0);

    /* aux_1 = 1 / pow(16, k) */
    if ( k==0 ) mpf_set_d (aux_1, 1.0);
    else
    {
        mpf_set_d (aux_1, 16.0);
        for(i=0; i<k-1; i++)
        {
            mpf_mul_ui (aux_1, aux_1, 16.0);
        }
        mpf_ui_div (aux_1, 1.0, aux_1);
    }



    /* aux_2 = 4 / (8*k+1) */
    mpf_set_d (aux_2, (8.0*k + 1.0));
    mpf_ui_div (aux_2, 4.0, aux_2);

    /* aux_3 = 2 / (8*k+4) */
    mpf_set_d (aux_3, (8.0*k + 4.0));
    mpf_ui_div (aux_3, 2.0, aux_3);       

    /* aux_4 = 1 / (8*k+5) */
    mpf_set_d (aux_4, (8.0*k + 5.0));
    mpf_ui_div (aux_4, 1.0, aux_4);   

    /* aux_5 = 1 / (8*k+6) */
    mpf_set_d (aux_5, (8.0*k + 6.0));
    mpf_ui_div (aux_5, 1.0, aux_5);

    /* aux_6 = aux_2 - aux_3 - aux_4 - aux_5 */ 
    mpf_sub (aux_6, aux_2, aux_3);
    mpf_sub (aux_6, aux_6, aux_4);
    mpf_sub (aux_6, aux_6, aux_5);

    /* aux_0 = aux_1 * aux_6 */
    mpf_mul (aux_0, aux_1, aux_6);

    /* pi = pi + aux_0 */
    mpf_add (pi, pi, aux_0);

    return NULL;
}