// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

int existeFicheiro(){
    FILE *f;

    f = fopen("jogo.bin", "rb");
    if(f == NULL) return 0;
    return 1;
}

void gerarTabuleiro(char **tabuleiro, int dim){
    tabuleiro = malloc (dim * sizeof (char *));
    for (int i = 0; i < dim; ++i)
        tabuleiro[i] = malloc (dim * sizeof (char));

    for(int a = 0; a < dim; a++){
        for(int b = 0; b < dim; b++){
            tabuleiro[a][b] = 'X';
        }
    }

    for(int a = 0; a < dim; a++){
        for(int b = 0; b < dim; b++){
            printf("%c ", tabuleiro[a][b]);
        }
        printf("\n");
    }
    printf("\n");

}

void mostrarTabuleiro(char **tabuleiro, int dim){

    printf("%d", dim);
    
    for(int a = 0; a < dim; a++){
        for(int b = 0; b < dim; b++){
            printf("%c ", tabuleiro[a][b]);
        }
        printf("\n");
    }
    printf("\n");
}