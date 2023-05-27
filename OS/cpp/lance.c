//
// Created by sharon on 12/05/22.
//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {

    if(argc<3){
        printf("Nombre d'argument insuffisant\n");
        return EXIT_FAILURE;
    }

    // Template redirection
    int fstdout;
    fstdout= open(argv[2], O_WRONLY | O_CREAT, S_IRWXU);

    if(fstdout<0){
        perror("Ouverture fichier redirection");
        return EXIT_FAILURE;
    }

    close(STDOUT_FILENO); // fermututre dflux de sortie standard (flux vers lequel la redirection sera faite)

    if(dup(fstdout)<0){ // dup permet de faire la redirection effectivedes flux
        perror("Redirection erronée");
        return EXIT_FAILURE;
    }

    // Fin Template redirection

    if(argc==4){
        if(strcmp(argv[3], "-2") == 0){
            if(dup2(fstdout, STDERR_FILENO) < 0){
                perror("Redirection erronée");
                return EXIT_FAILURE;
            }
        }else{
            int fstderr;
            fstderr= open(argv[3], O_WRONLY | O_CREAT, S_IRWXU);

            if(fstderr<0){
                perror("Ouverture fichier redirection d'erreur");
                return EXIT_FAILURE;
            }

            close(STDERR_FILENO);

            if(dup(fstderr)<0){
                perror("Redirection erronée");
                return EXIT_FAILURE;
            }

            close(fstderr);
        }
    }

    close(fstdout);

    // Construction des arguments qui sont passés en paramètre au programme
    char * args[5];
    args[0]= argv[1];
    args[1]= NULL;

    int fpid;
    fpid=fork();
    switch(fpid){

        case -1:
            perror("Erreur création fils");
            return EXIT_FAILURE;

        case 0:
            fprintf(stderr, "\t\t [ERREUR]\n ------------ Notre test d'erreur ------------\n\t\t [ERREUR]\n\n");
            execvp(args[0],args); // Recouvrement: il change le code du fils qui se retrouve à exécuter la commande qui lui est passée et ne revient plus exécuter la même chose que le père
            return EXIT_SUCCESS;
    }

}
