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

    int l, c;
    l = linhas;
    c = colunas;
    
    fwrite(&linhas, sizeof(int), 1, f);
    fwrite(&colunas, sizeof(int), 1, f);
    fwrite(A, sizeof(Jogador), 1, f);
    fwrite(B, sizeof(Jogador), 1, f);
    fwrite(&turnos, sizeof(int), 1, f);
    fwrite(tabuleiro, sizeof(char**), l * c, f);

    fclose(f);
    return 1;
    
}

char **recuperaJogo(char **tabuleiro, int *linhas, int *colunas, int *turnos, Jogador *A, Jogador *B){
    FILE *f;
    f = fopen("jogo.bin", "rb");
    if(f == NULL) return 0;

    int l, c;

    fread(&l, sizeof(int), 1, f); *linhas = l;
    fread(&c, sizeof(int), 1, f); *colunas = c;
    fread(A, sizeof(Jogador), 1, f);
    fread(B, sizeof(Jogador), 1, f);
    fread(&turnos, sizeof(int), 1, f);
    
    tabuleiro = (char **)malloc(sizeof(char *)*l); 

    for(int i = 0; i < l; i++){
        tabuleiro[i] = (char *)malloc(sizeof(char)*c);
    }
        
    fread(tabuleiro, sizeof(char**), l * c, f);
    printf("asdasdsa%c", **(tabuleiro + 1));

    fclose(f);
    return tabuleiro;
}

int exportarJogo(char *ficheiro, plivro p){
    ficheiro[strlen(ficheiro) - 1] = '\0';
    char extension[5] = ".txt";
    strcat(ficheiro, extension);

    FILE *f;
    f = fopen(ficheiro, "w+");
    if(f == NULL) return 0;

    int l, c, cota;
    while(p != NULL){
        char **tabuleiro = p->tab;
        cota = p->cota;
        l = p->linhas;
        c = p->colunas;

        fprintf(f, "JOGADA %d\n", cota);
        for(int i = 0; i < l; i++){
            for(int j = 0; j < c; j++){
                fprintf(f, "%c ", tabuleiro[i][j]);
            }
            fprintf(f, "\n");
        }
        fprintf(f, "\n\n");
        p = p->prox;
    }

    fclose(f);
    return 1;
}