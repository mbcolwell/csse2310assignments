#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

    int p_id = 0;
    int n = 0;

    // Create 4 processes in series
    for (int i = 0; i<3; i++) {
        if (p_id == 0) {
            p_id = fork();
        }
    }

    printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());

    int res = wait(NULL);  // wait until child has finished

    if (res == -1) {
        printf("No children to wait for\n");
    } else {
        printf("%d finished execution\n", res);
    }

    printf("Hello World! %d\n", p_id);

    return 0;
}