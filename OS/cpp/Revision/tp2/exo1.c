//
// Created by infini on 06/05/22.
//
#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NB 124

int main(int narg, char *argv[], char *env[]){
    char buffer[NB];
    int file;
    int file_read;
    int nombre;

    // Creation et ouverture du fichier en mode lecture/ecriture
    file = open("chats.txt", O_CREAT | O_RDWR, S_IRWXU | S_IRGRP | S_IXGRP);
    if(file == -1)
    {
        perror("Overture du fichier");
        return EXIT_FAILURE;
    }

    // Eriture des paramètre passé au programme via argv (narg : le nombre d'arguments passé au programme)
    for(int i = 1; i < narg; i++)
    {
        // Ajouter un espace devant chaque entrer (ps : C'est affreux de le faire en C)
        char chaine[15];
        strcpy(chaine, argv[i]);
        strcat(chaine, " ");

        nombre = write(file, chaine, strlen(chaine));
        if(nombre == -1)
        {
            perror("Ecriture echoué");
            return EXIT_FAILURE;
        }
    }
    // Ecriture d'un retour a la ligne
    write(file, "\n", 1);

    // Ouverture du second fichier en mode lecture
    file_read = open("vision.txt", O_RDONLY);
    if(file_read == -1)
    {
        perror("Overture du fichier");
        return EXIT_FAILURE;
    }

    // Lecture du second fichier
    nombre = read(file_read, buffer, NB);
    int nb_ecrit;
    while (nombre > 0){
        // Ecriture des données du second fichier dans le premier
        nb_ecrit = write(file, buffer, nombre);
        if(nb_ecrit == -1)
        {
            perror("Ecriture echoué");
            return EXIT_FAILURE;
        }
        nombre = read(file_read, buffer, NB);
    }

    // Fermeture des fichiers
    close(file);
    close(file_read);

    return EXIT_SUCCESS;
}