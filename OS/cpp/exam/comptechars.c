//
// Created by infini on 13/05/22.
//
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#define TAB_MAX 150

int main(int argc, char **argv){
    char buffer = EOF;
    char chaine[TAB_MAX];

    int nbChar = 0;
    int nbMchar = 0;
    int sum = 0;

    int tube[2];
    pid_t fils;

    if(pipe(tube)){
        perror("Creation Tube");
        return EXIT_FAILURE;
    }

    fils = fork();
    switch (fils) {
        case -1:
            perror("Fork erreur");
            return EXIT_FAILURE;
        case 0:
            close(tube[1]);
            printf("Fils PID : %d\n", getpid());
            read(tube[0], &buffer, sizeof(char));

            while (buffer != EOF){
                if(buffer >= '0' && buffer <= '9'){
                    sum += atoi(&buffer);
                }
                else if(buffer >= 'a' && buffer <= 'z')
                    nbChar++;

                read(tube[0], &buffer, sizeof(char));
            }
            printf("Somme chiffre : %d\nNombre caractère minuscule : %d\n", sum, nbChar);
            return EXIT_SUCCESS;
    }
    close(tube[0]);

    fscanf(stdin, "%s", chaine);

    for (int i = 0; i < strlen(chaine); i++) {
        if((chaine[i] >= '0' && chaine[i] <= '9') || (chaine[i] >= 'a' && chaine[i] <= 'z'))
        {
            write(tube[1], &chaine[i], sizeof(char));
        } else if(chaine[i] >= 'A' && chaine[i] <= 'Z')
            nbMchar++;
    }

    write(tube[1], &buffer, sizeof(char));

    int status;
    wait(&status);

    printf("Nombre caractère majuscule : %d\n", nbMchar);

    return EXIT_SUCCESS;
}