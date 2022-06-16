/* 
Trabalho de threads elaborado para a disciplina de Sistemas Operacionais
Aluno: Felipe Amadori Machado
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>



struct args_t{
    char* palavra;
    char* filename;
    pthread_t tid;
};



void* busca(void* args){

    struct args_t* a = (struct args_t*) args;
    char* linha = NULL;
    size_t len = 0;
    int line_count = 1;
    ssize_t line_size;
    clock_t end, start;
    double total_t;
    

    FILE *fp = fopen(a->filename, "r");
    if (!fp){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    start = clock();

    while(getline(&linha, &len, fp) != -1){
        //verificar se a substring esta na linha
        if (strstr(linha, a->palavra) != NULL){
            printf("Thread: %ld, a string %s foi encontrada na linha %d, do arquivo %s.\n", a->tid, a->palavra, line_count, a->filename);
            end = clock();
            total_t = (double)(end - start)/CLOCKS_PER_SEC;
            printf("Thread: %ld, a string foi encontrada em %f\n", a->tid, total_t);
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
    
    printf("Thread: %ld, a string %s nao foi encontrada no arquivo %s.\n", a->tid, a->palavra, a->filename);
    
    return (void*) 0;

}



int main(int argc, char *argv[])
{

    if (argc != 2){
        printf("Entrada invalida\n");
        exit(1);
    }

    struct args_t a1, a2, a3, a4;
      
    a1.palavra = a2.palavra = a3.palavra = a4.palavra = argv[1];
    a1.filename = "File1_test3.txt";
    a2.filename = "File2_test3.txt";
    a3.filename = "File3_test3.txt";
    a4.filename = "File4_test3.txt";

    pthread_create(&a1.tid, NULL, busca, (void*) &a1);
    pthread_create(&a2.tid, NULL, busca, (void*) &a2);
    pthread_create(&a3.tid, NULL, busca, (void*) &a3);
    pthread_create(&a4.tid, NULL, busca, (void*) &a4);
    pthread_join(a1.tid, NULL);
    pthread_join(a2.tid, NULL);
    pthread_join(a3.tid, NULL);
    pthread_join(a4.tid, NULL);

    
    

    return 0;
}

