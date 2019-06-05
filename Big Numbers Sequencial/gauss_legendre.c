/* ALGORITMO DE CALCULO DO PI - MÉTODO DE GAUSS-LEGENDRE */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

#define PRECISION 100000

int main (int argc, char* argv[])
{
    double aux;
    double aux_2;

    mpf_t a_current;
    mpf_init2 (a_current, PRECISION);
    mpf_set_d (a_current, 1.0);

    mpf_t b_current;
    mpf_init2 (b_current, PRECISION);
    mpf_set_d (b_current, 2.0);
    mpf_sqrt(b_current, b_current);
    mpf_ui_div(b_current, 1.0, b_current);

    mpf_t t_current;
    mpf_init2 (t_current, PRECISION);
    mpf_set_d (t_current, 4.0);
    mpf_ui_div(t_current, 1.0, t_current);

    mpf_t p_current;
    mpf_init2 (p_current, PRECISION);
    mpf_set_d (p_current, 1.0);

    printf("a0:");
    mpf_out_str(stdout,10,6,a_current);
    printf("\nb0:");
    mpf_out_str(stdout,10,6,b_current);
    printf("\nt0:");
    mpf_out_str(stdout,10,6,t_current);
    printf("\np0:");
    mpf_out_str(stdout,10,6,p_current);
    printf("\n");

    mpf_t a_next;
    mpf_init2 (a_next, PRECISION);

    mpf_t b_next;
    mpf_init2 (b_next, PRECISION);

    mpf_t t_next;
    mpf_init2 (t_next, PRECISION);

    mpf_t p_next;
    mpf_init2 (p_next, PRECISION);

    printf("a_next:");
    mpf_out_str(stdout,10,6,a_next);
    printf("\nb_next:");
    mpf_out_str(stdout,10,6,b_next);
    printf("\nt_next:");
    mpf_out_str(stdout,10,6,t_next);
    printf("\np_next:");
    mpf_out_str(stdout,10,6,p_next);
    printf("\n");
 
    int iteracoes = pow(10,2);
    int i;

    mpf_t float_aux;
    mpf_init2 (float_aux, PRECISION);
    mpf_t float_aux2;
    mpf_init2 (float_aux2, PRECISION);

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

    mpf_t pi;
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