#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int matrixSize;
int sumTotal = 0;
// int soma_debug = 0; teste para verificar a soma

void *sumArray(void *lines_arg);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void){
    int i, current;
    // printf("Digite o o tamanho da matriz quadrática: ");
    scanf("%d", &matrixSize);

    int matriz[matrixSize][matrixSize];
    pthread_t threads[matrixSize];

    for(i = 0; i < matrixSize; i++){
        for(int j = 0; j < matrixSize; j++){
            // printf("[%d][%d] = ", i, j); 
            scanf("%d", &current);
            // soma_debug += current;
            matriz[i][j] = current;
        }
    }

    // for(i = 0; i < matrixSize; i++){
    //     for(int j = 0; j < matrixSize; j++){
    //        printf("%d ", matriz[i][j]);
    //     }
    //     printf("\n");
    // }

    for (i = 0; i < matrixSize; i++){
        int *linhas_matriz = malloc(matrixSize * sizeof(int));

        if(pthread_create(&(threads[i]), NULL, sumArray, (void*)linhas_matriz)){
            printf("[X] Thread %d not created\n", i);
        }
        for(int k = 0; k < matrixSize; k++){
            linhas_matriz[k] = matriz[i][k]; // avançando na linha;
        }
    }

    for (i = 0; i < matrixSize; i++){
        pthread_join(threads[i], NULL);
    }
    // printf("%d\n", soma_debug); // teste para verificar a soma
    printf("%d\n", sumTotal);
    
}

void *sumArray(void *lines_arg){
    int soma_atual = 0;

    int *linhas_matriz = (int *)lines_arg;
    int tamanho_linhas = sizeof(*linhas_matriz);

    for(int i = 0; i< tamanho_linhas; i++){
        soma_atual = soma_atual + linhas_matriz[i];
    }

    pthread_mutex_lock (&mutex);
    sumTotal = sumTotal + soma_atual;
    pthread_mutex_unlock (&mutex);
    return lines_arg;
}
