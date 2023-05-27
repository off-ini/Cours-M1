//
// Created by infini on 29/03/2022.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (){
    pid_t valeur;
    printf("printf-0 Avant fork : ici processus numero %d\n", (int)getpid());
    valeur = fork();
    if (valeur == 0) sleep(4);
    printf("printf-1 Valeur retournee par la fonction fork: %d\n", (int)valeur);
    printf("printf-2 Je suis le processus numero %d\n", (int)getpid());
    return 0;
}

/**
 * 1- ) 5 lignes de printf() car après le fork() nous aurons deux processus (père et fils) qui vont exécuté
 *      le reste des instruction chacun de leur côté.
 *
 * 2- ) Le processus fils et obligé d'attendre 4 secondes ce qui laisse le temps au père de ce terminer avant
 *      le fils.
 *      conclusion: le processus fils sera un processus orphelin (zombie).
 * **/
