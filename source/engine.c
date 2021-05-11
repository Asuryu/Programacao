// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Tomás Gomes Silva - 2020143845

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/engine.h"
#include "../headers/utils.h"

char **gerarTabuleiro(int linhas, int colunas){

    char **tabuleiro; // Variável onde o tabuleiro vai ser guardado
 
    tabuleiro = (char **)malloc(sizeof(char *)*linhas); // Aloca memória para as linhas cada linha com tamanho para um char*

    for(int i = 0; i < linhas; i++){ // Para cada linha do tabuleiro, faz: (dar "área ao tabuleiro")
        tabuleiro[i] = (char *)malloc(sizeof(char)*colunas); // Aloca memória para as colunas com tamanho para um char
    }

    for(int i = 0; i < linhas; i++){ // Percorre as linhas do tabuleiro
        for(int j = 0; j < colunas; j++){ // Percorre as colunas do tabuleiro
            tabuleiro[i][j] = '_'; // Coloca todos os espaços do tabuleiro com o caractere "_"
        }
    }

    return tabuleiro; // Retorna o ponteiro para o início do tabuleiro

}

void mostrarTabuleiro(char **tabuleiro, int linhas, int colunas){

    mostrarASCII();
    for(int i = 0; i < linhas; i++){ // Percorre as linhas do tabuleiro
        for(int j = 0; j < colunas; j++){ // Percorre as colunas do tabuleiro
            printf("%c ", tabuleiro[i][j]); // Mostra o que é que está no par linha/coluna
        }
        printf("\n");
    }

    printf("\n");

}

