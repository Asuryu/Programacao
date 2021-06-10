// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Tomás Gomes Silva - 2020143845

// COMPILAR O CÓDIGO:
// gcc -c main.c
// gcc -c ./source/engine.c -o ./o/engine.o
// gcc -c ./source/files.c -o ./o/files.o
// gcc -c ./source/utils.c -o ./o/utils.o
// gcc -o output main.o ./o/engine.o ./o/files.o ./o/utils.o

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/utils.h"
#include "headers/engine.h"
#include "headers/files.h"

int main(){

    Jogador jogadorA; // Struct para guardar informações sobre o jogador A
    Jogador jogadorB; // Struct para guardar informações sobre o jogador B
    int jogada; // Variável que indica em que jogada é que vamos

    int flag = 0; // Flag que nos indica se existe um ficheiro de jogo para ser retomado ou não

    if(existeFicheiro()){ // Se o ficheiro "jogo.bin" existe na pasta do jogo, então:
        
        mostrarASCII(); // Mostra um título todo bonitinho
        char escolha; // Variável que indica se o jogador quer ou não retomar o jogo anterior
        printf("Foi encontrado um ficheiro de jogo.\nPretende continuar o jogo anterior?\n\n");
        do {
            printf("Continuar? (S/N) ");
            scanf("\n%c", &escolha);

            if (escolha == 'N') break;
            else if (escolha == 'S') break;

        } while (escolha != 'S' || escolha != 'N');

        if (escolha == 'S') flag = 1;

    }

    initRandom(); // Inicialização da aleatoriedade

    ptabuleiro lista = NULL; // Inicialização de uma lista ligada para guardar a sucessão de jogadas
    ptabuleiro aux; // Lista ligada para auxiliar na iteração pela lista original

    int randomDim; // Dimensão quadrada do tabuleiro
    int computador; // Indica se o jogador B é o computador ou um humano
    int linhasTotais, colunasTotais, turno = 0; // Linhas e colunas do tabuleiro. Manutenção do turno de jogada
    char **tabuleiro; // Variável que armazena o tabuleiro de jogo

    if(flag == 0){ // Se o utilizar não tiver escolhido continuar o jogo anterior, então:

        if(menu() == 0) computador = 0; // Se menu() retornar 0 então o utilizador não quer jogar contra o computador
        else if(menu() == 1) computador = 1; // Se menu() retornar 1 então o jogador B será o computador

        jogadorA.nome = 'A'; // Jogador A
        jogadorA.pedras = 1; // Inicialização das pedras do jogador A
        jogadorA.expandir = 2; // Inicialização das expansões do jogador A

        jogadorB.nome = 'B'; // Jogador B
        jogadorB.pedras = 1; // Inicialização das pedras do jogador B
        jogadorB.expandir = 2; // Inicialização das expansões do jogador B

        randomDim = intUniformRnd(3, 5); // Escolher um número entre 3 e 5 para as dimensões iniciais do tabuleiro
        linhasTotais = randomDim;
        colunasTotais = randomDim;
        jogada = 1;

        tabuleiro = gerarTabuleiro(linhasTotais, colunasTotais); // Função para gerar um tabuleiro pela primeira vez com tamanho passado nos parâmetros
        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, 0, -1, computador, '\0', -1, -1); // Inserir a jogada 0 (inicialização do tabuleiro) na lista ligada
    
    } else { // Se o utilizador tiver escolhido continuar com o jogo anterior, então:

        lista = recuperaJogo(&jogadorA, &jogadorB); // Função para recuperar a lista ligada com as jogadas do jogo guardado

        aux = lista; // Variável auxiliar para iterar pela lista ligada
        while(aux != NULL){ // Enquanto o elemento atual não for nulo, associa os valores do jogo anterior às variáveis do jogo atual
            computador = aux->cpu;
            linhasTotais = aux->linhas;
            colunasTotais = aux->colunas;
            jogada = aux->cota;
            turno = aux->jogador;
            tabuleiro = aux->tab;
            aux = aux->prox;
        }

    }

    int linha, coluna, pedras, expandir, jogadaAleatoria; // Inicialização de variáveis (linha jogada, coluna jogada, quantidade de pedras, quantidade de expansões, ...)
    char cor, escolha, habilidade, tipo; // Inicialização de variáveis

    do{
        mostrarASCII();
        mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais, 0); // Mostra o tabuleiro no estado atual

        if(computador == 0){ // Se o utilizador tiver escolhido jogar contra um humano, então:
            if(turno == 0) printf("\n[JOGADOR A]\n"); // Cabeçalho para o jogador A se o turno for 0
            else printf("\n[JOGADOR B]\n"); // Cabeçalho para o jogador B se o turno for 1 
        } else if(computador == 1) { // Se o utilizador tiver escolhido jogar contra o computador, então:
            if(turno == 0) printf("\n[JOGADOR A]\n"); // Cabeçalho para o jogador A se o turno for 0
            else{ // Se não, efetua a jogada aleatoriamente escolhida pelo computador
                int retorno = 0;
                do{
                    jogadaAleatoria = intUniformRnd(1, 4); // Número de 1 a 4 que representa a jogada que o computador vai efetuar
                    retorno = verificaJogadaCPU(tabuleiro, linhasTotais, colunasTotais, jogadaAleatoria, &jogadorB); // Função para realizar uma jogada (CPU)

                } while(retorno == 0); // Faz o ciclo enquanto não encontrar uma jogada válida para efetuar
                
                if(jogadaAleatoria == 1){ // Se a jogada escolhida tiver sido "colocar uma peça verde", então:
                    if(retorno == 1){
                        // Adiciona a jogada ao final da lista ligada
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'G', 0, 0);
                        mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais, 1); // Mostra o tabuleiro depois do CPU ter feito a jogada
                        printf("\n[COMPUTADOR]\nColocou uma pe\u00E7a verde"); // Cabeçalho para o CPU

                    }
                    else if(retorno == 2){ // Se a jogada escolhida tiver sido "colocar uma peça amarela", então:
                        // Adiciona a jogada ao final da lista ligada
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'Y', 0, 0);
                        mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais, 1); // Mostra o tabuleiro depois do CPU ter feito a jogada
                        printf("\n[COMPUTADOR]\nColocou uma pe\u00E7a amarela"); // Cabeçalho para o CPU

                    } 
                    else if(retorno == 3){ // Se a jogada escolhida tiver sido "colocar uma peça vermelha", então:
                        // Adiciona a jogada ao final da lista ligada
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'R', 0, 0);
                        mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais, 1); // Mostra o tabuleiro depois do CPU ter feito a jogada
                        printf("\n[COMPUTADOR]\nColocou uma pe\u00E7a vermelha"); // Cabeçalho para o CPU
                    } 
                } 
                else if(jogadaAleatoria == 2){ // Se a jogada escolhida tiver sido "colocar uma pedra", então:
                    // Adiciona a jogada ao final da lista ligada             
                    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'X', 0, 0);
                    mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais, 1); // Mostra o tabuleiro depois do CPU ter feito a jogada
                    printf("\n[COMPUTADOR]\nColocou uma pedra no tabuleiro"); // Cabeçalho para o CPU
                } 
                else if(jogadaAleatoria == 3){ // Se a jogada escolhida tiver sido "expandir as linhas", então:
                    colunasTotais++; // Incrementa as linhas do tabuleiro
                    getchar();
                    // Adiciona a jogada ao final da lista ligada
                    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'E', 0, 0);
                    mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais, 1); // Mostra o tabuleiro depois do CPU ter feito a jogada
                    printf("\n[COMPUTADOR]\nUsou uma expans\u00E3o (colunas)"); // Cabeçalho para o CPU
                } 
                else if(jogadaAleatoria == 4){ // Se a jogada escolhida tiver sido "expandir as colunas", então:
                    colunasTotais++; // Incrementa as colunas do tabuleiro
                    getchar();
                    // Adiciona a jogada ao final da lista ligada
                    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'E', 0, 0);
                    mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais, 1); // Mostra o tabuleiro depois do CPU ter feito a jogada
                    printf("\n[COMPUTADOR]\nUsou uma expans\u00E3o (colunas)"); // Cabeçalho para o CPU
                } 

                printf("\nPressione a tecla ENTER para continuar");
                fflush(stdin);
                getchar();

                jogada++; // Incrementa a jogada
                turno = 0; // Inverte o turno para dar a oportunidade ao outro jogador de jogar
            }
        }

        // Mostrar tabuleiro depois de ter sido alterado
        if(computador == 0){
            mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais, 1);
            if(turno == 0) printf("\n[JOGADOR A]\n");
            else printf("\n[JOGADOR B]\n");
        } else {
            mostrarTabuleiro(tabuleiro, linhasTotais, colunasTotais, 1);
            if(turno == 0) printf("\n[JOGADOR A]\n");
            else printf("\n[COMPUTADOR]\n");
        }

        // Escolha da jogada a efetuar por um jogador humano
        printf("Que jogada queres efetuar? (P - Pe\u00E7a / H - Habilidade / T - Tabuleiro / E - Sair): ");
        scanf("%c", &escolha); // Escolha: P - Colocar uma peça. H - Colocar uma pedra ou expandir. T - Ver as K jogadas anteriores.
        switch(escolha){
            case 'P': // No caso do utilizador querer colocar uma peça
                printf("Onde queres colocar a tua pe\u00E7a? (Linha Coluna Cor): ");
                scanf("%d %d %c", &linha, &coluna, &cor);

                if(colocarPeca(tabuleiro, cor, linha, coluna, linhasTotais, colunasTotais)){ // Se o jogador tiver conseguido colocar a peça
                    if(jogadaVencedora(tabuleiro, cor, linha, coluna, linhasTotais, colunasTotais, turno)){ // Verifica a possibilidade de a jogada ter surtido numa vitória
                        
                        // Caso a jogada tenha surtido numa vitória:

                        // Adiciona a jogada à lista ligada
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, cor, linha, coluna);

                        char exportar;
                        do {
                            printf("\nExportar ficheiro do jogo? (S/N) ");
                            fflush(stdin);
                            scanf("%c", &exportar);

                            if (exportar == 'N'){
                                free(tabuleiro);
                                exit(0);
                            }
                            else if (exportar == 'S') break;

                        } while (exportar != 'S' || exportar != 'N'); // Ciclo para perguntar ao utilizador se quer guardar o jogo

                        mostrarASCII();
                        char fname[30]; // Nome do ficheiro
                        printf("\nIntroduza um nome para o ficheiro\n>> ");
                        fflush(stdin);
                        fgets(fname, 30, stdin); // Obtém o nome para o ficheiro escolhido pelo utilizador
                        exportarJogo(fname, lista); // Exporta as sucessões do jogo para um ficheiro de texto
                        liberta_lista(lista); // Liberta a memória alocada para a lista ligada
                        free(tabuleiro); // Liberta a memória alocada para o tabuleiro
                        exit(0); // Sai do jogo

                    }
                    else { // Se a jogada não tiver surtido numa vitória :
                        
                        // Adiciona a jogada à lista ligada
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, cor, linha, coluna);
                        jogada++; // Incrementa a jogada
                        if(turno == 0) turno = 1; // Inverte os turnos
                        else turno = 0; // Inverte os turnos
                    }
                }

                break;

            case 'H': // No caso do utilizador querer utilizar uma habilidade
                if(turno == 0){ // Se for o jogador A a jogar
                    pedras = jogadorA.pedras; // Guarda as pedras que o jogador A tem disponíveis numa variável
                    expandir = jogadorA.expandir; // Guarda as expansões que o jogador A tem disponíveis numa variável
                }
                else{ // Se for o jogador B a jogar
                    pedras = jogadorB.pedras; // Guarda as pedras que o jogador B tem disponíveis numa variável
                    expandir = jogadorB.expandir; // Guarda as expansões que o jogador B tem disponíveis numa variável
                }

                printf("> Tens %d PEDRAS para jogares\n", pedras);
                printf("> Podes EXPANDIR mais %d vezes\n", expandir);

                printf("Que habilidade queres utilizar? (P - Pedra / E - Expandir): ");
                scanf("\n%c", &habilidade);
                
                // Se o jogador tiver escolhido colocar uma pedra
                if(habilidade == 'P' && pedras > 0){
                    printf("Onde queres colocar a tua pedra? (Linha Coluna): ");
                    scanf("%d %d", &linha, &coluna);
                    if(colocarPeca(tabuleiro, 'X', linha, coluna, linhasTotais, colunasTotais)){ // Se o jogador tiver conseguido colocar a pedra
                        if(turno == 0){
                            jogadorA.pedras = pedras - 1; // Retira uma pedra ao jogador A
                            turno = 1; // Inverte os turnos
                        }
                        else{
                            jogadorB.pedras = pedras - 1; // Retira uma pedra ao jogador B
                            turno = 0; // Inverte os turnos
                        }
                        
                        // Adiciona a jogada à lista ligada
                        lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'X', linha, coluna);
                        jogada++; // Incrementa a jogada
                    }
                }
                // Se o jogador tiver escolhido efetuar uma expansão
                if(habilidade == 'E' && expandir > 0){
                    printf("Qual \u00E9 o tipo de expans\u00E3o que queres fazer? (L - Linha / C - Coluna): ");
                    scanf("\n%c", &tipo);
                    if(tipo == 'L') linhasTotais += 1; // Se o utilizador tiver escolhido expandir uma linha, incrementa as linhas do tabuleiro
                    else if(tipo == 'C') colunasTotais += 1; // Se o utilizador tiver escolhido expandir uma coluna, incrementa as colunas do tabuleiro
                    else break;

                    tabuleiro = expandirTabuleiro(tabuleiro, linhasTotais, colunasTotais, tipo); // Chama a função para expandir o tabuleiro

                    if(turno == 0){
                        jogadorA.expandir = expandir - 1; // Retira uma expansão ao jogador A
                        turno = 1; // Inverte os turnos
                    }
                    else{
                        jogadorB.expandir = expandir - 1; // Retira uma expansão ao jogador B
                        turno = 0; // Inverte os turnos
                    }
                    
                    // Adiciona a jogada à lista ligada
                    lista = insere_final(lista, tabuleiro, linhasTotais, colunasTotais, jogada, turno, computador, 'E', -1, -1);
                    jogada++; // Incrementa a jogada
                }

                break;

            case 'T': // No caso do utilizador querer ver as jogadas anteriores
                mostrarASCII();
                int k; // Jogadas anteriores que o jogador quer visulizar (a definir)
                char continuar = '\0';
                do {
                    //mostrarASCII();
                    if(jogada == 1) k = 0; // Se só tiver havido uma jogada mostra o tabuleiro no estado atual
                    else if(jogada == 2) k = 1; // Se só tiver havido duas jogadas mostra o tabuleiro no estado anterior
                    else{
                        printf("Qual o número de jogadas que quer recuar para visualizar? (1 - %d) ", nrElementos(lista)); // Obtém o numéro de elementos guardados
                        scanf("%d", &k);
                        printf("\n");
                    }
                    
                    listaInvertida(lista, nrElementos(lista) - k - 1); // Inverter a lista e obter os k elementos do início
                    printf("\nPressione a tecla ENTER para continuar");
                    fflush(stdin);
                    getchar();


                } while (k > nrElementos(lista) || continuar == 'N' || k <= 0); // Ciclo obrigar o jogador a introduzir uma jogada válida

                break;

            case 'E': // No caso do utilizador querer sair do jogo
                mostrarASCII();
                printf("Antes de sair pretende guardar o jogo para retomar mais tarde?\n");
                printf("\nGuardar? (S/N) ");

                char guardar;
                do {
                    scanf("%c", &guardar);

                    if (guardar == 'S'){
                        guardaJogo(lista, &jogadorA, &jogadorB);
                        break;
                    }
                    else if (guardar == 'N') break;

                } while (guardar != 'S' || guardar != 'N'); // Ciclo para perguntar se o jogador que guardar o jogo para jogar no futuro
                
                liberta_lista(lista); // Liberta a memória alocada para a lista ligada
                free(tabuleiro); // Liberta a memória alocada para o tabuleiro
                exit(0); // Sai do jogo

            default:
                break;
        }

    } while (1); // Ciclo de jogo

    return 0;

}