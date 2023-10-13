#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int _wordMatch(char * letters, char l, char * word, int nLetters, int nWord) {
    // by this point letters, l, word are all uppercase
    // note could probably design a faster algorithm that sorts letters once and sorts word each time
    if (nWord > (nLetters + 1)) return 0;  // + 1 to include l

    char * loc;
    int * used = calloc(nLetters, sizeof(int));  // calloc initialises all to 0
    int i, j;
    int lLoc = -1;

    // first find l if necessary and record its location
    if (l != '\0') {
        loc = strchr(word, l);
        if (loc != NULL) {
            lLoc = (loc-word);
        } else {
            return 0;
        }
    }

    for (i=0; i<nWord; i++) {
        if (lLoc == -1 || lLoc == i) continue;  // Handling for l if matched

        do {
            loc = strchr(letters, l);
            j = (loc != NULL) ? (loc - letters) : -1;
        } while ((loc != NULL) && used[j]);

        if (loc != NULL) {
            used[j] = 1;
        } else {
            return 0;
        }
    }
    return 1;
}

char * _wordUpper(char * word) {
    // store word upper on stack
    char upperedWord[51];
    int i;

    for (i=0; i<51; i++) upperedWord[i] = toupper(word[i]);

    return upperedWord;
}

char ** matchWords(char * letters, char letter, char ** words, int nWords, int * nMatched) {
    int i, j;
    int nMatched = 0;
    int nLetters = 0;

    while (letters[nLetters] != '\0') nLetters++;
    char * upperLetters = _wordUpper(letter);
    char upperWord[51];

    int * matched = malloc(sizeof(int) * nWords);  // 1 = match, 0 = not match

    for (i=0; i<nWords; i++) {
        for (j=0; j<51; j++) {
            if (words[i][j] == '\0') {
                break;
            }
        }
        strcpy(upperWord, _wordUpper(words[i]));
        matched[i] = _wordMatch(upperWord, upperLetters, toupper(letter), nLetters, j);
        if (matched[i]) nMatched++;
    }

    
    char ** matchedWords = calloc(nMatched, sizeof(char *));
    j = 0;
    for (i=0; i<nMatched; i++) {
        while (!matched[j]) j++;
        matchedWords[i] = malloc(sizeof(char)*51);
        strcpy(matchedWords[i], words[j]);
    }

    return matchedWords;
}


int * sortMatched(char ** matchedWords, int nMatched, char sortMode) {
    int * sortOrder = (int *) malloc(sizeof(int) * nMatched);
    int i, j;

    switch (sortMode) {
        case 'd':
            for (i=0; i<nMatched; i++) sortOrder[i] = i;
            return sortOrder;
        case 'n':
            int nLength = 0;
            for (i=0; i<nMatched; i++) {
                for (j=0; j<51; j++) {
                    if (matchedWords[i][j] == '\0') break;
                }
                sortOrder[i] = j;
                if (j > nLength) nLength = j;
            }
            for (i=0; i<nMatched; i++) {
                if (sortOrder[i] < nLength) {
                    sortOrder[i] = -1;
                }
            }
            break;
        case 'l':
            for (i=0; i<nMatched; i++) sortOrder[i] = i;
            // pass
    }
    // do alpha sorting
    return sortOrder;
}
