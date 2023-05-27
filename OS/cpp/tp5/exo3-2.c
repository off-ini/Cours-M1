//
// Created by infini on 12/04/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int narg, char *argv[], char *env[] ) {
    int pid;
    int nb = 4;
    char * argv_exec[nb][3];
    argv_exec[0][0]="/bin/who";
    argv_exec[0][1]=NULL;

    argv_exec[1][0]="/bin/ps";
    argv_exec[0][1]=NULL;

    argv_exec[2][0]="/bin/ls";
    argv_exec[2][1]="-l";
    argv_exec[0][2]=NULL;


    for(int i = 0; i < nb-1; i++)
    {
        pid = fork();
        int pid_child;
        int status;
        switch (pid)
        {
            case -1:
                perror("fork failed");
                return 1;
            case 0:
                execve(argv_exec[i][0], argv_exec[i], NULL) ;
                exit(i);
        }
        pid_child = wait(&status);
    }

    exit(0);
}


