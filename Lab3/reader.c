#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "myfifo"

int main(void) {
    int fd;
    int status;
    char buffer[64];
    char c;       // символ для посимвольного чтения
    int i;        // индекс в буфере
    ssize_t bytes;// количество прочитанных байт

    status = 0;
    fd = -1;
    i = 0;

    mkfifo(FIFO_NAME, 0666);

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        status = 1;
    }

    if (status == 0) {
        bytes = read(fd, &c, 1);

        while (bytes > 0 && status == 0) {
            buffer[i] = c;
            i++;

            if (c == '\n') {
                buffer[i] = '\0';
                printf("Reader received: %s", buffer);
                i = 0;
                sleep(3);
            }

            bytes = read(fd, &c, 1);
        }

        if (bytes == -1) {
            perror("read failed");
            status = 1;
        }
    }

    if (fd != -1) {
        close(fd);
    }

    return status;
}