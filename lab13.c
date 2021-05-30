#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/mman.h>

int createFile(char* name){
    FILE* file = fopen(name, "w");
    if(file == NULL){
        printf("Unable to open file!\n");
        return 1;
    }
    fclose(file);
    return 0;
}

char* getFileName(int i, int temp){
    char* filename = malloc(sizeof("100"));
    if(temp == 0)
        sprintf(filename, "files/%03d", i);
    else
        sprintf(filename, "%03d", i);
    return filename;
}

int main(int argc, char* argv[]){
    DIR *dir = opendir("files");

    if(dir == NULL) {
       printf("Create directory with name \"files\"\n");
       system("mkdir files");
    } else {
       printf("Directory \"files\" was deleted and created again\n");
       system("rm -r files");
       system("mkdir files");
    }

    char* firstName = getFileName(0, 0);
    if(createFile(firstName)){
        free(firstName);
        printf("Unable to open file!\n");
        exit(1);
    }
    free(firstName);
    int counter = 1;

    while(1){
        char* prevFile = getFileName(counter - 1, 1);
        char* nextFile = getFileName(counter, 0);
        if(symlink(prevFile, nextFile)) {
            free(prevFile);
            free(nextFile);
            printf("Symlink error\n");
            exit(-1);
        }
        FILE* newFile = fopen(nextFile, "r");
        if(newFile == NULL){
            free(prevFile);
            free(nextFile);
            break;
         }

        fclose(newFile);
        free(prevFile);
        free(nextFile);
        counter++;
    }
    printf("result: %d\n", --counter);
    closedir(dir);

    return 0;
}