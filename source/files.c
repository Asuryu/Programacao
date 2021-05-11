// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Tomás Gomes Silva - 2020143845

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/files.h"
#include "../headers/engine.h"


int guardaJogo(ptabuleiro p, Jogador *A, Jogador *B){
    FILE *f; // Criar um ponteiro para o ficheiro
    f = fopen("jogo.bin", "wb"); // Abrir o ficheiro "jogo.bin" no modo de escrita binária
    if(f == NULL) return 0; // Se algum erro tiver surgido retorna 0

    fwrite(A, sizeof(Jogador), 1, f); // Escreve a struct referente ao jogador A
    fwrite(B, sizeof(Jogador), 1, f); // Escreve a struct referente ao jogador B
    while(p != NULL){ // Percorre a lista ligada até ao último elemento
        fwrite(p, sizeof(tab), 1, f); // Escreve o elemento da lista ligada
        for(int j = 0; j<p->linhas; j++) // Percorre o tabuleiro do elemento atual
            fwrite(p->tab[j], p->colunas*sizeof(char), 1, f ); // Escreve o tabuleiro desse elemento da lista ligada
        p = p->prox; // Avança para o próximo elemento da lista ligada
    }

    fclose(f); // Fecha o ficheiro
    return 1; // Retorna o sucesso da operação
    
}

ptabuleiro recuperaJogo(Jogador *A, Jogador *B){
    FILE *f; // Criar um ponteiro para o ficheiro
    tab *p = NULL, novo; // Criar uma lista ligada para colocar as sucessões do jogo anterior e uma variável auxiliar

    f = fopen("jogo.bin", "rb"); // Abrir o ficheiro "jogo.bin" no modo leitura binária
    if(f == NULL) return 0; // Se algum erro tiver surgido retorna 0

    char **tabuleiro; // Cria uma variável para armazenar o tabuleiro
    tabuleiro = gerarTabuleiro(9, 9); // Aloca memória para receber o tabuleiro
    
    fread(A, sizeof(Jogador), 1, f); // Lê a struct referente ao jogador A
    fread(B, sizeof(Jogador), 1, f); // Lê a struct referente ao jogador B
    while(fread(&novo, sizeof(tab), 1, f) > 0){ // Lê os elementos da lista ligada para a variável novo enquanto existir coisas para ler
        novo.tab = tabuleiro; // A memória alocada passa para a variável que vai receber o tabuleiro

        for(int j = 0; j<novo.linhas; j++) // Percorre o tabuleiro guardado
            fread(novo.tab[j], novo.colunas*sizeof(char), 1, f ); // Lê o tabuleiro para a variável "novo.tab"
        
        // Adiciona este novo objeto ao final da lista ligada
        p = insere_final(p, novo.tab, novo.linhas, novo.colunas, novo.cota, novo.jogador, novo.cpu, novo.pecaJogada, novo.linhaJogada, novo.colunaJogada);
    }

    fclose(f); // Fecha o ficheiro
    return p; // Retorna um ponteiro para o início da lista ligada que foi recuperada
}

int exportarJogo(char *ficheiro, ptabuleiro p){
    ficheiro[strlen(ficheiro) - 1] = '\0'; // Adiciona um ESCAPE CHARACTER para tornar o array numa string válida
    char extension[5] = ".txt"; // Array que contém a string que representa o formato do ficheiro (.txt)
    strcat(ficheiro, extension); // Concatena o nome do ficheiro e a extensão do ficheiro

    FILE *f; // Criar um ponteiro para o ficheiro
    f = fopen(ficheiro, "w+"); // Criar o ficheiro e abri-lo no modo de escrita
    if(f == NULL) return 0; // Se algum erro tiver surgido retorna 0

    int l, c, cota, turno, lJogada, cJogada; // Decalração das variáveis para armazenaram informação em cada iteração
    char cor, nome; // Decalração das variáveis para armazenaram informação em cada iteração
    char **tabuleiro; // Variável onde o tabuleiro vai ser guardado em cada iteração
    while(p != NULL){ // Enquanto o elemento atual não for NULO
        tabuleiro = p->tab;
        cota = p->cota;
        l = p->linhas;
        c = p->colunas;
        turno = p->jogador;
        cor = p->pecaJogada;
        lJogada = p->linhaJogada;
        cJogada = p->colunaJogada;

        fprintf(f, "JOGADA %d\n", cota); // Escreve o número da jogada no ficheiro
        if(turno == 0) nome = 'A'; // Escreve o nome do jogador A na jogada atual no ficheiro (caso a jogada tenha sido feita pelo jogador A)
        else if(turno == 1) nome = 'B'; // Escreve o nome do jogador B na jogada atual no ficheiro (caso a jogada tenha sido feita pelo jogador B)
        else nome = NULL; // Caso contrário o nome do jogador é NULO

        // Inclui uma mensagem com o detalhe do que é que aconteceu na jogada atual
        if(cor == NULL || nome == NULL) fprintf(f, "O tabuleiro foi iniciado com %d linhas e %d colunas\n", l, c);
        else if(cor == 'X') fprintf(f, "O jogador %c colocou uma pedra na posição (%d, %d)\n", nome, lJogada, cJogada);
        else if(cor == 'E') fprintf(f, "O jogador %c expandiu o tabuleiro\n", nome);
        else if(cor == 'G') fprintf(f, "O jogador %c colocou uma peça verde na posição (%d, %d)\n", nome, lJogada, cJogada);
        else if(cor == 'Y') fprintf(f, "O jogador %c colocou uma peça amarela na posição (%d, %d)\n", nome, lJogada, cJogada);
        else if(cor == 'R') fprintf(f, "O jogador %c colocou uma peça vermelha na posição (%d, %d)\n", nome, lJogada, cJogada);
        else fprintf(f, "O jogador %c fez uma jogada inesperada que o programa não estava à espera!\n", nome, lJogada, cJogada);

        for(int i = 0; i < l; i++){ // Percorre as linhas do tabuleiro
            for(int j = 0; j < c; j++){ // Percorre as colunas do tabuleiro
                fprintf(f, "%c ", tabuleiro[i][j]); // Escreve o tabuleiro no ficheiro
            }
            fprintf(f, "\n"); // Escreve uma linha em branco no ficheiro
        }
        fprintf(f, "\n\n"); // Escreve duas linhas em branco no ficheiro
        p = p->prox; // Salta para o próximo elemento da lista ligada
    }

    fclose(f); // Fecha o ficheiro
    return 1; // Retorna o sucesso da operação
}