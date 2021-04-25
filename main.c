// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

int main(){

    system("clear");
    initRandom();

    printf("   _____                      ____                     \n");
    printf("  / ___/___  ____ ___  ____ _/ __/___  _________  _____\n");
    printf("  |__ \\/ _ \\/ __ `__ \\/ __ `/ /_/ __ \\/ ___/ __ \\/ ___/\n");
    printf(" ___/ /  __/ / / / / / /_/ / __/ /_/ / /  / /_/ (__  ) \n");
    printf("/____/\\___/_/ /_/ /_/\\__,_/_/  \\____/_/   \\____/____/  \n");
    printf("                                                       \n");
    printf("Jogo dos Semáforos - Trabalho Prático de Programação\n\n\n");

    if(existeFicheiro()){
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
        int randomDim = intUniformRnd(3, 5);
        char **tabuleiro;
        tabuleiro = gerarTabuleiro(tabuleiro, randomDim);

        printf("%c", *tabuleiro[0]);

    }

    return 0;

}