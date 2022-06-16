#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define FILENAME "File1_test1.txt"



void* busca(void* arg){

    char* linha = NULL;
    char* palavra = (char*) arg;
    size_t len = 0;
    int line_count = 1;
    ssize_t line_size;
    clock_t end, start;
    double total_t;
    

    FILE *fp = fopen(FILENAME, "r");
    if (!fp){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    start = clock();

    while(getline(&linha, &len, fp) != -1){
        //verificar se a substring esta na linha
        if (strstr(linha, palavra) != NULL){
            printf("%s encontrada na linha %d\n", palavra, line_count);
            end = clock();
            total_t = (double)(end - start)/CLOCKS_PER_SEC;
            printf("String encontrada em %f\n", total_t);
            if(fp){
                fclose(fp);
            }
            return (void*) 1;
        }

        line_count++;
    }
    
    if(fp){
        fclose(fp);
    }
    
    printf("String %s nao foi encontrada\n", palavra);
    
    return (void*) 0;

}



int main(int argc, char *argv[])
{

    if (argc != 2){
        printf("Entrada invalida\n");
        exit(1);
    }
    
    char* palavra = argv[1];
    busca(palavra);
    

    return 0;
}

