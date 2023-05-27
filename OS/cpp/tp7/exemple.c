//
// Created by infini on 09/05/22.
//

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/file.h>

int main( int argc, char * argv[] ) {
    int tampon, var;
    pid_t fils;
    tampon = open("/tmp/tampon", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (tampon < 0) {
        perror("Ouverture /tmp/tampon");
        return EXIT_FAILURE;
    }
    var = 1;
    lseek(tampon, 0, SEEK_SET);
    if (write(tampon, (void *) &var, 4) != 4) {
        perror("Écriture tampon père");
        return EXIT_FAILURE;
    }
    fprintf(stderr, "Père écrit VAR=%d\n", var);
    fils = fork();
    if (fils == -1) {
        perror("Fork");
        unlink("/tmp/tampon");
        return EXIT_FAILURE;
    }

    if (fils == 0) {
        (void) close(tampon);
        tampon = open("/tmp/tampon", O_RDWR);
        if (tampon < 0) {
            perror("Ouverture /tmp/tampon");
            return EXIT_FAILURE;
        }

        while (1) {
            if (flock(tampon, LOCK_EX) < 0) {
                perror("Pose verrou");
                return EXIT_FAILURE;
            }
            lseek(tampon, 0, SEEK_SET);
            var = 0;
            if (read(tampon, (void *) &var, 4) != 4) {
                perror("Lecture /tmp/tampon fils");
                return EXIT_FAILURE;
            }
            fprintf(stderr, "Fils lit VAR=%d, FILS écrit VAR=%d\n", var++, var);
            fflush(stderr);
            lseek(tampon, 0, SEEK_SET);
            if (write(tampon, (void *) &var, 4) != 4) {
                perror("Écriture tampon fils");
                return EXIT_FAILURE;
            }
            if (flock(tampon, LOCK_UN) < 0) {
                perror("Levée verrou");
                return EXIT_FAILURE;
            }
            if (var % 3 == 0) sleep(1);
        }
        return EXIT_SUCCESS;
    }

    var = 1;
    while (var < 20) {
        if (flock(tampon, LOCK_EX) < 0) {
            perror("Pose verrou père");
            return EXIT_FAILURE;
        }
        var = 0;
        lseek(tampon, 0, SEEK_SET);
        if (read(tampon, (void *) &var, 4) != 4) {
            perror("Lecture /tmp/tampon père");
            return EXIT_FAILURE;
        }
        fprintf(stderr, "PÈRE lit VAR=%d, PÈRE écrit VAR=%d\n", var++, var);
        fflush(stderr);
        lseek(tampon, 0, SEEK_SET);
        if (write(tampon, (void *) &var, 4) != 4) {
            perror("Écriture tampon PÈRE");
            return EXIT_FAILURE;
        }
        if (flock(tampon, LOCK_UN) < 0) {
            perror("Levée verrou");
            return EXIT_FAILURE;
        }
        if (var % 2 == 0) sleep(1);
    }
    kill(fils, SIGTERM);
    (void) wait((int *) NULL);
    return EXIT_SUCCESS;
}
