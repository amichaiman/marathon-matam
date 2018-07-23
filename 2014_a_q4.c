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
    int i;
    int newNum = 0;
    int bitToAdd = 0;
    //  000..000 1010 0010
    //  n>>1
    //  000..000 0101 0001
    // &000..000 0000 0001
    //  000..000 0000 0000
    // |000..000 0000 0001

    for (i=0; i<BITS_IN_BYTE*sizeof(int); i++){
        bitToAdd = getBit(n, permutation[i]);
        newNum = setBit(newNum, i, bitToAdd);
    }

    return newNum;
}


int setBit(int c, int i, int val){
    int mask = 1 << i;
    if(val == 1){
        return c | mask;
    } else {
        return c & ~mask;
    }
}

int getBit(int c, int i){
    int mask = 1 << i;

    return (c&mask) >> i;
}