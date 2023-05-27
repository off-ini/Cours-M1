#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int fich = open( "fichier.txt", O_CREAT, S_IRUSR | S_IWGRP | S_IRWXO ) ;
  if (fich == -1 ) {
    fprintf( stderr, "Erreur lors de la creation'\n" );
    return -1 ;
  }
  close(fich);
    return 0;
}