#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define SHM_NAME "/s21_shared_memory"
#define MEM_SIZE 256

int main(void) {
    int fd;
    char* mem = NULL;
    pid_t pid = -1;
    int status = 0;

    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    if (fd == -1) {
        printf("Error: shm_open failed\n");
        status = 1;
    }

    if (status == 0 && ftruncate(fd, MEM_SIZE) == -1) {
        printf("Error: ftruncate failed\n");
        status = 1;
    }

    if (status == 0) {
        mem = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        if (mem == MAP_FAILED) {
            printf("Error: mmap failed\n");
            status = 1;
        }
    }

    if (status == 0) {
        mem[0] = '\0';

        pid = fork();

        if (pid == -1) {
            printf("Error: fork failed\n");
            status = 1;
        }
    }

    if (status == 0 && pid == 0) {
        printf("Receiver: waiting...\n");

        while (mem[0] == '\0') {
            usleep(100000);
        }

        printf("Receiver got message: %s\n", mem);

        munmap(mem, MEM_SIZE);
        close(fd);
    }

    if (status == 0 && pid > 0) {
        sleep(3);

        strcpy(mem, "Hello from sender process");

        printf("Sender: message sent\n");

        wait(NULL);

        munmap(mem, MEM_SIZE);
        close(fd);
        shm_unlink(SHM_NAME);
    }

    return status;
}
