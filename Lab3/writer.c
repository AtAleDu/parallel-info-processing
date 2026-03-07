#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "myfifo"
#define COUNT 10
#define MSG "Hello!\n"

int main(void) {
    int fd;
    int status;

    status = 0;
    fd = -1;

    mkfifo(FIFO_NAME, 0666);

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        status = 1;
    }

    if (status == 0) {
        for (int i = 0; i < COUNT && status == 0; i++) {
            if (write(fd, MSG, strlen(MSG)) == -1) {
                perror("write failed");
                status = 1;
            } else {
                printf("Writer sent: Hello! (%d/%d)\n", i + 1, COUNT);
                sleep(2);
            }
        }
    }

    if (fd != -1) {
        close(fd);
    }

    return status;
}