#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    char tampon[NB];
    int fich, nlus, necrits;

    fich = open("/tmp/fichier.txt", O_RDONLY);
    if (fich == -1) {
        write(2, (void *) ERROR_OPEN, strlen(ERROR_OPEN));
        return -1;
    }

}