#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>    // For O_* constants
#include <sys/stat.h> // For mode constants
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    // Create (or open) a named semaphore with an initial value of 1.
    sem_t *sem = sem_open("/mysem", O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {  // Child process
        // Open the semaphore (child can also use the sem returned from fork,
        // but calling sem_open here shows how to obtain it independently)
        sem_t *child_sem = sem_open("/mysem", 0);
        if (child_sem == SEM_FAILED) {
            perror("Child sem_open");
            exit(EXIT_FAILURE);
        }
        
        printf("Child: waiting for semaphore...\n");
        sem_wait(child_sem);
        printf("Child: acquired semaphore, doing work...\n");
        sleep(2); // Simulate some work
        printf("Child: releasing semaphore...\n");
        sem_post(child_sem);
        
        sem_close(child_sem);
        exit(0);
    } else {  // Parent process
        printf("Parent: waiting for semaphore...\n");
        sem_wait(sem);
        printf("Parent: acquired semaphore, doing work...\n");
        sleep(2); // Simulate some work
        printf("Parent: releasing semaphore...\n");
        sem_post(sem);
        
        // Wait for the child to finish
        wait(NULL);
        
        // Clean up the semaphore
        sem_close(sem);
        sem_unlink("/mysem"); // Remove the named semaphore from the system
        
        printf("Parent: finished.\n");
    }
    
    return 0;
}
