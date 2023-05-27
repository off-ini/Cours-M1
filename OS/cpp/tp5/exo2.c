//
// Created by infini on 05/04/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int narg, char *argv[], char *env[] ) {
    int pid;
    int nb;
    char * argv_exec[3];
    argv_exec[0]="/bin/ls";
    argv_exec[1]=NULL;

    printf("== Nombre de processus ==\n >>> ");
    scanf("%d", &nb);

    printf (" print 1 - Je suis le processus pere num=%d \n\t\t|\n",(int)getpid() );

    for(int i = 1; i <= nb; i++)
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
                printf("\t\t|\n");
                if(i == 3) {
                    int a = 0;
                    int b = 5;
                    b = b/a;
                }
                execve(argv_exec[0], argv_exec, NULL) ;
                exit(i);
        }
        pid_child = wait(&status);
        if(WIFEXITED(status))
            printf("Terminaison normale");
        else{
            printf("Terminaison anormale\n");
            exit(0);
        }
        printf(" du processus %d\n", pid_child);
    }

    exit(0);
}


