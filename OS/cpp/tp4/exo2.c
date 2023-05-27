//
// Created by infini on 29/03/2022.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
    pid_t valeur, valeur1;
    printf (" print 1 - Je suis le processus pere num=%d \n",(int)getpid() );
    valeur = fork();
    printf (" print 2 - retour fork: %d - processus num= %d -num pere=%d \n",(int)valeur, (int)getpid(), (int)getppid() );
    valeur1 = fork();
    printf (" print 3 - retour fork: %d - processus num= %d -num pere=%d \n",(int)valeur1, (int)getpid(), (int)getppid() );
    return 0;
}

/**
 * 1-) Compiler puis exécuter
 *
 * print 1 - Je suis le processus pere num=273749
 * print 2 - retour fork: 273750 - processus num= 273749 -num pere=150302
 * print 2 - retour fork: 0 - processus num= 273750 -num pere=273749
 * print 3 - retour fork: 273751 - processus num= 273749 -num pere=150302
 * print 3 - retour fork: 273752 - processus num= 273750 -num pere=273749
 * print 3 - retour fork: 0 - processus num= 273751 -num pere=2162
 * print 3 - retour fork: 0 - processus num= 273752 -num pere=2162
 *
 * 2- ) Schéma de l’arborescence (hiérarchie) des processus
 *
 *                     (273749) père
 *                              /\
 *                             /  \
 *                 (273750) fils1  \
 *                           /      \
 *                          /        \
 *       (273752) petit fils 1        fils2 (273751)
 * **/