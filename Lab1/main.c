#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;

static void* writer(void* arg);
static void* reader(void* arg);

int main(void) {
    pthread_t writer1;
    pthread_t writer2;
    pthread_t reader_thread;

    int status;
    int result;

    result = 0;

    status = pthread_mutex_init(&mutex, NULL);
    if (status != 0)
        result = 1;

    if (result == 0) {
        status = pthread_cond_init(&not_full, NULL);
        if (status != 0)
            result = 1;
    }

    if (result == 0) {
        status = pthread_cond_init(&not_empty, NULL);
        if (status != 0)
            result = 1;
    }

    if (result == 0) {
        status = pthread_create(&writer1, NULL, writer, NULL);
        if (status != 0)
            result = 1;
    }

    if (result == 0) {
        status = pthread_create(&writer2, NULL, writer, NULL);
        if (status != 0)
            result = 1;
    }

    if (result == 0) {
        status = pthread_create(&reader_thread, NULL, reader, NULL);
        if (status != 0)
            result = 1;
    }

    if (result == 0) {
        pthread_join(writer1, NULL);
        pthread_join(writer2, NULL);
        pthread_join(reader_thread, NULL);
    }

    return result;
}

static void* writer(void* arg) {
    void* result;

    (void)arg;
    result = NULL;

    while (1) {
        int value;

        value = rand() % 100;

        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &mutex);

        buffer[in] = value;

        in = (in + 1) % BUFFER_SIZE;

        count = count + 1;

        printf("Writer wrote: %d\n", value);

        pthread_cond_signal(&not_empty);

        pthread_mutex_unlock(&mutex);

        usleep(500000);
    }

    return result;
}

static void* reader(void* arg) {
    void* result;

    (void)arg;
    result = NULL;

    while (1) {
        int value;

        pthread_mutex_lock(&mutex);

        while (count == 0)
            pthread_cond_wait(&not_empty, &mutex);

        value = buffer[out];

        out = (out + 1) % BUFFER_SIZE;

        count = count - 1;

        printf("Reader read: %d\n", value);

        pthread_cond_signal(&not_full);

        pthread_mutex_unlock(&mutex);

        usleep(700000);
    }

    return result;
} 
