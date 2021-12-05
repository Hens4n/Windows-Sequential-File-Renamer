#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <io.h>
#include <errno.h>
#define CLS "cls"

void getType(char *file, char *type);
int checkFile(char *seqName, char *fileToCheck);
void banner();

int main() {
    struct _finddata_t data;
    intptr_t fileP, flag;
    char folder[MAX_PATH], fileName[MAX_PATH], type[10];
    char fileName1[MAX_PATH], fileName2[MAX_PATH], c;
    int i = 0;

    system(CLS);
    banner();
    printf("\nEnter the path to the files here: ");
    while((c = getchar()) != '\n') {
        if(c == '\\') folder[i++] = c;
        folder[i++] = c; 
    }
    folder[i] = '\0';
    
    if(_chdir(folder) == 0) system(CLS);                           // Checks if it was possible to change the path
    else {                                                         // If it was, then chages the path
        if(errno == ENOENT) printf("Path not found.\n");
        else printf("Unknown error.\n");
        getchar(); exit(1);
    }

    banner();
    printf("\nEnter sequential file names here\n");
    printf("Ex: Test-#-Test (# is where the numeration occurs)\n");
    for(i = 1; i <= 3; i++) printf("Test-%d-Test\n", i);            // Example iteration
    printf("...\n");
    i = 0;
    while((c = getchar()) != '#') {
        fileName1[i++] = c;
    }
    fileName1[i] = '\0';
    i = 0;
    while((c = getchar()) != '\n') {                    // It only matters when the user wants something after numbering
        fileName2[i++] = c;
    }
    fileName2[i] = '\0'; system(CLS); banner();

    fileP = _findfirst("*.*", &data);
    flag = fileP;

    i = 1;
    while(flag != -1) {
        if(data.attrib & _A_ARCH) {
            if(checkFile(fileName1, data.name)) {
                getType(data.name, type);
                sprintf(fileName, "%s%d%s%s", fileName1, i++, fileName2, type); // Formats the new file name
                printf("%s\n", fileName);
                rename(data.name, fileName);                                    // Renames the file
            }
        }

        flag = _findnext(fileP, &data);
    }
    
    _findclose(fileP);
    return 0;
}

void getType(char *file, char *type) {                  // Function to get the file type
    int i = 0;

    for(file; *file != '.'; file++);                    // Iterate until it find "."

    for(file; *file != '\0'; file++) {
        *type = *file;                                  // It copy the file type
        type++;
    }
    *type = '\0';
}

int checkFile(char *seqName, char *fileToCheck) {    // Function to check if the file name data.name has already been changed
    for(seqName; *seqName != '\0'; seqName++) {      // If it hasn't changed, it will be changed inside the while in the main code
        if(*fileToCheck != *seqName) return 1;
        fileToCheck++;
    }

    return 0;
}

void banner() {
    int i;

    printf("%c", 201);
    for(i = 0; i < 35; i++) printf("%c", 205);
    printf("%c\n", 187);
    printf("%c", 186);
    printf("%1sSequential File Renamer%1s", " ", " ");
    printf("%c\n",186);
    printf("%c", 200);
    for(i = 0; i < 35; i++) printf("%c", 205);
    printf("%c\n", 188);
}