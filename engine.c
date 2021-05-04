// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "engine.h"
#include "utils.h"

char **gerarTabuleiro(int linhas, int colunas){

    char **tabuleiro;
 
    tabuleiro = (char **)malloc(sizeof(char *)*linhas); 

    for(int i = 0; i < linhas; i++){
        tabuleiro[i] = (char *)malloc(sizeof(char)*colunas);
    }

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            tabuleiro[i][j] = '_';
        }
    }

    return tabuleiro;

}

void mostrarTabuleiro(char **tabuleiro, int linhas, int colunas){

    //mostrarASCII();
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("\n");

}

int jogadaVencedora(char **tabuleiro, char cor, int l, int c, int linhas, int colunas, int turno){

    int empate = 0;
    int horizontal = 0;
    int vertical = 0;
    int diagonal = 0;
    int diagonalX = 0;

    for(int i = 0; i < colunas; i++){
        if(tabuleiro[l - 1][i] != cor) horizontal = 0;
        else horizontal += 1;
    }
    for(int j = 0; j < linhas; j++){
        if(tabuleiro[j][c - 1] != cor) vertical = 0;
        else vertical += 1;
    }
    if(linhas == colunas){
        for(int a = 0; a < linhas; a++){
            if(tabuleiro[a][a] != cor) diagonal = 0;
            else diagonal += 1;
        }
        for(int a = 0; a < linhas; a++){
            if(tabuleiro[a][colunas - a - 1] != cor) diagonalX = 0;
            else diagonalX += 1;
        }
    }
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(tabuleiro[i][j] != '_') empate += 1;
            else empate = 0;
        }
    }

    if(empate == linhas * colunas){
        mostrarASCII();
        printf("\n*** O JOGO ACABOU NUM EMPATE! ***\nFica para a próxima!\n");
        scanf("%c", &cor);
        return 1;
    }

    if(horizontal == colunas){
        mostrarASCII();
        if(turno == 0) printf("\n*** O JOGADOR A É O VENCEDOR DO JOGO! ***\nLinha preenchida!\n");
        else printf("\n*** O JOGADOR B É O VENCEDOR DO JOGO! ***\nLinha preenchida!\n");
        scanf("%c", &cor);
        return 1;
    }
    else if(vertical == linhas){
        mostrarASCII();
        if(turno == 0) printf("\n*** O JOGADOR A É O VENCEDOR DO JOGO! ***\nColuna preenchida!\n");
        else printf("\n*** O JOGADOR B É O VENCEDOR DO JOGO! ***\nColuna preenchida!\n");
        scanf("%c", &cor);
        return 1;
    }
    else if(diagonal == linhas || diagonalX == linhas){
        mostrarASCII();
        if(turno == 0) printf("\n*** O JOGADOR A É O VENCEDOR DO JOGO! ***\nDiagonal preenchida!\n");
        else printf("\n*** O JOGADOR B É O VENCEDOR DO JOGO! ***\nDiagonal preenchida!\n");
        scanf("%c", &cor);
        return 1;
    }
    else {
        return 0;
    }
    
}

int colocarPeca(char **tabuleiro, char cor, int l, int c, int linhas, int colunas){

    if(l > linhas || l <= 0) return 0;
    if(c > colunas || c <= 0) return 0;

    switch(cor){
        case 'X':
            if(tabuleiro[l - 1][c - 1] == '_'){
                tabuleiro[l - 1][c - 1] = 'X';
                return 1;
            }
            printf("Não podes colocar uma PEDRA nessa posição\n");
            return 0;
        case 'G':
            if(tabuleiro[l - 1][c - 1] == '_'){
                tabuleiro[l - 1][c - 1] = 'G';
                return 1;
            }
            printf("Não podes colocar a peça VERDE nessa posição\n");
            return 0;

        case 'Y':
            if(tabuleiro[l - 1][c - 1] == 'G'){
                tabuleiro[l - 1][c - 1] = 'Y';
                return 1;
            }
            printf("Não podes colocar a peça AMARELA nessa posição\n");
            return 0;

        case 'R':
            if(tabuleiro[l - 1][c - 1] == 'Y'){
                tabuleiro[l - 1][c - 1] = 'R';
                return 1;
            }
            printf("Não podes colocar a peça VERMELHA nessa posição\n");
            return 0;

        default:
            printf("Escolhe uma cor válida para jogares\n");
            return 0;
    }

}

char **expandirTabuleiro(char **tabuleiro, int linhas, int colunas, char tipo){

    tabuleiro = (char **)realloc(tabuleiro, sizeof(char *)*linhas);

    for(int i = 0; i < linhas; i++){
        tabuleiro[i] = (char *)realloc(tabuleiro[i], sizeof(char)*colunas);
    }

    if(tipo == 'L'){
        for(int i = linhas - 1; i < linhas; i++){
            for(int j = 0; j < colunas; j++){
                tabuleiro[i][j] = '_';
            }
        }
    }
    else{
        for(int i = 0; i < linhas; i++){
            for(int j = colunas - 1; j < colunas; j++){
                tabuleiro[i][j] = '_';
            }
        }
    }

    return tabuleiro;

}







// LINKED LIST

int lista_vazia(plivro p){
    if(p == NULL) return 1;
    else return 0;
}

void mostra_info(plivro p){
    while(p != NULL){
        mostrarTabuleiro(p->tab, p->linhas, p->colunas);
        p = p->prox;
    }
}

int procura_cota(plivro p, int c){

    while(p != NULL){
        if(p->cota == c){
            mostrarTabuleiro(p->tab, p->linhas, p->colunas);
            return 1;
        }
        else p = p->prox;
    }
    return 0;

}

void preenche(plivro p, char **tabuleiro, int l, int c, int i, int jogador, char cor, int lJogada, int cJogada){
    char **aux;
    aux = (char **)malloc(sizeof(char *)*l); 

    for(int a = 0; a < l; a++){
        aux[a] = (char *)malloc(sizeof(char)*c);
    }

    for(int b = 0; b < l; b++){
        for(int d = 0; d < c; d++){
            aux[b][d] = tabuleiro[b][d];
        }
    }

    p->tab = aux;
    p->linhas = l;
    p->colunas = c;
    p->linhaJogada = lJogada;
    p->colunaJogada = cJogada;
    p->jogador = jogador;
    p->peçaJogada = cor;
    p->cota = i;
    p->prox = NULL;
}

plivro insere_final(plivro p, char **tabuleiro, int l, int c, int i, int jogador, char cor, int lJogada, int cJogada){
    plivro novo, aux;

    novo = malloc(sizeof(livro));
    if(novo == NULL) return p;
    preenche(novo, tabuleiro, l, c, i, jogador, cor, lJogada, cJogada);

    if(p == NULL) p = novo;
    else {
        aux = p;
        while(aux->prox != NULL) aux = aux->prox;
        aux->prox = novo;
    }

    return p;
}

int nrElementos(plivro p){
    int contador = 0;
    while(p != NULL){
        contador++;
        p = p->prox;
    }
    return contador - 1;
}

void liberta_lista(plivro p){
    plivro aux;
    
    while(p != NULL){
        aux = p;
        p = p->prox;
        free(aux);
    }
}