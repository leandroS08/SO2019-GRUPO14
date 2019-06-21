#include <stdio.h>
#include <stdlib.h>
//#include<pthread.h>
#include <math.h>
#include <time.h>

double blackScholes()
{
    double S, E, r, sigma, T;
    int M;

    //scanf("%lf %lf %lf %lf %lf %d ", &S, &E, &r, &sigma, &T, &M);
    S = 2.0;
    E = 2.0;
    r = 2.0;
    sigma = 2.0;
    T = 2.0;
    M = 100;

    double *trials = (double*) calloc(M, sizeof(double));

    int i;
    double t, aux; 
    for(i=0; i<M; i++)
    {
        aux = ((double)rand()/(double)RAND_MAX);
        t = S * exp( ( ( r - ( 0.5 * pow(sigma, 2) ) ) * T ) + (sigma*sqrt(T)*aux) );

        if(t-E > 0) 
            trials[i] = exp( (-r)*T ) * (t-E);
        else
            trials[i] = 0;
    }

    double mean, aux_mean = 0;

    for(i=0; i<M; i++)
        aux_mean += trials[i];
    mean = aux_mean / (double) M;

    double stddev, aux_stddev; 
    for(i=0; i<M; i++)
        aux_stddev += pow(trials[i] - mean, 2);
    stddev = sqrt( aux_stddev / (double)M );

    double conf_widht = 1.96 * stddev / sqrt(M);
    double conf_min = mean - conf_widht;
    double conf_max = mean + conf_widht;

    printf("Range:  ( %lf ; %lf ) \n", conf_min, conf_max);
}

int main()
{
    srand(time(NULL));
    blackScholes();
    return 0;

}