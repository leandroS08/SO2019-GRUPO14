#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include<pthread.h>

void *myfunc(void *myvar);

double trials[100000];
double t, aux; 
double S, E, r, sigma, T;
int M;
int i, k, j;

void blackScholes()
{
    //trials = (double*) calloc(M, sizeof(double));

    int THREADS_MAX = 10;
    pthread_t threads[THREADS_MAX];
    double thread_args[THREADS_MAX];

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

    printf(" Entrada: ( S = %.2lf, E = %.2lf, r = %.2lf, sigma = %.2lf, T = %.2lf, M = %d ) \n", S, E, r, sigma, T, M);

    for(k = 0; k < M/THREADS_MAX; k++){
        j = THREADS_MAX*k;
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

}

int main()
{
    srand(time(NULL));
    blackScholes();
    return 0;

}

void *myfunc(void *myvar){
    double* end = (double*)myvar;
    //printf("Valor recibo pela função da thread: %lf\n", *end);
    int i = (int)*end;
    //printf("Esse é o meu i %d\n", i);
    double aux = ((double)rand()/(double)RAND_MAX);
    //printf("Esse é o meu aux %lf, %lf\n", aux, T);
    double t = S * exp( ( ( r - ( 0.5*pow(sigma, 2) ) ) * T ) + (sigma*sqrt(T)*aux) );
    //printf("trials %lf\n", t);
   
    if(t-E > 0){
        trials[i] = exp( (-r)*T ) * (t-E);
        //printf("trials %lf\n", trials[i]);
    }else{
        trials[i] = 0;
        //printf("CASO 0 Esse é o meu trials %lf\n", trials[i]);
    }
    return NULL;
}