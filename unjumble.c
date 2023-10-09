#include <stdio.h>
#include "read_cli.h"

int main(int argc, char **argv) {
    char mode = 'd';  // for default
    char l = '\0';
    char letters[51] = {0};
    char dictPath[255] = {0};

    setCmdArgs(&mode, &l, letters, dictPath, argc, argv);
    printf("Mode: %c\nletter: %c\nletters: %s\ndictPath: %s\n", mode, l, letters, dictPath);

    return 0;
}
