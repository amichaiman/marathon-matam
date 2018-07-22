#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TRUE 1
#define FALSE 0

int sentenceFoundExactlyInMiddle(FILE* fp, long fileLen, char *line, char *sentence, unsigned long startIndexOfSentenceInLine);

int main(int argc, char **argv) {
    FILE* fp;
    char *line = NULL;
    char *locOfSentenceInLine = NULL;
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
        locOfSentenceInLine = strstr(line,argv[2]);
        if (locOfSentenceInLine != NULL) {
            if (!sentenceFoundExactlyInMiddle(fp, fileLen, line, argv[2], locOfSentenceInLine - line)){
                /*  check if we are in first half or second */
                if (ftell(fp) < fileLen/2){
                    /*  check if the sentence appears twice in first half   */
                    if (foundSentence[0]){
                        printf("sentence appears twice in first half\n");
                        return 0;
                    }
                    foundSentence[0] = TRUE;
                } else {
                    /*  check if the sentence appears twice in first half   */
                    if (foundSentence[1]){
                        printf("sentence appears twice in second half\n");
                        return 0;
                    }
                    foundSentence[1] = TRUE;
                }
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

/*  returns true if file starts in first half && ends in second half 
 * */
int sentenceFoundExactlyInMiddle(FILE* fp, long fileLen, char *line, char *sentence, unsigned long startIndexOfSentenceInLine){
    /*  if sentence starts in first half && ends in second half */
    if (ftell(fp) - strlen(line) + startIndexOfSentenceInLine < fileLen/2
            && ftell(fp) - strlen(line) + startIndexOfSentenceInLine + strlen(sentence) > fileLen/2){
        return 1;
    }
    return 0;
}