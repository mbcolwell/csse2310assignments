char ** matchWords(char * letters, char letter, char ** words, int nWords, int * nMatched) {
    char ** matchedWords;
    int nLetters, i, j;

    while (letters[nLetters] != '\0') nLetters++;

    int * matched = malloc(sizeof(int) * nWords);  // 1 = match, 0 = not match

    for (i=0; i<nWords; i++) {
        for (j=0; j<51; j++) {
            if (words[i][j] == '\0') {
                break;
            }
        }
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
