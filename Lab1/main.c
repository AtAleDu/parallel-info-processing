#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

typedef struct {
    int data[BUFFER_SIZE];
    int head;
    int tail;
    int size;
} Queue;

Queue queue;

pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;

static void enqueue(int value);
static int dequeue(void);

static void* writer(void* arg);
static void* reader(void* arg);

int main(void) {
    pthread_t writer1;
    pthread_t writer2;
    pthread_t reader_thread;

    int status;
    int result = 0;

    queue.head = 0;
    queue.tail = 0;
    queue.size = 0;

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

static void enqueue(int value) {
    queue.data[queue.tail] = value;
    queue.tail = (queue.tail + 1) % BUFFER_SIZE;
    queue.size++;
}

static int dequeue(void) {
    int value = queue.data[queue.head];
    queue.head = (queue.head + 1) % BUFFER_SIZE;
    queue.size--;
    return value;
}

static void* writer(void* arg) {
    (void)arg;

    while (1) {
        int value = rand() % 100;

        pthread_mutex_lock(&mutex);

        while (queue.size == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &mutex);

        enqueue(value);

        printf("Writer wrote: %d\n", value);

        pthread_cond_signal(&not_empty);

        pthread_mutex_unlock(&mutex);

        usleep(500000);
    }

    return NULL;
}

static void* reader(void* arg) {
    (void)arg;

    while (1) {
        int value;

        pthread_mutex_lock(&mutex);

        while (queue.size == 0)
            pthread_cond_wait(&not_empty, &mutex);

        value = dequeue();

        printf("Reader read: %d\n", value);

        pthread_cond_signal(&not_full);

        pthread_mutex_unlock(&mutex);

        usleep(700000);
    }

    return NULL;
}
