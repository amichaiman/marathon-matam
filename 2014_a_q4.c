#include <stdio.h>

#define BITS_IN_BYTE 8

unsigned int permute(unsigned int n, int *permutation);

int main(){
    int permutations[] = {0,1,2,3,4,5,6,7,8,9,
                          10,11,12,13,14,15,16,17,18,19,
                          20,21,22,23,24,25,26,27,28,29,
                          30,31};

    printf("the new value of %u is %d\n", 1234, permute(1234,permutations));
    return 0;
}

unsigned int permute(unsigned int n, int *permutation){
    unsigned int res = 0;
    int i;

    for (i=BITS_IN_BYTE*sizeof(int)-1; i>0; i--){
        /*  add the bit that is in location permutation[i] */
        res |= n>>permutation[i]&0x1;
        res <<= 1;
    }

    return res;
}