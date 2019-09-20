#include "unif01.h"
#include "bbattery.h"
#include <stdio.h>
#include <math.h>


#define bit 32

FILE *fp;

unsigned int dev_urandom(void){ // = /dev/random for macOS
    unsigned int data;
    fread(&data, 4, 1, fp);
    return data;
}

int main(void){
    unif01_Gen *gen;  // RNG Object
    fp = fopen("/dev/urandom", "r");
    gen = unif01_CreateExternGenBits ("/dev/urandom", dev_urandom);

    // Tests
    long int nb = pow(2, 30);
    int times = 100;
    int i;
    printf("=== SmallCrush ===\n");
    for(i = 0; i<times; ++i)
        bbattery_SmallCrush(gen);
    printf("=== Rabbit ===\n");
    for(i = 0; i<times; ++i)
        bbattery_Rabbit(gen, nb);
    printf("=== Alphabit ===\n");
    for(i = 0; i<times; ++i)
        bbattery_Alphabit(gen, nb, 0, bit);
    // End tests

    unif01_DeleteExternGen01 (gen);
    fclose(fp);

    return 0;
}
