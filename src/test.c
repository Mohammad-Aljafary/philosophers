#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()

pthread_mutex_t mutex;

void *routine(void *ptr)
{
    // Try to lock the mutex
    if (pthread_mutex_lock(&mutex) != 0)
    {
        // If locking fails, print a countdown to death
        printf("Mutex lock failed! Countdown to death begins...\n");
        for (int i = 5; i > 0; i--)
        {
            printf("%d...\n", i);
            sleep(1); // Sleep for 1 second
        }
        routine (NULL);
        printf("You died. :(\n");
        return (void *)1; // Return a non-NULL value to indicate failure
    }

    // Critical section
    printf("hahahahahha\n");

    // Unlock the mutex
    pthread_mutex_unlock(&mutex);

    // Return NULL to indicate success
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    void *ret1, *ret2;

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create the first thread (this one will succeed)
    if (pthread_create(&t1, NULL, routine, NULL) != 0)
    {
        printf("Thread 1 creation failed\n");
        return 1;
    }

    // Wait for the first thread to finish
    pthread_join(t1, &ret1);

    // Destroy the mutex before creating the second thread
    pthread_mutex_destroy(&mutex);

    // Create the second thread (this one will fail because the mutex is destroyed)
    if (pthread_create(&t2, NULL, routine, NULL) != 0)
    {
        printf("Thread 2 creation failed\n");
        return 1;
    }

    // Wait for the second thread to finish
    pthread_join(t2, &ret2);

    // Check return values
    if (ret1 == (void *)1)
    {
        printf("Thread 1 failed to lock the mutex\n");
    }
    else
    {
        printf("Thread 1 succeeded\n");
    }

    if (ret2 == (void *)1)
    {
        printf("Thread 2 failed to lock the mutex\n");
    }
    else
    {
        printf("Thread 2 succeeded\n");
    }

    return 0;
}