#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int 
main(){
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        int child_pid = wait(&rc); // -1
        printf("Child (%d): child_pid(%d)\n", (int) getpid(), child_pid);
    } else{
        int child_pid = wait(&rc); // returns child's pid
        printf("Parent (%d): I'm the parent of %d, child_pid(%d)\n", (int) getpid(), rc, child_pid);
    }
    return 0;
}