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
    printf("\nInsira aqui o endereco do arquivo (Nao inserir caminho com caractere especial): ");
    while((c = getchar()) != '\n') {
        if(c == '\\') folder[i++] = c;
        folder[i++] = c; 
    }
    folder[i] = '\0';
    
    if(_chdir(folder) == 0) system(CLS);                           // Verifica se foi possível trocar o diretório de trabalho
    else {                                                         // Se sim, ele troca
        if(errno == ENOENT) printf("Caminho nao encontrado.\n");
        else printf("Erro desconhecido.\n");
        getchar(); exit(1);
    }

    banner();
    printf("\nInsira o nome sequencial dos arquivos.\n");
    printf("Ex: Teste-#-Teste (# e a posicao onde ocorrera a numeracao)\n");
    for(i = 1; i <= 3; i++) printf("Teste-%d-Teste\n", i);              // Iteração de exemplo
    printf("...\n");
    i = 0;
    while((c = getchar()) != '#') {
        fileName1[i++] = c;
    }
    fileName1[i] = '\0';
    i = 0;
    while((c = getchar()) != '\n') {                    // Apenas caso a pessoa deseje algo após a numeração
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
                sprintf(fileName, "%s%d%s%s", fileName1, i++, fileName2, type); // Formata o nome do arquivo
                printf("%s\n", fileName);
                rename(data.name, fileName);                                    // Renomeia o arquivo
            }
        }

        flag = _findnext(fileP, &data);
    }
    
    _findclose(fileP);
    return 0;
}

void getType(char *file, char *type) {                  // Função para obter o tipo de arquivo
    int i = 0;

    for(file; *file != '.'; file++);                    // Itera até encontrar o '.'

    for(file; *file != '\0'; file++) {
        *type = *file;                                  // Copiar o tipo do arquivo para a string type
        type++;
    }
    *type = '\0';
}

int checkFile(char *seqName, char *fileToCheck) {     // Função para checar se o arquivo de nome data.name já foi alterado
    for(seqName; *seqName != '\0'; seqName++) {      // Se não foi alterado, ele será alterado dentro do while no código principal
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
    printf("%1sRenomeador Sequencial de Arquivos%1s", " ", " ");
    printf("%c\n",186);
    printf("%c", 200);
    for(i = 0; i < 35; i++) printf("%c", 205);
    printf("%c\n", 188);
}