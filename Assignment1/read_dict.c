#include <stdio.h>
#include <stdlib.h>

char **readDictionary(char * dictPath, int * nWords) {
    const int maxWordSize = 50;
    int i, message;
    char **words = (char **) malloc(sizeof(char *)*10);
    FILE *dict = fopen(dictPath, "r");

    i = 0;
    do {
        if (i % 10 && i != 0) {
            words = (char **) realloc(words, sizeof(char *)*10*(i/10+1));
        }
        char *word = malloc(maxWordSize+1);
        message = fscanf(dict, "%s", word);
        words[i] = word;
        i++;
    }
    while (message != EOF);

    // last word read will be EOF so decrement i and free
    i--;
    free(words[i]);

    *nWords = i;
    return words;
}

void freeWords(char ** words, int nWords) {
    int i;
    for (i=0; i<nWords; i++) {
        free(words[i]);
    }
}
