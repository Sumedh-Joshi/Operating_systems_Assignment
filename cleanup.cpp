#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

int main() {
    shm_unlink("/mytable");
    sem_unlink("/mutex");
    sem_unlink("/empty");
    sem_unlink("/full");

    cout << "Cleaned up shared memory and semaphores.\n";
    return 0;
}
