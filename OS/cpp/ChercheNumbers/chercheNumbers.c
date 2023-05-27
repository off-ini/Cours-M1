#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>

int main() {
    pid_t fils;
    int tubeFP[2];
    int tubePF[2];
    int reponse;

    if (pipe(tubeFP)) {
        perror("Erreur tube FP !\n");
        exit(EXIT_FAILURE);
    }
    if (pipe(tubePF)) {
        perror("Erreur tube PF !\n");
        exit(EXIT_FAILURE);
    }

    fils = fork();
    switch (fils) {
        case -1:
            perror("Erreur fork !\n");
            exit(EXIT_FAILURE);
        case 0:
            //Bouchons
            close(tubeFP[0]);
            close(tubePF[1]);
            int nbreTrouve = 0;
            int nbreSoumis = 0;

            //Lecture de la valeur dans le fils
            int valeur;
            printf("Le fils envoie: ");
            scanf("%d", &valeur);
            while (valeur != EOF) {
                //Ecriture de la valeur reçu au clavier
                write(tubeFP[1], &valeur, sizeof(valeur));
                nbreSoumis++;

                //Lecture de la réponse envoyé par le père
                read(tubePF[0], &reponse, sizeof(reponse));
                if (reponse == 1) {
                    printf("Père répond OK\n\n");
                    nbreTrouve++;
                } else if (reponse == 0) {
                    printf("Père répond NOK\n\n");
                }

                printf("Le fils envoie: ");
                scanf("%d", &valeur);
            }

            write(tubeFP[1], &valeur, sizeof(valeur));//EOF pour que le père quitte sa boucle infini
            sleep(1);
            printf("%d nombres trouvés sur %d soumis\n", nbreTrouve, nbreSoumis);
            exit(EXIT_SUCCESS);
    }

    //Le père
    FILE *fichier;
    int tampon;
    int valeurFichier;
    int trouve;
    int status;

    //Bouchons
    close(tubePF[0]);
    close(tubeFP[1]);

    //Ouverture du fichier
    fichier = fopen("liste.txt", "r");
    if (fichier == NULL) {
        perror("Erreur fopen !\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        read(tubeFP[0], &tampon, sizeof(tampon));
        printf("Le père lit %d\n", tampon);
        valeurFichier = 0;
        trouve = 0;

        if (tampon == EOF) {
            break;
        }

        //Lecture dans le fichier
        while (fscanf(fichier, "%d", &valeurFichier) != EOF) {
            if (valeurFichier == tampon) {
                trouve = 1;
            }
        }
        rewind(fichier);

        //Affichage du résultat
        if (trouve) {
            reponse = 1;
        } else {
            reponse = 0;
        }
        write(tubePF[1], &reponse, sizeof(reponse));
    }

    wait(&status);
    return 0;
}