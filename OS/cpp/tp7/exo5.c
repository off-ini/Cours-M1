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

volatile int n = 5;

void _sigint( int sig ){ // Ctrl C
    fprintf( stderr, "==> La nouvelle valeur de N : %d\n", ++n);
    return ;
}

void _sigstop( int sig ){ // Ctrl Z
    fprintf( stderr, "==> La nouvelle valeur de N : %d\n", --n);
    return ;
}

int main( int argc, char ** argv) {
    int c = 0, z = 0;
    int signum;
    sigset_t mask;
    siginfo_t info;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTSTP);

    // sigprocmask( SIG_BLOCK, &mask, NULL );

    switch (fork()) {
        case -1:
            perror("Fork");
            return EXIT_FAILURE;
        case 0:
            if (signal(SIGINT, _sigint) == SIG_ERR){
                perror("Assignation SIGINT") ;
                kill(getppid(), SIGTERM) ; // alerte le père
                return EXIT_FAILURE ;
            }

            if (signal(SIGTSTP, _sigstop) == SIG_ERR){
                perror("Assignation SIGSOP") ;
                kill(getppid(), SIGTERM) ; // alerte le père
                return EXIT_FAILURE ;
            }

            while (n > 0 && n < 10)
            {
                signum = sigwaitinfo(&mask, &info);
                if(signum == SIGINT) c++;
                else if(signum == SIGTSTP) z++;
            }

            fprintf(stderr, "\nCTRL C : %d\tCTRL Z : %d\n", c, z);
            return EXIT_SUCCESS;
    }


    if (signal(SIGINT, SIG_IGN) == SIG_ERR){
        perror("Sigignore") ;
        kill(getppid(), SIGTERM) ;
        return EXIT_FAILURE ;
    }

    if (signal(SIGTSTP, SIG_IGN) == SIG_ERR){
        perror("Sigignore") ;
        kill(getppid(), SIGTERM) ;
        return EXIT_FAILURE ;
    }

    int status;
    wait(&status);
    return  EXIT_SUCCESS;
}
