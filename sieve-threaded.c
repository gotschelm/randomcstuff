#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<linux/types.h>
#include<stdint.h>
#include<unistd.h>
#include<pthread.h>

#define ISON(n) ( grid[(n)/8] & (1<<((n)%8)) )
#define SETOFF(n) ( grid[(n)/8] &= ~(1<<((n)%8)) )

typedef struct targs {
    uint64_t i;
    uint64_t j;
} walkargs;

uint64_t max = 100;
int numthreads=0;
int maxthreads=4;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t *tid;

unsigned char *grid;

void *walkovergrid(void *args){
    //	walkargs *threadargs = (walkargs*)args;
    uint64_t i = ((walkargs*)args)->i;
    uint64_t j = ((walkargs*)args)->j;

    for (j;j<max;j+=i) {
        SETOFF(j);
        //		usleep(1000*500);
    }
    //	printf("Finished deleting multiples of %u\n", i);
    pthread_mutex_lock(&mutex);
    numthreads--;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}


int main(int argc, char* argv[]){
    uint64_t i, j;
    uint64_t ti=0;
    walkargs *threadargs;

    //printf("size of unsigned long long: %d\n", sizeof(unsigned long long));
    //printf("size of uint64_t: %d\n", sizeof(uint64_t));

    if ( argc > 1 ) {
        max = strtoull(argv[1], NULL, 0);
    }

    grid = malloc(max/8);
    memset(grid,0xaa,max/8); // 10101010 multiples of 2 are already set to 0
    memset(grid,0b10101100,1);

    threadargs = malloc(sqrt(max) * sizeof(walkargs));
    tid = malloc(sqrt(max) * sizeof(pthread_t));

    for (i=3; i<(uint64_t)sqrt(max); i++) {
        if ( ISON(i) ) {
            j = (uint64_t)pow(i,2);
            SETOFF(j);
            threadargs[ti].i=i;
            threadargs[ti].j=j;
            //		printf("creating thread %d to remove multiples of %d\n", ti, i);
            pthread_create(&tid[ti], NULL, walkovergrid, (void *)&threadargs[ti]);
            numthreads++;
            ti++;
            pthread_mutex_lock(&mutex);
            //		printf("numthreads is %d and maxthreads is %d\n", numthreads, maxthreads);
            while ( numthreads >= maxthreads ) {
                pthread_cond_wait(&cond, &mutex);
            }
            pthread_mutex_unlock(&mutex);
        }

    }
    // uncomment to print numbers
    //int t=0;
    //int rc;
    //for(t=ti-maxthreads; t<ti; t++){
    //    printf("In main: joining thread #%d\n", t);
    //    rc = pthread_join(tid[ti-t], NULL);
    //    if (rc) { fprintf(stderr, "failed to join thread #%ld - %s\n",
    //            (long)t, strerror(rc));
    //    exit(EXIT_FAILURE);
    //    }
    //}

    //for (i=0;i<max;i++) {
    //    if ( ISON(i) ) {
    //        printf("%d\n", i);
    //    }
    //}

    free(grid);

    pthread_exit(NULL);
}
