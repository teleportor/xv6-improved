#include "xv6/types.h"
#include "xv6/user.h"

#define NTHREAD 2
#define NBUFFER 3
#define NARRAY  (NBUFFER + 1)

volatile int buffer[NARRAY];
volatile int head = 0, tail = 0;

void print()
{
    printf(1, " Time: %d  Buffer:", uptime());
    for (int i = head; i != tail; i = (i + 1) % NARRAY)
        printf(1, " %d", buffer[i]);
    printf(1, "\n");
}

void inqueue(int x)
{
    buffer[tail] = x;
    tail = (tail + 1) % NARRAY;
    print();
}

int outqueue()
{
    int h = buffer[head];
    head = (head + 1) % NARRAY;
    print();
    return h;
}

int main(int argc, char *argv[])
{
    volatile int pid[NTHREAD + 1];
    volatile int index;

// **************************************************
// This block is used to allocate system resources.
// **************************************************
    usersem buffersem = semaphore_create(NBUFFER);
    usersem productsem = semaphore_create(0);
    usersem mutex = semaphore_create(1);
// **************************************************
// Block end.
// **************************************************

    pid[0] = 1;
    for (int i = 1; i <= NTHREAD; i++) {
        pid[i] = thread_create();
        if (pid[i] == 0) {
            memset(pid, 0, sizeof(pid));
            index = i;
            break;
        }
        else if (pid[i] < 0) {
            printf(1, "thread error\n");
            exit();
        }
    }

    if (pid[0]) {

// **************************************************
// This block is the code of parent thread.
// **************************************************
// **************************************************
// Block end.
// **************************************************

        while (thread_wait() != -1)
            ;

// **************************************************
// This block is used to free system resources.
// **************************************************
        semaphore_free(buffersem);
        semaphore_free(productsem);
        semaphore_free(mutex);
// **************************************************
// Block end.
// **************************************************

        exit();
    } else {

// **************************************************
// This block is the code of chlid threads.
// **************************************************
        int item = 0;
        switch (index) {
        case 1:
            while (1) {
                sleep((item < 5) ? 30 : 10);
                item++;
                semaphore_acquire(buffersem);
                semaphore_acquire(mutex);
                inqueue(item);
                semaphore_release(mutex);
                semaphore_release(productsem);
            }
            break;
        case 2:
            while (1) {
                sleep(20);
                semaphore_acquire(productsem);
                semaphore_acquire(mutex);
                outqueue();
                semaphore_release(mutex);
                semaphore_release(buffersem);
            }
            break;
        default:
            break;
        }
// **************************************************
// Block end.
// **************************************************

        thread_exit();
    }
}
