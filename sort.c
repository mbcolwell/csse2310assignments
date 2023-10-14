#include <stdlib.h>


// Functions necessary for alpha sort
int _asciiToOrder(char c) {
    int i = (int) c;
    return i % 32 + i/32;
}

int _asciiCompare(const char * a, const char * b) {
    // We want to achieve ordering such that AaBbCc...
    // Convert ascii to int with A=1, a=2, B=3 ...

    if (a[0] == '\0' && b[0] == '\0') {
        return 1;  // Edge case for both words are the same
    }

    int aVal = _asciiToOrder(a[0]);
    int bVal = _asciiToOrder(b[0]);

    if (aVal > bVal) {
        return 1;
    }
    if (bVal > aVal) {
        return -1;
    }
    return _asciiCompare((a+1), (b+1));
}

int _qsortChar(const void* a, const void* b) {
    return _asciiCompare(*(const char**)a, *(const char**)b); 
}

void _alphaSort(char ** words, int n) {
    qsort(words, n, sizeof(const char*), _qsortChar); 
}

// Function necessary for longest words only
int * _wordLengths(char ** words, int n, int * maxLength, int * nMatched) {
    int i, j;
    int * wordLengths = malloc(sizeof(int)*n);

    for (i=0; i<n; i++) {
        for (j=0; j<51; j++) {
            if (words[i][j] == '\0') break;
        }
        wordLengths[i]=j;
        if (j == *maxLength) (*nMatched)++; 
        if (j > *maxLength) {
            *maxLength = j;
            *nMatched = 1;
        }
    }
    return wordLengths;
}

// Functions necessary for length sort
int _lengthCompare(const char * a, const char * b) {
    // We want to achieve ordering such that AaBbCc...
    // Convert ascii to int with A=1, a=2, B=3 ...

    int aLen = 0;
    int bLen = 0;

    while (a[aLen] != '\0') aLen++;
    while (b[bLen] != '\0') bLen++;

    return -1*(aLen - bLen);
}

int _qsortLength(const void* a, const void* b) {
    return _lengthCompare(*(const char**)a, *(const char**)b); 
}

void _lenSort(char ** words, int n) {
    qsort(words, n, sizeof(const char*), _qsortLength); 
}

// Function called in main() to sort words array
void sortWords(char *** words, int n, char sortMode, int * nMatched) {

    switch (sortMode) {
        case 'd':
            return;
        case 'n':
            _alphaSort(*words, n);
            int i, j;
            int maxLength = 0;
            *nMatched = 1;
            int * wordLengths = _wordLengths(*words, n, &maxLength, nMatched);
            char ** longWords = malloc(sizeof(char *)*(*nMatched));

            j=0;
            for (i=0; i<n; i++) {
                if (wordLengths[i] < maxLength) {
                    free((*words)[i]);
                } else {
                    longWords[j] = (*words)[i];
                    j++;
                }
            }
            *words = longWords;
            free(wordLengths);
            break;
        case 'l':
            _alphaSort(*words, n);
            _lenSort(*words, n);
            break;
        case 'a':
            _alphaSort(*words, n);
            break;
    }
}
