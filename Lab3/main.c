#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define COUNT 10
#define MSG "Hello!\n"

int main(void) {
    int fd[2];
    pid_t pid;
    int status;

    status = 0;
    pid = -1;

    if (pipe(fd) == -1) {
        perror("pipe failed");
        status = 1;
    }

    if (status == 0) {
        pid = fork();

        if (pid < 0) {
            perror("fork failed");
            status = 1;
        }
    }

    /* WRITER */
    if (status == 0 && pid > 0) {
        close(fd[0]);

        for (int i = 0; i < COUNT && status == 0; i++) {
            if (write(fd[1], MSG, strlen(MSG)) == -1) {
                perror("write failed");
                status = 1;
            } else {
                printf("Writer sent: Hello!\n");
                sleep(2);
            }
        }

        close(fd[1]);
        wait(NULL);
    }

    /* READER */
    if (status == 0 && pid == 0) {
        char buffer[64];
        ssize_t bytes;

        close(fd[1]);

        bytes = read(fd[0], buffer, sizeof(buffer) - 1);

        while (bytes > 0 && status == 0) {
            buffer[bytes] = '\0';
            printf("Reader received: %s", buffer);

            bytes = read(fd[0], buffer, sizeof(buffer) - 1);
        }

        if (bytes == -1) {
            perror("read failed");
            status = 1;
        }

        close(fd[0]);
    }

    return (status);
}