#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SHM_NAME "/s21_shared_memory"
#define MEM_SIZE 256

int main(void) {
    int fd;
    char* mem;
    int status;

    status = 0;
    mem = NULL;

    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        printf("Error: shm_open\n");
        status = 1;
    }

    if (status == 0) {
        if (ftruncate(fd, MEM_SIZE) == -1) {
            printf("Error: ftruncate\n");
            status = 1;
        }
    }

    if (status == 0) {
        mem = mmap(NULL, MEM_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
        if (mem == MAP_FAILED) {
            printf("Error: mmap\n");
            status = 1;
        }
    }

    if (status == 0) {
        strcpy(mem, "Hello from sender");
        printf("Sender: message sent\n");
    }

    if (mem != NULL && mem != MAP_FAILED)
        munmap(mem, MEM_SIZE);

    close(fd);

    return status;
}