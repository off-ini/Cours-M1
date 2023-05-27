//
// Created by infini on 07/05/22.
//
#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int narg, char *argv[], char *env[]){
    FILE * file = NULL;
    FILE * file_read = NULL;
    int nombre_ecrit;
    int nombre_lue;

    // Overture du fichier chats
    file = fopen("chats.txt", "w+");
    if(file == NULL)
    {
        perror("Chat open");
        return EXIT_FAILURE;
    }

    // Ecriture des arguments dans le fichier chats
    for(int i = 1; i < narg; i++){
        nombre_ecrit = fputs(argv[i], file);
        if(nombre_ecrit == -1){
            perror("Ecriture chat");
            return EXIT_FAILURE;
        }
        fputc('\n', file);
    }

    fflush(file); // Vidé les caches pour l'écriture du fichier chats
    // Overture du fichier Vision
    file_read = fopen("vision.txt", "r");
    if(file_read == NULL){
        perror("Vision open");
        return EXIT_FAILURE;
    }

    // Lecture caractère par caractètre du fichier vision
    nombre_lue = fgetc(file_read);  // première lecture
    while (nombre_lue != EOF){ // Lire quand qu'on n'est pas à la fin du fichier
        nombre_ecrit = fputc(nombre_lue, file); // Ecrire le caractère lu dans le fichier Chats
        if(nombre_ecrit == -1){
            perror("Ecriture chat 2");
        }
        nombre_lue = fgetc( file_read); // Lecture iterative des caractères
    }

    fflush(file); // Vidé les caches pour l'écriture du fichier chats
    // Fermeture des fichiers
    fclose(file);
    fclose(file_read);

    return EXIT_SUCCESS;
}