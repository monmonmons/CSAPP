#include "csapp.h"
#define MAXTHREADS 32

void *sum_local(void *vargp); /* Thread routine */

/* Global shared variables */
long gsum = 0;              /* Global sum */
int *psum;             
long nelems_per_thread; /* Number of elements to sum */
sem_t mutex;            /* Mutex to protect global sum */

int main(int argc, char **argv)
{
    long i, nelems, log_nelems, nthreads, myid[MAXTHREADS];
    pthread_t tid[MAXTHREADS];

    /* Get input arguments */
    if (argc != 3) {
        printf("Usage: %s <nthreads> <log_nelems>\n", argv[0]);
        exit(0);
    }
    nthreads = atoi(argv[1]);
    log_nelems = atoi(argv[2]);
    nelems = (1L << log_nelems);
    nelems_per_thread = nelems / nthreads;
    Sem_init(&mutex, 0, 1);
    psum = calloc(nthreads, sizeof(int));

    /* Create peer threads and wait for them to finish */
    for (i = 0; i < nthreads; i++) {
        myid[i] = i;
        Pthread_create(&tid[i], NULL, sum_local, &myid[i]);
    }
    for (i = 0; i < nthreads; i++)
        Pthread_join(tid[i], NULL);

    for (i = 0; i < nthreads; i++)
        gsum += psum[i];
        
    /* Check final answer */
    if (gsum != (nelems * (nelems - 1)) / 2)
        printf("Error: result=%ld\n", gsum);
    else
        printf("OK! result=%ld\n", gsum);
    
    free(psum);

    exit(0);
}


/* Thread routine for psum-local.c */
void *sum_local(void *vargp)
{
    long myid = *((long *)vargp);          /* Extract the thread ID */
    long start = myid * nelems_per_thread; /* Start element index */
    long end = start + nelems_per_thread;  /* End element index */
    long i, sum = 0;

    for (i = start; i < end; i++) {
        sum += i;                       /* Local variable */
    }
    psum[myid] = sum;
    return NULL;
}