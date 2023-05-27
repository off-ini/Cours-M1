//
// Created by infini on 14/05/22.
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

#define FILE_LISTE "liste.txt"

int findNumber(FILE * file, int number) // La fonction de recherche des nombres : return 1 Si trouvé 0 Sinon
{
    int value;

    fseek(file, 0, SEEK_SET);
    while (fscanf(file, "%d", &value) != EOF){
        if(value == number) return 1;
    }

    return 0;
}

int main(int argc, char **argv){
    pid_t fils;
    int tubeFP[2];
    int tubePF[2];
    int saisie;
    int resultat;

    FILE * fileliste = NULL;

    if(pipe(tubeFP) < 0){
        perror("Tube Fils - Pere");
        return EXIT_FAILURE;
    }

    if(pipe(tubePF) < 0){
        perror("Tube Pere - Fils");
        return EXIT_FAILURE;
    }

    fils = fork();
    switch (fils) {
        case -1:
            perror("Fork error");
            return EXIT_FAILURE;
        case 0:
            close(tubeFP[0]);
            close(tubePF[1]);

            int nbT = 0;
            int nbS = 0;

            fprintf(stderr," === Entrer un Nombre et faite [ENTRER]. (-1 pour arreter)  === \n");

            fprintf(stderr, "Fils envoie : ");
            fscanf(stdin,"%d", &saisie);
            while (saisie != -1){
                write(tubeFP[1], &saisie, sizeof(saisie));
                nbS++;
                read(tubePF[0], &resultat, sizeof(resultat));
                if(resultat == 1){
                    printf("Père répond : OK\n\n");
                    nbT++;
                }else{
                    printf("Père répond : NOK\n\n");
                }
                fprintf(stderr, "Fils envoie : ");
                fscanf(stdin,"%d", &saisie);
            }
            write(tubeFP[1], &saisie, sizeof(saisie));

           fprintf(stderr, "%d nombres trouvés sur %d soumis\n", nbT, nbS);
            return EXIT_SUCCESS;
    }

    close(tubeFP[1]);
    close(tubePF[0]);

    fileliste = fopen("liste.txt", "r+");

    if(fileliste == NULL){
        perror("Ouverture du fichier");
        return EXIT_FAILURE;
    }

    int value;

    read(tubeFP[0], &value, sizeof(value));
    while (value != -1){
        fprintf(stdout, "Père lit : %d\n", value);
        fflush(stdout);

        resultat = findNumber(fileliste, value);
        write(tubePF[1], &resultat, sizeof(resultat));

        read(tubeFP[0], &value, sizeof(value));
    }

    int status;
    wait(&status);

    return EXIT_SUCCESS;
}