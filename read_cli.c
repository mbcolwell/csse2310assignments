#include <string.h>
#include <stdio.h>

void setMode(char * currentMode, char set) {
    if (*currentMode != 'd') {
        *currentMode = 'i';  // invalid input
    } else {
        *currentMode = set;
    }
}

void setCmdArgs(
    char * mode, 
    char * l, 
    char letters[51], 
    char dictPath[255], 
    int argc, 
    char **argv
) {
    int i;
    for (i=1; i<argc; i++) {
        if (!strcmp(argv[i], "-alpha")) {
            setMode(mode, 'a');
        } else if (!strcmp(argv[i], "-len")) {
            setMode(mode, 'n');
        } else if (!strcmp(argv[i], "-longest")) {
            setMode(mode, 'l');
        } else if (!strcmp(argv[i], "-include")) {
            i++;
            *l = (*argv[i]);
            if (*(argv[i]+1) != '\0') {
                printf(
                    "Warning - multiple include letters passed, using first\n"
                );
            }
        } else if (argv[i][0] != '-' && letters[0] == '\0') {
            strcpy(letters, argv[i]);
        } else if (argv[i][0] != '-' && dictPath[0] == '\0') {
            strcpy(dictPath, argv[i]);
        } else {
            printf("Unknown argument passed: %s\n", argv[i]);
            return;
        }
    }
    if (dictPath[0] == '\0') {
        strcpy(dictPath, "/usr/share/dict/words");
    }
}
