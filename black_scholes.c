#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double blackScholes()
{
    double S, E, r, sigma, T;
    int M;
    int i;

    FILE *myfile = fopen("entrada_blackscholes.txt", "r");;
    for(i=0; i<6; i++)
    {
        if(i==0) fscanf(myfile,"%lf",&S);
        if(i==1) fscanf(myfile,"%lf",&E);
        if(i==2) fscanf(myfile,"%lf",&r);
        if(i==3) fscanf(myfile,"%lf",&sigma);
        if(i==4) fscanf(myfile,"%lf",&T);
        if(i==5) fscanf(myfile,"%d",&M);
    }
    fclose(myfile);

    //printf(" Entrada: ( S = %.2lf, E = %.2lf, r = %.2lf, sigma = %.2lf, T = %.2lf, M = %d ) \n", S, E, r, sigma, T, M);

    double *trials = (double*) calloc(M, sizeof(double));

    double t, aux; 
    for(i=0; i<M; i++)
    {
        aux = ((double)rand()/(double)RAND_MAX);
        t = S * exp( ( ( r - ( 0.5*pow(sigma, 2) ) ) * T ) + (sigma*sqrt(T)*aux) );

        if(t-E > 0) 
            trials[i] = exp( (-r)*T ) * (t-E);
        else
            trials[i] = 0;
    }

    double mean, aux_mean = 0;

    for(i=0; i<M; i++)
        aux_mean += trials[i];
    mean = aux_mean / (double)M;

    double stddev, aux_stddev = 0; 
    for(i=0; i<M; i++)
        aux_stddev += pow(trials[i] - mean, 2);
    stddev = sqrt( aux_stddev / (double)M );

    double conf_widht = 1.96 * stddev / sqrt(M);
    double conf_min = mean - conf_widht;
    double conf_max = mean + conf_widht;

    printf(" Saida: ( %lf ; %lf ) \n", conf_min, conf_max);

    free(trials);
}

int main()
{
    srand(time(NULL));
    blackScholes();
    return 0;

}