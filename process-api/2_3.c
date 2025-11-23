#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main() {
    int f = open("process-api/2.txt", O_CREAT|O_RDWR, S_IRWXU);
    char buffer[100];
    for (int i = 0; i < sizeof(buffer); i++) {
        buffer[i] = '\0';
    }

    int parent_pid = (int) getpid();

    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        int child_pid = (int) getpid();
        char text[] = "hello ";

        int n = read(f, buffer, sizeof(buffer));
        if (n < 0) {
            fprintf(stderr, "Child (%d): can't read file", child_pid);
            return -1;
        }

        printf("Child (%d): open(%d), buffer(size: %d, content: %s), n(%d)\n", child_pid, f, sizeof(buffer), buffer, n);
        write(f, text, sizeof(text) - 1);
    } else{
        /*
        2:
        both of them can write in concurrent
        if parent waits, child can read file content and parent can't
        if parent does not wait, child can't read file content and parent can
        */

        int wc = wait(&rc);
        // 3. int wc = waitpid(rc, NULL, 0);
        char text[] = "goodbye ";

        int n = read(f, buffer, sizeof(buffer));
        if (n < 0) {
            fprintf(stderr, "Parent (%d): can't read file", parent_pid);
            return -1;
        }

        printf("Parent (%d): I'm the parent of %d, open(%d), buffer(size: %d, content: %s)\n", parent_pid, rc, f, sizeof(buffer), buffer);
        write(f, text, sizeof(text) - 1);
    }
}