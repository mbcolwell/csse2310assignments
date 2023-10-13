#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int charIndex(char * word, char letter) {
    if (letter == '\0') return -1;
    char * loc = strchr(word, letter);
    return (loc != NULL) ? (loc-word) : -1;
}

int _wordMatch(char * letters, char l, char * word, int nLetters, int nWord) {
    // by this point letters, l, word are all uppercase
    // note could probably design a faster algorithm that sorts letters once and sorts word each time
    if (nWord > (nLetters + 1)) return 0;  // + 1 to include l

    int * used = calloc(nLetters, sizeof(int));  // calloc initialises all to 0
    int i, j;
    int lLoc = -1;
    int nMatched = 0;

    // first find l if necessary and record its location
    if (l != '\0') {
        lLoc = charIndex(word, l);
        if (lLoc == -1) {
            return 0;
        }
        nMatched++;
    }

    for (i=0; i<nWord; i++) {
        if (lLoc == i) continue;  // Handling for l if matched

        j=-1;
        do {
            // starting at letters+0, move pointer to next position in letters if 
            j = charIndex((letters+j+1), word[i]);
        } while (j != -1 && used[j]);  // Exit if j == -1 OR used[j] == 1

        if (j != -1) {
            used[j] = 1;
            nMatched++;
        }
    }
    return (nMatched==nWord);
}

char * _wordUpper(char * word) {
    // store word upper on stack
    char * upperedWord = malloc(sizeof(char)*51);
    int i;

    for (i=0; i<51; i++) upperedWord[i] = toupper(word[i]);

    return upperedWord;
}

char ** matchWords(char * letters, char l, char ** words, int nWords, int * nMatched) {
    int i, j;
    int nLetters = 0;
    *nMatched = 0;

    while (letters[nLetters] != '\0') nLetters++;
    char * upperLetters = _wordUpper(letters);
    char upperWord[51];

    int * matched = malloc(sizeof(int) * nWords);  // 1 = match, 0 = not match

    for (i=0; i<nWords; i++) {
        for (j=0; j<51; j++) {
            if (words[i][j] == '\0') {
                break;
            }
        }
        
        char * _upper = _wordUpper(words[i]);
        strcpy(upperWord, _upper);
        free(_upper);

        matched[i] = _wordMatch(upperLetters, toupper(l), upperWord, nLetters, j);
        if (matched[i]) {
            (*nMatched)++;
        }
    }

    
    char ** matchedWords = calloc(*nMatched, sizeof(char *));
    j = 0;
    for (i=0; i<*nMatched; i++) {
        while (!matched[j]) j++;
        matchedWords[i] = malloc(sizeof(char)*51);
        strcpy(matchedWords[i], words[j]);
        j++;
    }

    free(matched);
    return matchedWords;
}
