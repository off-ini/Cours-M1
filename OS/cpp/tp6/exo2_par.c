//
// Created by infini on 09/05/22.
//

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>

#define TMAX 100
#define BASE_NAME "/tmp/stdout"

void fils(char * fich){
    int fdout;

    char * args[] = {"wc", "-l", fich, (char*) NULL};

    char fichTemp[TMAX];
    sprintf(fichTemp, "%s%d.r", BASE_NAME, getpid());

    // Redirection de la sortie fdout
    if((fdout = open(fichTemp, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1){
        perror("Erreur ouverture fichier Temp");
        exit(-1);
    }

    close(STDOUT_FILENO);

    if(dup(fdout) < 0 ){
        perror("Erreur dup fdout");
        exit(-1);
    }

    close(fdout);

    //on lance wc
    execvp(args[0], args);
    perror("Erreur exec");

}

void pere(){
    int status;
    int pid;
    FILE * fd1;

    // le pere attend la fin d'un fils
    while ((pid = wait(&status)) != -1){
        char fichTemp[TMAX];
        sprintf(fichTemp, "%s%d.r", BASE_NAME, pid);
        fd1 = fopen(fichTemp, "r");
        char filename[250] ;
        int nbLigne;

        fscanf(fd1, "%d %s", &nbLigne, filename);
        fprintf(stdout, "Le Fichier %s contient %d lignes \n", filename, nbLigne);
    }

}

int main(int narg, char *argv[]) {

    if(narg < 2) {
        printf("Vous devez avoir au moins un paramètre");
        return -1;
    }

    for(int i = 1; i < narg; i++){
        int pid = fork();

        switch (pid) {
            case -1 :
                perror("fork");
                exit(1);

            case 0 :
                fils(argv[i]);
        }
    }
    pere();
}