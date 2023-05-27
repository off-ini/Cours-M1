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

int main( int argc, char ** argv) {
    int pid_fils;
    int tubPF[2];
    int tubeFP[2];

    if (pipe(tubPF) != 0){
        perror("Tube PF");
        return EXIT_FAILURE;
    }

    if (pipe(tubeFP) != 0){
        perror("Tube FP");
        return EXIT_FAILURE;
    }

    pid_fils = fork();

    switch (pid_fils) {
        case -1:
            perror("Fork");
            return EXIT_FAILURE;
        case 0:
            close(tubPF[1]);
            close(tubeFP[0]);

            int fl = 0;
            while (1){
                read(tubPF[0], &fl, sizeof (fl));
                printf("- Fils %d\n", ++fl);
                write(tubeFP[1], &fl, sizeof (fl));
            }
            return EXIT_SUCCESS;
    }

    close(tubPF[0]);
    close(tubeFP[1]);

    int pe = 0;
    while (pe < 10){
        write(tubPF[1], &pe, sizeof(pe));
        read(tubeFP[0], &pe, sizeof(pe));
        printf("- Pere %d\n", ++pe);
    }

    kill(pid_fils, SIGTERM);

    wait((int *)NULL);
    return EXIT_SUCCESS;
}