int jogadaVencedora(char **tabuleiro, char cor, int l, int c, int linhas, int colunas, int turno){

    // Flags de controlo
    int empate = 0; 
    int horizontal = 0;
    int vertical = 0;
    int diagonal = 0;
    int diagonalX = 0;

    for(int i = 0; i < colunas; i++){ // Percorre as colunas do tabuleiro para verificar se uma determinada coluna está completamente preenchida
        if(tabuleiro[l - 1][i] != cor) horizontal = 0; // Se nessa posição da coluna estiver uma peça de cor diferente da colocada o contador volta a 0
        else horizontal += 1; // Se não o contador incrementa
    }
    for(int j = 0; j < linhas; j++){ // Percorre as linhas do tabuleiro para verificar se uma determinada linha está completamente preenchida
        if(tabuleiro[j][c - 1] != cor) vertical = 0; // Se nessa posição da linha estiver uma peça de cor diferente da colocada o contador volta a 0
        else vertical += 1; // Se não o contador incrementa
    }
    if(linhas == colunas){ // Se o tabuleiro for quadrado isso abre a possibilidade de alguém ganhar na diagonal
        for(int a = 0; a < linhas; a++){ // Percorre a diagonal principal para verificar se essa diagonal está completamente preenchida
            if(tabuleiro[a][a] != cor) diagonal = 0; // Se nessa posição da diagonal estiver uma peça de cor diferente da colocada o contador volta a 0
            else diagonal += 1; // Se não o contador incrementa
        }
        for(int a = 0; a < linhas; a++){ // Percorre a diagonal "secundária" para verificar se essa diagonal está completamente preenchida
            if(tabuleiro[a][colunas - a - 1] != cor) diagonalX = 0; // Se nessa posição da diagonal estiver uma peça de cor diferente da colocada o contador volta a 0
            else diagonalX += 1; // Se não o contador incrementa
        }
    }
    for(int i = 0; i < linhas; i++){ // Percorre as linhas do tabuleiro
        for(int j = 0; j < colunas; j++){ // Percorre as colunas do tabuleiro
            if(tabuleiro[i][j] != '_') empate += 1; // Se a posição é diferente de "_" o contador incrementa
            else empate = 0; // Se não o contador volta a zero
        }
    }

    if(empate == linhas * colunas){ // Se o contador for igual ao produto das linhas pelas colunas quer dizer que não há nenhum espaço em branco
        mostrarASCII();
        printf("\n*** O JOGO ACABOU NUM EMPATE! ***\nFica para a próxima!\n");
        scanf("%c", &cor);
        return 1;
    }

    if(horizontal == colunas){ // Se o contador for igual ao número de colunas quer dizer que a coluna está completa com a mesma cor
        mostrarASCII();
        if(turno == 0) printf("\n*** O JOGADOR A É O VENCEDOR DO JOGO! ***\nLinha preenchida!\n");
        else printf("\n*** O JOGADOR B É O VENCEDOR DO JOGO! ***\nLinha preenchida!\n");
        scanf("%c", &cor);
        return 1;
    }
    else if(vertical == linhas){ // Se o contador for igual ao número de linhas quer dizer que a linha está completa com a mesma cor
        mostrarASCII();
        if(turno == 0) printf("\n*** O JOGADOR A É O VENCEDOR DO JOGO! ***\nColuna preenchida!\n");
        else printf("\n*** O JOGADOR B É O VENCEDOR DO JOGO! ***\nColuna preenchida!\n");
        scanf("%c", &cor);
        return 1;
    }
    else if(diagonal == linhas || diagonalX == linhas){ // Se o contador for igual ao número de linhas/colunas quer dizer que ou a diagonal principal ou a diagonal "secundária" está completa com a mesma cor
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

    if(l > linhas || l <= 0) return 0; // Retorna 0 se o jogador tiver tentado colocar uma peça numa linha superior ao total
    if(c > colunas || c <= 0) return 0; // Retorna 0 se o jogador tiver tentado colocar uma peça numa coluna superior ao total

    switch(cor){ // Switch-case para a cor escolhida pelo utilizador
        case 'X': // Caso o jogador tenha escolhido colocar uma pedra:
            if(tabuleiro[l - 1][c - 1] == '_'){ // Se essa posição estiver vazia (_), então:
                tabuleiro[l - 1][c - 1] = 'X'; // Coloca nessa mesma posição uma pedra (X)
                return 1; // Retorna o sucesso da operação
            }
            return 0;
        case 'G': // Caso o jogador tenha escolhido colocar uma peça verde:
            if(tabuleiro[l - 1][c - 1] == '_'){ // Se essa posição estiver vazia (_), então:
                tabuleiro[l - 1][c - 1] = 'G'; // Coloca nessa mesma posição uma peça verde (G)
                return 1; // Retorna o sucesso da operação
            }
            return 0;

        case 'Y': // Caso o jogador tenha escolhido colocar uma peça amarela:
            if(tabuleiro[l - 1][c - 1] == 'G'){ // Se nessa posição estiver uma peça verde (G), então:
                tabuleiro[l - 1][c - 1] = 'Y'; // Coloca nessa mesma posição uma peça amarela (Y)
                return 1; // Retorna o sucesso da operação
            }
            return 0;

        case 'R': // Caso o jogador tenha escolhido colocar uma peça vermelha:
            if(tabuleiro[l - 1][c - 1] == 'Y'){ // Se nessa posição estiver uma peça amarela (Y), então:
                tabuleiro[l - 1][c - 1] = 'R'; // Coloca nessa mesma posição uma peça vermelha (R)
                return 1; // Retorna o sucesso da operação
            }
            return 0;

        default:
            return 0;
    }

}

char **expandirTabuleiro(char **tabuleiro, int linhas, int colunas, char tipo){

    tabuleiro = (char **)realloc(tabuleiro, sizeof(char *)*linhas); // Realoca memória para a expansão do tabuleiro em termos de linhas

    for(int i = 0; i < linhas; i++){ // Percorre as linhas do tabuleiro
        tabuleiro[i] = (char *)realloc(tabuleiro[i], sizeof(char)*colunas); // Realoca memória para a expansão do tabuleiro em termos de colunas
    }

    if(tipo == 'L'){ // Se o jogador tiver escolhido expandir uma linha
        for(int i = linhas - 1; i < linhas; i++){ // Percorre a linha recentemente criada (última linha)
            for(int j = 0; j < colunas; j++){ // Percorre todas as colunas do tabuleiro
                tabuleiro[i][j] = '_'; // Coloca os espaços vazios prontos a serem preenchidos
            }
        }
    }
    else{ // Se o jogador tiver escolhido expandir uma coluna
        for(int i = 0; i < linhas; i++){ // Percorre todas as linhas do tabuleiro
            for(int j = colunas - 1; j < colunas; j++){ // Percorre a coluna recentemente criada (última coluna)
                tabuleiro[i][j] = '_'; // Coloca os espaços vazios prontos a serem preenchidos
            }
        }
    }

    return tabuleiro; // Retorna um ponteiro para o início do tabuleiro expandido

}

int verificaJogadaCPU(char **tabuleiro, int linhas, int colunas, int jogada, int indicador, Jogador *B){

    int pedras = B->pedras; // As pedras disponíveis do CPU correspondem às peças do jogador B
    int expandir = B->expandir; // As expansões disponíveis do CPU correspondem às expansões do jogador B

    if(indicador == 1){ // Se a jogada aleatoriamente escolhida tiver sido colocar uma peça:
        for(int i = 0; i < linhas; i++){ // Percorre as linhas do tabuleiro
            for(int j = 0; j < colunas; j++){ // Percorre as colunas do tabuleiro
                if(tabuleiro[i][j] == '_'){ // Se a posição escolhida estiver vazia
                    colocarPeca(tabuleiro, 'G', i+1, j+1, linhas, colunas); // Coloca uma peça verde nessa mesma posição
                    return 1; // Retorna um indicador de sucesso particular
                }
                else if(tabuleiro[i][j] == 'G'){ // Se na posição escolhida estiver uma peça verde
                    colocarPeca(tabuleiro, 'Y', i+1, j+1, linhas, colunas); // Coloca uma peça amarela nessa mesma posição
                    return 2; // Retorna um indicador de sucesso particular
                }
                else if(tabuleiro[i][j] == 'Y'){ // Se na posição escolhida estiver uma peça amarela
                    colocarPeca(tabuleiro, 'R', i+1, j+1, linhas, colunas); // Coloca uma peça vermelha nessa mesma posição
                    return 3; // Retorna um indicador de sucesso particular
                }
            }
        }
        return 0; // Retorna o fracasso da operação
    }

    else if(indicador == 2){ // Se a jogada aleatoriamente escolhida tiver sido colocar uma pedra:
        if(pedras > 0){ // Se o CPU tiver pedras para jogar:
            for(int i = 0; i < linhas; i++){ // Percorre as linhas do tabuleiro
                for(int j = 0; j < colunas; j++){ // Percorre as colunas do tabuleiro
                    if(tabuleiro[i][j] == '_'){ // Se a posição escolhida estiver vazia
                        colocarPeca(tabuleiro, 'X', i+1, j+1, linhas, colunas); // Coloca uma pedra nessa mesma posição
                        B->pedras = pedras - 1; // Decrementa as pedras disponíveis para o CPU
                        return 4; // Retorna um indicador de sucesso particular
                    }
                }
            }
            return 0; // Retorna o fracasso da operação
        }
        else return 0; // Retorna o fracasso da operação
    }

    else if(indicador == 3){ // Se a jogada aleatoriamente escolhida tiver sido expandir uma linha:
        if(expandir > 0){ // Se o CPU tiver expansões para utilizar:
            tabuleiro = expandirTabuleiro(tabuleiro, linhas + 1, colunas, 'L'); // Expande o tabuleiro por uma linha
            B->expandir = expandir - 1; // Decrementa as expansões disponíveis para o CPU
            return 5; // Retorna um indicador de sucesso particular
        }
        else return 0;
    }

    else if(indicador == 4){ // Se a jogada aleatoriamente escolhida tiver sido expandir uma coluna:
        if(expandir > 0){ // Se o CPU tiver expansões para utilizar:
            tabuleiro = expandirTabuleiro(tabuleiro, linhas, colunas + 1, 'C'); // Expande o tabuleiro por uma linha
            B->expandir = expandir - 1; // Decrementa as expansões disponíveis para o CPU
            return 6; // Retorna um indicador de sucesso particular
        }
        else return 0; // Retorna o fracasso da operação
    }

    else return 0; // Retorna o fracasso da operação

}

int lista_vazia(ptabuleiro p){
    if(p == NULL) return 1; // Se o elemento atual é NULO retorna 0 pois a lista está vazia
    else return 0; // Se não retorna 0
}

void mostra_info(ptabuleiro p){
    while(p != NULL){ // Percorre a lista ligada enquanto o elemento atual não é nulo
        mostrarTabuleiro(p->tab, p->linhas, p->colunas); // Mostra o tabuleiro desse elemento da lista ligada
        p = p->prox; // Salta para o próximo elemento da lista ligada
    }
}

int procura_cota(ptabuleiro p, int c){

    while(p != NULL){ // Percorre a lista ligada enquanto o elemento atual não é nulo
        if(p->cota == c){ // Se a cota corresponde à cota pesquisada, então:
            mostrarTabuleiro(p->tab, p->linhas, p->colunas); // Mostra o tabuleiro dessa cota
            return 1; // Retorna o sucesso da operação
        }
        else p = p->prox; // Se não salta para o próximo elemento da lista ligada
    }
    return 0;

}

void preenche(ptabuleiro p, char **tabuleiro, int l, int c, int i, int jogador, int cpu, char cor, int lJogada, int cJogada){
    char **aux; // Variável auxiliar para alojar o tabuleiro temporariamente

    aux = (char **)malloc(sizeof(char *)*l); // Aloca memória para as linhas cada linha com tamanho para um char*

    for(int a = 0; a < l; a++){ // Para cada linha do tabuleiro, faz: (dar "área ao tabuleiro")
        aux[a] = (char *)malloc(sizeof(char)*c); // Aloca memória para as colunas cada coluna com tamanho para um char
    }

    for(int b = 0; b < l; b++){ // Percorre as linhas do tabuleiro auxiliar
        for(int d = 0; d < c; d++){ // Percorre as colunas do tabuleiro auxiliar
            aux[b][d] = tabuleiro[b][d]; // Iguala os dois tabuleiros
        }
    }

    // Preenche o elemento da lista ligada com as informações passadas nos parâmetros da função
    p->tab = aux;
    p->linhas = l;
    p->colunas = c;
    p->linhaJogada = lJogada;
    p->colunaJogada = cJogada;
    p->jogador = jogador;
    p->cpu = cpu;
    p->pecaJogada = cor;
    p->cota = i;
    p->prox = NULL;
}

ptabuleiro insere_final(ptabuleiro p, char **tabuleiro, int l, int c, int i, int jogador, int cpu, char cor, int lJogada, int cJogada){
    ptabuleiro novo, aux; // Declaração de uma variável para o novo elemento e uma variável auxiliar

    novo = malloc(sizeof(tab)); // Aloca memória para um novo elemento
    if(novo == NULL) return p; // Se houver algum problema a alocar memória para o novo elemento retorna o ponteiro para o início da lista inalterada
    preenche(novo, tabuleiro, l, c, i, jogador, cpu, cor, lJogada, cJogada); // Preenche o novo elemento da lista com a informação passada nos parâmetros

    if(p == NULL) p = novo; // Se a lista ligada estiver vazia então isso quer dizer que o novo elemento vai para o início da lista
    else { // Caso a lista não esteja vazia:
        aux = p; // Igualar a variável auxiliar à lista ligada original
        while(aux->prox != NULL) aux = aux->prox; // Percorre a lista ligada até encontrar o último elemento e será nesse sítio que o novo elemento irá ficar
        aux->prox = novo; // O ponteiro para o novo elemento é o novo elemento adicionado ao final da lista previamente 
    }

    return p; // Retorna um ponteiro para o ínicio da lista com o novo elemento no final
}

int nrElementos(ptabuleiro p){
    int contador = 0; // Inicia o contador de elementos a 0
    while(p->prox != NULL){ // Enquanto o ponteiro para o próximo elemento não for nulo:
        contador++; // Incrementa o contador
        p = p->prox; // Salta para o próximo elemento da lista ligada
    }
    return contador; // Retorna o número de elementos
}

void liberta_lista(ptabuleiro p){
    ptabuleiro aux; // Variável auxiliar
    
    while(p != NULL){ // Enquanto o elemento atual não for NULO
        aux = p; // A variável auxiliar toma o valor do elemento atual
        p = p->prox; // Salta para o próximo elemento da lista ligada
        free(aux); // Liberta a memória alocada para a lista auxiliar "aux" e consequentemente liberta também a lista utilizada durante o jogo
    }
}