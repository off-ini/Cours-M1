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

int f(int x)
{
    /*if(x != 0 && x % 2 == 0)
        return x / 2;*/
    return x;
}

int main( int argc, char ** argv) {
    pid_t fils;
    int tube[2];

    if (argc<2){
        fprintf(stderr,"Manque argument\n");
        return EXIT_FAILURE;
    }
    if (pipe(tube) != 0){
        perror("Création tube");
        return EXIT_FAILURE;
    }

    switch (fils = fork()) {
        case -1:
            perror("Fork erreur");
            return EXIT_FAILURE;
        case 0:
            (void) close( tube[0] );

            int y;
            for (int i = 1; i < argc; ++i) {
                y = f(atoi(argv[i]));
                write(tube[1], &y, sizeof(y));
                printf("+ Ecriture %d\n", y);
            }
            exit(0);
    }

    int tmp;
    int sum = 0;
    float moyenne;

    (void) close( tube[1] );

    for (int i = 1; i < argc; ++i) {
        read(tube[0], &tmp, sizeof(tmp));
        sum += tmp;
        printf("- Lecture %d\n", tmp);
    }

    moyenne = (float) sum / (argc - 1);
    fprintf(stderr, "\nLa moyenne est : %.2f\n", moyenne);

    return EXIT_SUCCESS;
}
