// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "utils.c"

int main(){

    if(existeFicheiro()){
        mostrarASCII();
        char escolha;
        printf("Foi encontrado um ficheiro de jogo.\nPretende continuar o jogo anterior? (S/N)\n");
        do {
            scanf("%c", &escolha);

            if (escolha == 'N') break;
            else if (escolha == 'S') break;

        } while (escolha != 'S' || escolha != 'N');

        if (escolha == 'S') printf("Escolheu a opção SIM\n");
        else printf("Escolheu a opção NÃO\n");
    }

    else {
        menu();
        initRandom();
        int randomDim = intUniformRnd(3, 5);
        char **tabuleiro = gerarTabuleiro(randomDim);
        mostrarTabuleiro(tabuleiro, randomDim);


        int linha, coluna;
        char cor;

        while(1){
            printf("Onde queres colocar a tua peça? (Linha/Coluna/Cor): ");
            scanf("%d/%d/%c", &linha, &coluna, &cor);

            colocarPeca(tabuleiro, cor, linha, coluna);
            mostrarTabuleiro(tabuleiro, randomDim);
        }

    }

    return 0;

}