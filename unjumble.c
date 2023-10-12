#include <stdio.h>
#include "read_cli.h"
#include "read_dict.h"
#include "matching.h"


int main(int argc, char **argv) {
    char sortMode = 'd';  // for default
    char l = '\0';
    char letters[51] = {0};
    char dictPath[255] = {0};
    int nWords, nMatched;

    setCmdArgs(&sortMode, &l, letters, dictPath, argc, argv);
    if (letters[0] == '\0') {
        return 1;
    }
    // printf("Mode: %c\nletter: %c\nletters: %s\ndictPath: %s\n", mode, l, letters, dictPath);

    char **words = readDictionary(dictPath, &nWords);  // start a pointer to an array of strings
    // int i;
    // for (i=0; i<nWords; i++) {
    //     printf("%s\n", words[i]);
    // }
    // printf("%d\n", nWords);
    char **matchedWords = matchWords(letters, l, words, nWords, &nMatched);
    freeWords(words, nWords);
    int *matchOrder = sortMatched(matchedWords, nMatched, sortMode);

    int i;
    for (i=0; i<nMatched; i++) {
        printf("%s", matchedWords[matchOrder[i]]);
    }
    freeWords(matchedWords);

    return 0;
}
