// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "engine.h"


int guardaJogo(plivro p, Jogador *A, Jogador *B){
    FILE *f;
    f = fopen("jogo.bin", "wb");
    if(f == NULL) return 0;
    
    fwrite(p, sizeof(plivro), 1, f);
    fwrite(A, sizeof(Jogador), 1, f);
    fwrite(B, sizeof(Jogador), 1, f);

    fclose(f);
    return 1;
    
}

int recuperaJogo(plivro p, Jogador *A, Jogador *B){
    FILE *f;
    f = fopen("jogo.bin", "rb");
    if(f == NULL) return 0;

    fread(p, sizeof(plivro), 1, f);
    fread(A, sizeof(Jogador), 1, f);
    fread(B, sizeof(Jogador), 1, f);

    printf("%d", p->linhas);
    printf("%d", A->expandir);
    printf("%d", A->pedras);
    printf("%d", B->pedras);
    printf("%d", B->expandir);

    fclose(f);
    return 1;
}

int exportarJogo(char *ficheiro, plivro p){
    ficheiro[strlen(ficheiro) - 1] = '\0';
    char extension[5] = ".txt";
    strcat(ficheiro, extension);

    FILE *f;
    f = fopen(ficheiro, "w+");
    if(f == NULL) return 0;

    int l, c, cota, turno, lJogada, cJogada;
    char cor, nome;
    while(p != NULL){
        char **tabuleiro = p->tab;
        cota = p->cota;
        l = p->linhas;
        c = p->colunas;
        turno = p->jogador;
        cor = p->peçaJogada;
        lJogada = p->linhaJogada;
        cJogada = p->colunaJogada;

        fprintf(f, "JOGADA %d\n", cota);
        if(turno == 0) nome = 'A';
        else if(turno == 1) nome = 'B';
        else nome = NULL;

        if(cor == NULL || nome == NULL) fprintf(f, "O tabuleiro foi iniciado com %d linhas e %d colunas\n", l, c);
        else if(cor == 'X') fprintf(f, "O jogador %c colocou uma pedra na posição (%d, %d)\n", nome, lJogada, cJogada);
        else if(cor == 'E') fprintf(f, "O jogador %c expandiu o tabuleiro\n", nome);
        else if(cor == 'G') fprintf(f, "O jogador %c colocou uma peça verde na posição (%d, %d)\n", nome, lJogada, cJogada);
        else if(cor == 'Y') fprintf(f, "O jogador %c colocou uma peça amarela na posição (%d, %d)\n", nome, lJogada, cJogada);
        else if(cor == 'R') fprintf(f, "O jogador %c colocou uma peça vermelha na posição (%d, %d)\n", nome, lJogada, cJogada);
        else fprintf(f, "O jogador %c fez uma jogada inesperada que o programa não estava à espera!\n", nome, lJogada, cJogada);

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