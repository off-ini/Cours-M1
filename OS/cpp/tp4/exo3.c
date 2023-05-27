//
// Created by infini on 29/03/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {
    int pid, nb;
    printf("== Nombre de processus ==\n >>> ");
    scanf("%d", &nb);

    printf (" print 1 - Je suis le processus pere num=%d \n\t\t|\n",(int)getpid() );

    for(int i = 1; i <= nb; i++)
    {
        pid = fork();
        switch (pid)
        {
            case -1:
                perror("fork failed");
                return 1;
            case 0:
                sleep(2 * i);
                if(i == 2){
                    int a = 0;
                    int b = 5;
                    b = i/a;
                }
                printf (" Retour fork: %d - processus num= %d -num pere=%d \n",(int)pid, (int)getpid(), (int)getppid() );
                exit(i);
        }
    }

    int pid_child;
    int status;

    pid_child = wait(&status);
    while (pid_child != -1)
    {
        if(WIFEXITED(status))
            printf("Terminaison normale");
        else
            printf("Terminaison anormale");
        printf(" du processus %d\n", pid_child);
        pid_child = wait(&status);
        // printf ("\t Retour wait: %d \n",(int)status );
    }

    exit(0);
}

