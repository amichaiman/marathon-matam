#include <stdio.h>
#include <stdlib.h>

/*  a.  */
void copyBits(int *pRes, int *pN, int n) {
    int i;

    for (i=0; i<n; i++){
        (*pRes) |= (*pN)&0x80000000;
        (*pN) <<= 1;
        (*pRes) <<= 1;
    }
}

int updateBits(int n, int m, int i, int j){
    int res=0;
    int k;

    /*  copy left bits to res   */
    copyBits(&res, &n, 32-j);

    for (k=0; k<32-(j-i+1); k++){
        m <<= 1;
    }

    /*  copy bits from m to res   */
    copyBits(&res, &m, j-i+1);


    /*  copy right bits to res   */
    copyBits(&res,&n,i);

    return n;
}



