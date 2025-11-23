#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/*
p - search in PATH if no /
execvp - args as vector of params search in PATH if no "/" in the beginning
execvP - with custom search path
*/

int
main() {
    int parent_pid = (int) getpid();

    char *myargs[3];
    myargs[0] = strdup("/bin/ls");
    myargs[1] = strdup("-al");
    myargs[2] = NULL;

    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        int child_pid = (int) getpid();
        printf("Child (%d):", child_pid);
        execvp(myargs[0], myargs);
        // after that everything is replaced by /bin/ls
        printf("this shouldn’t print out");
        printf("this shouldn’t print out");
    } else{
        // int wc = wait(&rc);
        execvp(myargs[0], myargs);
        printf("Parent (%d): I'm the parent of %d\n", parent_pid, rc);
        // after that everything is replaced by /bin/ls
        printf("this shouldn’t print out");
        printf("this shouldn’t print out");
    }
}