#include<stdio.h>
#include<math.h>

#define N 1000000

#define ISON(n) ( grid[n/8] & (1<<n%8) )
#define SETOFF(n) ( grid[n/8] &= ~(1<<n%8) );

int main() {

    char grid[N] = { [0 ... N-1] = 0xFF };
    int i, j;

    grid[0] = 0b11111100;

    for (i=0; i<(int)sqrt(N); i++) {
        if ( ISON(i) ) {
            for (j=(int)pow(i,2);j<N;j+=i){
                SETOFF(j)
            }
        }
    }



    for (i=0; i<N; i++){
        if ( ISON(i) ) {
            printf("%d\n", i);
        }
    }

    return 0;
    }

// 2014-6-10
