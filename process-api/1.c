#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int 
main(){
    int x = 100;
    printf("Parent (%d): the value of x is %d\n", (int) getpid(), x);
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        x += 5;
        printf("Child (%d): x = %d\n", (int) getpid(), x);
    } else{
        x += 10;
        wait(&rc);
        printf("Parent (%d): I'm the parent of %d, my value of x is %d\n", (int) getpid(), rc, x);
    }
    return 0;
}