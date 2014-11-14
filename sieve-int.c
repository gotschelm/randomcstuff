#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define N 1000000

#define ISON(n) ( grid[(n)/8] & (1<<((n)%8)) )
#define SETOFF(n) grid[(n)/8] &= ~(1<<((n)%8));

int main(int argc, char* argv[]){
    int max = 100;
    int *grid;
    int i, j, z;

    if ( argc > 1 ) {
       max = atoi(argv[1]);
    }

    grid = malloc(max*sizeof(int));
    memset(grid,0xff,max*sizeof(int));
    memset(grid,0x0,2);

    for (i=2; i<(int)sqrt(max); i++) {
        if ( grid[i] != 0 ) {
            for (j=(int)pow(i,2);j<max;j+=i) {
                grid[j] = 0;
            }
        }
    }
/*
    for (i=0;i<max;i++) {
        if ( ISON(i) ) {
            printf("%d\n", i);
        }
    }
    */


    free(grid);

    return 0;
}
// 2014-6-10
