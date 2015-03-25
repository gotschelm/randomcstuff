#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<linux/types.h>
#include<stdint.h>


#define ISON(n) ( grid[(n)/8] & (1<<((n)%8)) )
#define SETOFF(n) grid[(n)/8] &= ~(1<<((n)%8));

int main(int argc, char* argv[]){
    uint64_t max = 100;
    register unsigned char *grid;
    uint64_t i, j;

//    printf("size of unsigned long long: %d\n", sizeof(unsigned long long));
//    printf("size of uint64_t: %d\n", sizeof(uint64_t));
    
    if ( argc > 1 ) {
       max = strtoull(argv[1], NULL, 0);
    }

    grid = malloc(max/8);
    memset(grid,0xaa,max/8); // 10101010 multiples of 2 are already set to 0
    memset(grid,0b10101100,1);

    for (i=3; i<(uint64_t)sqrt(max); i++) {
        if ( ISON(i) ) {
            for (j=(uint64_t)pow(i,2);j<max;j+=i) {
                SETOFF(j)
            }
        }
    }

//    for (i=0;i<max;i++) {
//        if ( ISON(i) ) {
//            printf("%d\n", i);
//        }
//    }




    free(grid);

    return 0;
}
// 2014-6-10
