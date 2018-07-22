#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>

#define POSITIVE 11
#define NEGATIVE 12

#define MAX_BCD_LEN 10

int getNumberOfDigits(int n);
int encodeBCD(int number, char **buffer);
int containsSign(unsigned char c);
int decodeBCD(int *number, char *buffer);
int getBufferLen(char *buffer);
void addDigit(char c, int *number, int *sign);

int main(){
    int n = -23678;
    char *buffer = NULL;
    int bufferLen;
    int i;

    bufferLen = encodeBCD(n, &buffer);

    for (i=0; i<bufferLen; i++){
        printf("0x%x ",(unsigned char)buffer[i]);
    }

    bufferLen = decodeBCD(&n, buffer);

    printf("\nbuffer length: %d\t%d\n",bufferLen, n);

    return 0;
}

int encodeBCD(int number, char **buffer){
    int lenOfBuffer;
    int numberOfDigitsInNumber = getNumberOfDigits(number);
    int i;
    unsigned char c = 0;

    /*  record sign */
    int sign = NEGATIVE;

    if (number > 0){
        sign = POSITIVE;
    } else {
        number = number*-1;
    }

    /*  compute buffer's length and allocate it's memory    */
    lenOfBuffer = (numberOfDigitsInNumber + 1) / 2 + (numberOfDigitsInNumber%2==0);
    *buffer = (char*) malloc (lenOfBuffer* sizeof(int));

    /*  compress    */
    for (i=0; i<numberOfDigitsInNumber/2; i++){
        /*  insert first 4 bytes of last digit in number    */
        c |= number%10;
        c <<= 4;

        /*  chop number's last digit    */
        number /= 10;

        /*  insert last 4 bytes of last digit in number    */
        c |= number%10;

        /*  chop number's last digit    */
        number /= 10;
        /*  after we are done compressing c we insert it to array   */
        (*buffer)[i] = c;

        /*  re-initialize char  */
        c = 0;
    }
    /*  check if number of digits is uneven */
    if (numberOfDigitsInNumber%2 == 1){
        c |= number%10;
        c <<= 4;
    }
    /*  add sign    */
    c |= sign;
    (*buffer)[i] = c;

    return lenOfBuffer;
}

int getNumberOfDigits(int n){
    int numberOfDigits = 0;

    while (n){
        numberOfDigits++;
        n /= 10;
    }

    return numberOfDigits;
}

int decodeBCD(int *number, char *buffer){
    *number = 0;
    int bufferLen = getBufferLen(buffer);
    int i;
    int n;  /*  current number read from buffer */
    int sign = NEGATIVE;

    /*  iterate through buffer. each spot in buffer represents two numbers
     *  excluding buffer[bufferLen-1] which contains either number & sign
     *  or only sign    */
    for (i=bufferLen-1; i>=0; i--){
        /*  extract right number from buffer[i] */
        addDigit(buffer[i], number, &sign);

        buffer[i] >>= 4;

        /*  extract left number from buffer[i] */
        addDigit(buffer[i], number, &sign);
    }

    if (sign == NEGATIVE){
        *number = -(*number);
    }
    return getNumberOfDigits(n)/2 + (n%2==0);
}

void addDigit(char c, int *number, int *sign) {
    int n;

    n = c&0x0f;

    if (n == POSITIVE){
        *sign = POSITIVE;
    } else if (n != NEGATIVE){
        *number *= 10;
        *number += n;
    }
}

/*  returns buffer's length
 *  end of buffer is determined by having a NEGATIVE value or a POSITIVE value
 *  in buffer[i]
 * */
int getBufferLen(char *buffer) {
    int len = 0;
    int i=0;
    while (!containsSign(buffer[i])){
        i++;
        len++;
    }
    return len+1;
}
/*  returns true if given char contains the value POSITIVE or NEGATIVE
 * */
int containsSign(unsigned char c) {
    int i;

    for (i=0; i<2; i++){
        if ((c & 0x0f) == NEGATIVE || (c&0x0f) == POSITIVE){
            return 1;
        }
        c >>= 4;
    }
    return 0;
}
/*  writes number to file after encoding it
 * */
int cfwrite(FILE* fp,int number/*, (*2) */){
    char *buffer;
    int bufferLen;
    int i;

    bufferLen = encodeBCD(number,&buffer);  /* (*2) */

    for (i=0; i<bufferLen; i++){
        fputc(buffer[i],fp);
    }
}

int cfread(FILE* fp/*, (*1)*/){
    int n;
    char buffer[MAX_BCD_LEN];

    fgets(buffer,MAX_BCD_LEN,fp);
    buffer[strcspn(buffer," \n")] = '\0';

    decodeBCD(&n,buffer);   /*  (*1)    */
    return n;
}

extern struct EncodingFunctions;
typedef struct EncodingFunctions EncodingFunctions;
/*  generic function to set encoding    */
void setEncoding(EncodingFunctions *funcs, int(*encodeFunc)(int,char**),int(*decodeFunc)(int*,char*));