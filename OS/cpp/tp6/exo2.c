//
// Created by infini on 09/05/22.
//
#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int narg, char *argv[], char *env[]) {
    int file_red;
    FILE *file;
    pid_t pid;

    char *argv_exec[5];
    argv_exec[0] = "/bin/wc";
    argv_exec[1] = "-l";
    argv_exec[2] = NULL;

    if (narg < 2) {
        printf("Aucun fichier\n");
        return EXIT_FAILURE;
    }

    file_red = open("stdout.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);

    if (file_red < 0) {
        perror("File ouverture\n");
        return EXIT_FAILURE;
    }

    if (dup2(file_red, STDOUT_FILENO) < 0) {
        perror("Rediection dup\n");
        return EXIT_FAILURE;
    }
    close(file_red);

    for (int i = 1; i < narg; i++) {
        printf("%s", argv[i]);
        pid = fork();
        switch (pid) {
            case -1:
                perror("fork failed");
                return 1;
            case 0:
                argv_exec[2] = argv[i];

                execve(argv_exec[0], argv_exec, NULL);
                perror("Erreur exec");
                return EXIT_FAILURE;
        }

        int status;

        if (wait(&status) != -1) {
            if (!WIFEXITED(status)) {
                perror("Terminaison de processus");
            }
        }
    }

    fflush(stdout);

    int line;
    char filename[50];

    fseek(stdout, SEEK_SET, 0);
    for (int i = 1; i < narg; i++) {
        fscanf(stdout, "%d %s", &line, filename);
        fprintf(stderr, "%s %d\n", filename, line);
    }

    return EXIT_SUCCESS;
}
