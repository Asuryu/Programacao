// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "engine.h"


int guardaJogo(ptabuleiro p, Jogador *A, Jogador *B){
    FILE *f;
    f = fopen("jogo.bin", "wb");
    if(f == NULL) return 0;

    fwrite(A, sizeof(Jogador), 1, f);
    fwrite(B, sizeof(Jogador), 1, f);
    while(p != NULL){
        fwrite(p, sizeof(tab), 1, f);
        for(int j = 0; j<p->linhas; j++)
            fwrite(p->tab[j], p->colunas*sizeof(char), 1, f );
        p = p->prox;
    }

    fclose(f);
    return 1;
    
}

ptabuleiro recuperaJogo(Jogador *A, Jogador *B){
    FILE *f;
    tab *p = NULL, novo;

    f = fopen("jogo.bin", "rb");
    if(f == NULL) return 0;

    char **tabuleiro;
    tabuleiro = gerarTabuleiro(9, 9);
    
    fread(A, sizeof(Jogador), 1, f);
    fread(B, sizeof(Jogador), 1, f);
    while(fread(&novo, sizeof(tab), 1, f) > 0){
        novo.tab = tabuleiro;

        for(int j = 0; j<novo.linhas; j++)
            fread(novo.tab[j], novo.colunas*sizeof(char), 1, f );
        
        p = insere_final(p, novo.tab, novo.linhas, novo.colunas, novo.cota, novo.jogador, novo.cpu, 'G', novo.linhaJogada, novo.colunaJogada);
    }

    fclose(f);
    return p;
}

int exportarJogo(char *ficheiro, ptabuleiro p){
    ficheiro[strlen(ficheiro) - 1] = '\0';
    char extension[5] = ".txt";
    strcat(ficheiro, extension);

    FILE *f;
    f = fopen(ficheiro, "w+");
    if(f == NULL) return 0;

    int l, c, cota, turno, lJogada, cJogada;
    char cor, nome;
    char **tabuleiro;
    while(p != NULL){
        tabuleiro = p->tab;
        cota = p->cota;
        l = p->linhas;
        c = p->colunas;
        turno = p->jogador;
        cor = p->pecaJogada;
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