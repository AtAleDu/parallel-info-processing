#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHM_NAME "/s21_shared_memory"
#define MEM_SIZE 256

int main(void) {
    int fd;
    char* mem;
    int status;

    status = 0;
    mem = NULL;

    fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (fd == -1) {
        printf("Error: shm_open\n");
        status = 1;
    }

    if (status == 0) {
        mem = mmap(NULL, MEM_SIZE, PROT_READ, MAP_SHARED, fd, 0);
        if (mem == MAP_FAILED) {
            printf("Error: mmap\n");
            status = 1;
        }
    }

    if (status == 0) {
        printf("Receiver got: %s\n", mem);
    }

    if (mem != NULL && mem != MAP_FAILED)
        munmap(mem, MEM_SIZE);

    close(fd);

    if (status == 0)
        shm_unlink(SHM_NAME);

    return status;
}