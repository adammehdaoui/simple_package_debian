#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ftw.h>

#define MAX_SIZE 10

typedef struct file {
    char *name;
    long size;
} File;

File *files[MAX_SIZE];

void alloc_files(){
    int i;

    for(i = 0; i < MAX_SIZE; i++){
        files[i] = malloc(sizeof(File));
        files[i]->size = 0;
        files[i]->name = NULL;
    }
}

void libere_files(){
    for(int i = 0; i < MAX_SIZE; i++){
        free(files[i]->name);
        free(files[i]);
    }
}

void print_files(char *rep){
    int i;

    fprintf(stderr, "TOP 10 des fichiers les plus lourds :\n\n");

    for(i=0;i < MAX_SIZE;i++){
        if (files[i]->size == 4096) {
            strcpy(files[i]->name, rep);
            strcat(files[i]->name, "/.");
        }
    }

    for(i=0;i < MAX_SIZE;i++){
        if (files[i]->size != 0) {
            fprintf(stderr, "%d; File : %s, Taille : %ld\n", i+1, files[i]->name, files[i]->size);
        }
    }
}

int size_files(const char *fpath, const struct stat *sb, int typeflag){
    int i = 0,j;
    //fprintf(stderr, "fpath : %s\n", fpath);

    while (i < MAX_SIZE && files[i]->size > sb->st_size) {
        //fprintf(stderr, "boucle i = %d files[i]->size %ld>? sb->st_size %ld\n",i,files[i]->size,sb->st_size);
        i++;
    }
    //fprintf(stderr, "insertion en %d\n",i);

    if (i < MAX_SIZE) {// ce n'est pas plein
            for (j=MAX_SIZE-1;j>i;j--) {
                //fprintf(stderr,"i = %d et j = %d\n",i,j);
                //on a un nom de fichier en j et j-1 => on switche
                if(files[j - 1]->size != 0){
                    //fprintf(stderr,"décalage du fichier %d = %d\n",j,j-1);
                    files[j]->size = files[j - 1]->size;
                    files[j]->name = (char *) realloc( files[j]->name, sizeof(char) * (strlen(files[j - 1]->name) + 1) );
                    strcpy(files[j]->name, files[j - 1]->name);
            }
        }

        files[i]->size = sb->st_size;
        if (files[i]->name == NULL) {
            files[i]->name = malloc(sizeof(char) * (strlen(fpath + 1)));
        }
        else {
            files[i]->name = (char *) realloc( files[i]->name, sizeof(char) * (strlen(fpath) + 1) );
        }
        
        strcpy(files[i]->name, (char *)fpath);
    }
    //print_files();
    return 0;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Utilisation : %s <répertoire>\n", argv[0]);
        return 1;
    }

    alloc_files();

    if (ftw(argv[1], size_files, MAX_SIZE) == -1) {
        perror("ftw");
        return EXIT_FAILURE;
    }

    print_files(argv[1]);

    libere_files();

    return EXIT_SUCCESS;
}