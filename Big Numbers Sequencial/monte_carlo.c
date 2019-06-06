#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <gmp.h>

#define PRECISION 256

int main()
{
    srand(time(NULL));
    int iteracoes = pow(10,6);
    int i;
    
    mpf_t pi;
    mpf_init2 (pi, PRECISION);
    mpf_set_d (pi, 0.0);

    mpf_t k;
    mpf_init2 (k, PRECISION);
    mpf_set_d (k, 0.0);

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


    for(i = 0; i < iteracoes;i++)
    {
        mpf_set_d (x, (double)rand()/(double)RAND_MAX);
        mpf_set_d (y, (double)rand()/(double)RAND_MAX);

        mpf_pow_ui (aux_x, x, 2.0);
        mpf_pow_ui (aux_y, y, 2.0);
        mpf_add (aux_0, aux_x, aux_y);

        if ( mpf_cmp_ui (aux_0, 1.0) <= 0 )
            mpf_add_ui (k, k, 1.0);
    }

    mpf_div_ui (pi, k, i);
    mpf_mul_ui (pi, pi, 4.0);

    printf("VALOR DO PI:");
    mpf_out_str(stdout,10,6,pi);
    printf("\n");

    return 0;
}