#include <stdio.h>
#include <stdlib.h>

/***************/
/*  2013 b q4  */
/***************/
void printLetters(FILE *fp, int n);

int main(int argc, char **argv){
    FILE* fp;
    long fileLen;
    int n;

    if (argc < 3){
        printf("ERROR: expected <./execution_file> <filename> <n value>\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");
    n = atoi(argv[2]);
    if (!fp){
        printf("ERROR: couldn't open %s\n",argv[1]);
        exit(2);
    }

    fseek(fp, 0, SEEK_END);
    fileLen = ftell(fp);
    /*  first five  */
    rewind(fp);
    printLetters(fp, n);

    /*  middle five */
    fseek(fp, fileLen/2 - n/2-1, SEEK_SET);
    printLetters(fp, n);

    /*  last five   */
    fseek(fp, fileLen-n, SEEK_SET);
    printLetters(fp, n);
}


/*  input: poiner to file
 *  output: none
 *
 *  prints n chars from current position in file to screen
 * */
void printLetters(FILE *fp, int n) {
    int i;

    for (i=0; i<n; i++){
        putchar(fgetc(fp));
    }
}