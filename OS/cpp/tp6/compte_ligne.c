#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>

void fils(char * fich, char * fichTemp){
    int fdin;
    int fdout;

    char * args[] = {"wc", "-l", (char*) NULL};

    // Redirection de la entree
    if((fdin = open(fich, O_RDONLY)) == -1){
        perror("Erreur ouverture");
        exit(-1);
    }

    close(STDIN_FILENO);

    if(dup(fdin) < 0 ){
        perror("Erreur dup fdin");
        exit(-1);
    }

    close(fdin);

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

void pere(char * fich, char * fichTemp){
    int status;
    FILE * fd1;

    // le pere attend la fin d'un fils
    pid = wait(&status);

    fd1 = fopen(fichTemp, "r");
    char  buffer[250] ;
    if(fd1 != NULL) {
        fgets(buffer, 250, fd1);
    }
    fprintf(stdout, "Le Fichier %s contient %s lignes \n", fich, buffer);  

}

int main(int narg, char *argv[]) {

    if(narg < 2) {
       printf("Vous devez avoir au moins un paramètre");
       return -1;
    }

    char *tmpFile = "/tmp/stdout.tmp";
    int nbFiles = narg - 1;

    for(int i = 0; i < nbFiles; i++){
        int pid = fork();

        switch (pid) {
            case -1 :
                perror("fork");
                exit(1);
            
            case 0 :
                fils(argv[i+1], tmpFile);
        }
        pere(argv[i+1], tmpFile);
    }

}