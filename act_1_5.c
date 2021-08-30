#include<stdio.h>
#include<omp.h>
static long num_pasos = 100000000; //Divisiones
double paso;
#define NUM_THREADS 23
//int NUM_THREADS;
void main()
{
    //scanf("&d", &NUM_THREADS);
    int i, nthreads;
    double pi, sum[NUM_THREADS];
    paso = 1.0/num_pasos; //Divisiones (dx)
    omp_set_num_threads(NUM_THREADS);
    const double startTime = omp_get_wtime();
    #pragma omp parallel
    {
        int i, id, nthrds; double x;
        id = omp_get_thread_num(); //Identificador de thread actual
        nthrds = omp_get_num_threads(); //Numero total de threads
        if(id==0)
            nthreads=nthrds;
        for (i=id, sum[id]=0.0; i<num_pasos; i=i+nthrds){
            x=(i+0.5)*paso+1.0;
            sum[id]+=1.0/(x);
        }
    }

    for (i=0,pi=0.0;i<nthreads;i++){
        pi+=sum[i]*paso;
    }
    const double endTime = omp_get_wtime();
    printf("Resultado = (%lf)\n", pi);
    printf("%lf\n", (endTime - startTime));
}