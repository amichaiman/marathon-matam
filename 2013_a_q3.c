#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE* outputFile;
    int i;

    if (argc < 3){
        printf("Error\n");
        exit(1);
    }

    for (i=2; i<argc; i++){
        outputFile = fopen(argv[i],"w");
        if (!outputFile){
            printf("Error printing to %s\n", argv[i]);
            exit(1);
        }
        fprintf(outputFile,"%s\n", argv[1]);
        fclose(outputFile);
    }

    return 0;
}