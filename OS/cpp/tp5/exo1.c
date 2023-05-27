//
// Created by infini on 05/04/2022.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int narg, char *argv[], char *env[] ) {
    char * argv_exec[5];
    argv_exec[0]="/usr/bin/xterm";
    argv_exec[1]="-e";
    argv_exec[2]="/bin/sh";
    argv_exec[3]=NULL;

    //setreuid(1001,1000);

    printf("réel %d effectif %d \n", getuid(), geteuid());
    execve(argv_exec[0], argv_exec, env ) ;

    return(EXIT_FAILURE);
}

