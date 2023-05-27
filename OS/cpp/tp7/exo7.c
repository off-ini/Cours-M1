//
// Created by infini on 11/05/22.
//
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void sigusr(int sig)
{
    return;
}

int main( int argc, char ** argv) {
    int nombre = 100;
    int fils;

    fils = fork();
    switch (fils) {
        case -1:
            perror("Fork");
            return EXIT_FAILURE;
        case 0:
            if (signal(SIGUSR1, sigusr) == SIG_ERR){
                perror("Assignation SIGUSER1") ;
                kill(getppid(), SIGTERM) ; // alerte le père
                return EXIT_FAILURE ;
            }

            for (int i = 1; i <= nombre; i += 2) {
                printf("Fils %d\n", i);
                kill(getppid(), SIGUSR2);
                pause();
            }
            return EXIT_SUCCESS;
    }

    if (signal(SIGUSR2, sigusr) == SIG_ERR){
        perror("Assignation SIGUSER2") ;
        kill(getppid(), SIGTERM) ; // alerte le père
        return EXIT_FAILURE ;
    }

    for (int i = 2; i <= nombre; i += 2) {
        pause();
        printf("Pere %d\n", i);
        kill(fils, SIGUSR1);
    }

    int status;
    wait(&status);

    return EXIT_SUCCESS;
}
