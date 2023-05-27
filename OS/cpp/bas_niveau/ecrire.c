#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]) {

  int fich = open("fichier.txt", O_RDWR ) ;
  if (fich == -1 ) {
    fprintf( stderr, "Erreur lors de l'ouverture\n" );
    return -1 ;
  }

  for(int i = 1; i < argc; i++)
  {
      write(fich, argv[i], strlen(argv[i]) + 1);
      
      if(strlen(argv[i]) != i - 1)
      {
        write(fich, " ", 1);
      }
  }

    close(fich);
    return 0;
}