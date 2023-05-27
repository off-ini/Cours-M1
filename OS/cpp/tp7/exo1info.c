//
// Created by infini on 10/05/22.
//

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void sigusr1( int sig ){ // pour signal 10 du pere --> fils au cadet
    fprintf( stderr, "==> Cadet reçoit signal  %d\n", sig );
    return ;
}

void sigusr2( int sig ){// pour signal 12 du fils cadet --> fils ainé
    fprintf( stderr, "==> Ainé reçoit signal  %d\n", sig );
    return ;
}

int main( int argc, char ** argv) {
    int aine, cadet;
    int signum;
    sigset_t mask;
    siginfo_t info;

    aine = fork();
    switch (aine) {
        case -1:
            perror("Fork ainé");
            return EXIT_FAILURE;
        case 0:
            if (signal(SIGUSR2, sigusr2) == SIG_ERR){
                perror("Assignation SIGUSR2") ;
                kill(getppid(), SIGTERM) ; // alerte le père
                return EXIT_FAILURE ;
            }

            pause();
            kill(getpid(), SIGTERM) ;
    }


    cadet = fork();
    switch (cadet) {
        case -1:
            perror("Fork cadet");
            return EXIT_FAILURE;
        case 0:
            if (signal(SIGUSR1, sigusr1) == SIG_ERR){
                perror("Assignation SIGUSR1") ;
                kill(getppid(), SIGTERM) ; // alerte le père
                return EXIT_FAILURE ;
            }

            while (1)
            {
                pause();
                signum = sigwaitinfo(&mask, &info);

                if(signum == SIGUSR1 && info.si_code == getppid()){
                    fprintf( stderr, "CADET ==> AINE\n");
                    kill(aine, SIGUSR2);
                    kill(getpid(), SIGTERM) ;
                }
            }

    }

    sleep(1);
    fprintf( stderr, "PERE ==> CADET\n");
    kill(cadet, SIGUSR1);

    return EXIT_SUCCESS;
}