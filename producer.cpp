#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstring>

using namespace std;

struct Table {
    int buffer[2];
    int count;
};

int main() {
    // Create shared memory
    int shm_fd = shm_open("/mytable", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    ftruncate(shm_fd, sizeof(Table));
    Table* table = static_cast<Table*>(
        mmap(0, sizeof(Table), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
    );

    if (table == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Initialize table only once
    table->count = 0;

    // Create/Open semaphores
    sem_t* mutex = sem_open("/mutex", O_CREAT, 0666, 1);
    sem_t* empty = sem_open("/empty", O_CREAT, 0666, 2);
    sem_t* full  = sem_open("/full",  O_CREAT, 0666, 0);

    if (mutex == SEM_FAILED || empty == SEM_FAILED || full == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }

    int item = 0;
    while (true) {
        item++;

        sem_wait(empty);
        sem_wait(mutex);

        // Critical section
        table->buffer[table->count] = item;
        table->count++;
        cout << "Produced: " << item << " | Count: " << table->count << endl;

        sem_post(mutex);
        sem_post(full);

        sleep(1);
    }

    return 0;
}
