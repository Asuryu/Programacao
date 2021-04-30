// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "engine.h"


int guardaJogo(char **tabuleiro, int *linhas, int *colunas, int *turnos, Jogador *A, Jogador *B){
    FILE *f;
    f = fopen("jogo.bin", "wb");
    if(f == NULL) return 0;

    fwrite(&linhas, sizeof(int), 1, f);
    fwrite(&colunas, sizeof(int), 1, f);
    fwrite(&turnos, sizeof(int), 1, f);
    fwrite(A, sizeof(Jogador), 1, f);
    fwrite(B, sizeof(Jogador), 1, f);

    fclose(f);
    return 1;
    
}

int recuperaJogo(char **tabuleiro, int *linhas, int *colunas, int *turnos, Jogador *A, Jogador *B){
    FILE *f;
    f = fopen("jogo.bin", "rb");
    if(f == NULL) return 0;

    // printf("%c", tabuleiro[0][0]);

    // for(int i = 0; i < linhas; ++i){
    //     fread(tabuleiro[i], sizeof(tabuleiro[i][0]), linhas, f);
    // }

    // printf("%c", tabuleiro[0][0]);

    fread(linhas, sizeof(int), 1, f);
    fread(colunas, sizeof(int), 1, f);
    fread(turnos, sizeof(int), 1, f);
    fread(A, sizeof(Jogador), 1, f);
    fread(B, sizeof(Jogador), 1, f);

    fclose(f);
    return 1;
}

int exportarJogo(char *ficheiro){
    ficheiro[strlen(ficheiro) - 1] = '\0';
    char extension[5] = ".txt";
    strcat(ficheiro, extension);
    puts(ficheiro);

    FILE *f;
    f = fopen(ficheiro, "w+");
    if(f == NULL) return 0;

    fclose(f);
    return 1;
}