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
    int i, j, c;
    int lLoc = -1;

    // first find l if necessary and record its location
    if (l != '\0') {
        lLoc = charIndex(word, l);
        if (lLoc == -1) {
            return 0;
        }
    }

    for (i=0; i<nWord; i++) {
        if (lLoc == i) continue;  // Handling for l if matched

        j=-1;
        do {
            // starting at letters+0 in char array, find next available character
            j++;
            c = charIndex((letters+j), word[i]);
            j += c;
        } while (c != -1 && used[j]);  // Exit if c == -1 OR used[j] == 1

        if (c != -1) {
            used[j] = 1;
        } else {
            // unable to find an available character for word[i] so return not matched
            return 0;
        }
    }
    // Made it through the whole word finding available characters so return matched
    return 1;
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
