//
// Created by infini on 15/03/2022.
//
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char * argv[]){
    FILE * fichier = NULL;
    int L = 256;
    int H = 256;
    int D = 256;

    fichier = fopen("image.pgm", "w+");

    if(fichier == NULL) {
        perror("FILE ERROR");
        return -1;
    }

    fprintf(fichier, "P2\n#Ma nouvelle image\n%d %d\n%d\n", L, H, D);

    for(int j = 0; j < H; j++)
    {
        for(int i = 0; i < L; i++)
        {
            if(i == L-1)
            {
                fprintf(fichier, "%d", rand() % D);
            } else{
                fprintf(fichier, "%d ", rand() % D);
            }
        }
        fputs("\n", fichier);
    }

    fclose(fichier);

    return 0;
}

