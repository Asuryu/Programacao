// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#ifndef UTILS_H
#define UTILS_H

// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

// Verifica se o ficheiro jogo.bin existe
// Return 0: O ficheiro não existe ---- Return 1: O ficheiro existe
int existeFicheiro();

// Limpa o ecrã e mostra uma arte em ASCII
void mostrarASCII();

// Mostra as instruções de como jogar o jogo
void howToPlay();

// Mostra um menu principal onde o jogador pode escolher o que quer fazer
int menu();

#endif /* UTILS_H */
