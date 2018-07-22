#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char **argv) {
    FILE* fp;
    char *line = NULL;
    long fileLen;
    size_t len;
    int foundSentence[2] = {FALSE};

    if (argc < 3){
        printf("ERROR: expected <./executable> <filename> <string>");
        exit(1);
    }

    fp = fopen(argv[1], "r");

    if (!fp){
        printf("ERROR: couldn't open file\n");
        exit(1);
    }

    fseek(fp,0,SEEK_END);
    fileLen = ftell(fp);

    rewind(fp);

    /*  read line by line   */
    while(getline(&line, &len, fp) != -1){
        /*  search for sentence in line */
        if (strstr(line,argv[2]) != NULL) {
            /*  check if we are in first half or second */
            if (ftell(fp) < fileLen/2){
                foundSentence[0] = TRUE;
            } else {
                foundSentence[1] = TRUE;
            }
        }
        /*  crucial for getline function    */
        free(line);
        line = NULL;
    }

    printf("sentence%s found in both halfs!\n",foundSentence[0] == TRUE && foundSentence[1] == TRUE? "" : " not");
    fclose(fp);
    return 0;
}