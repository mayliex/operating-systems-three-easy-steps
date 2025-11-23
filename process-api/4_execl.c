#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

/*
execl - args as variadic list of params
execle - args as variadic list of params and custom env
*/

int
main() {
    int parent_pid = (int) getpid();

    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        int child_pid = (int) getpid();
        printf("Child (%d):", child_pid);
        execl(strdup("/bin/ls"), strdup("/bin/ls"), strdup("-al"), NULL);
        execle(strdup("/bin/ls"), strdup("/bin/ls"), strdup("-al"), NULL);
        // after that everything is replaced by /bin/ls
        printf("this shouldn’t print out");
        printf("this shouldn’t print out");
    } else{
        int wc = wait(&rc);
        execl(strdup("/bin/ls"), strdup("/bin/ls"), strdup("-al"), NULL);
        execle(strdup("/bin/ls"), strdup("/bin/ls"), strdup("-al"), NULL);
        printf("Parent (%d): I'm the parent of %d\n", parent_pid, rc);
        // after that everything is replaced by /bin/ls
        printf("this shouldn’t print out");
        printf("this shouldn’t print out");
    }
}