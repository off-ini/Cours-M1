//
// Created by infini on 26/04/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int narg, char *argv[], char *env[]) {
    FILE * my_stdout;
    FILE * my_stderr;

    /*if(narg > 2){
        my_stderr = freopen(argv[3], "w+", stderr);
        if ( my_stderr == (FILE *)NULL) {
            perror("Echec de l'ouverture STDERR");
            return EXIT_FAILURE ;
        }
    }*/

    /*my_stdout = freopen( argv[2], "w+", stdout);
    if ( my_stdout == (FILE *)NULL) {
        perror("Echec de l'ouverture STDOUT");
        return EXIT_FAILURE ;
    }*/

    char *argv_exec[] = {argv[0], NULL};

    execvp(argv_exec[0], argv_exec) ;

    return EXIT_FAILURE ;
}