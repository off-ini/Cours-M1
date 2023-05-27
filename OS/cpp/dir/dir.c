//
// Created by infini on 28/03/2022.
//
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void exit_on_error(char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}

void  folders(const char * name)
{
    short folder = 0;
    DIR *dirp;
    struct dirent *dp;
    dirp = opendir(name);
    if(dirp==NULL) {
        //exit_on_error("opendir");
        folder = 1;
    }
    if(folder == 0)
    {
        while ((dp = readdir(dirp)) != NULL) {
            printf("%s\n",dp->d_name);
            if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
                printf("\t");
                folders(dp->d_name);
            }
        }
        int err = closedir(dirp);
        if(err<0) {
            exit_on_error("closedir");
        }
    }

}

int main (int argc, char *argv[]) {
    char name[]=".";
    folders(name);
}
