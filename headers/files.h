// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Tomás Gomes Silva - 2020143845

#ifndef FILES_H
#define FILES_H

// Guarda o jogo atual num ficheiro binário para ser acedido mais tarde
// Retorna o sucesso da operação (0 - Erro / 1 - Sucesso)
//
// Parâmetros (linhas - Ponteiro para o número de linhas total, colunas - Ponteiro para o número de colunas total)
// Parâmetros (turnos - Ponteiro para a varíavel que nos indica o utilizador que ficou por jogar)
// Parâmetros (A e B - Ponteiro para a estrutura que contém a informação do jogador A/B)
int guardaJogo(ptabuleiro p, Jogador *A, Jogador *B);

// Recupera um jogo anterior inacabado contido num ficheiro binário
// Retorna o sucesso da operação (0 - Erro / 1 - Sucesso)
//
// Parâmetros (linhas - Ponteiro para a variável que vai guardar de linhas total, colunas - Ponteiro para a variável que vai guardar o número de colunas total)
// Parâmetros (turnos - Ponteiro para a varíavel que vai guardar o utilizador que ficou por jogar)
// Parâmetros (A e B - Ponteiro para a estrutura que vai guardar a informação do jogador A/B)
ptabuleiro recuperaJogo(Jogador *A, Jogador *B);

// Guarda a sucesão do tabuleiro ao longo do jogo num ficheiro de texto
// Retorna o sucesso da operação (0 - Erro / 1 - Sucesso)
//
// Parâmetros (ficheiro - Ponteiro para o array que contém o nome que o utiliador escolheu para o ficheiro)
int exportarJogo(char *ficheiro, ptabuleiro p);

#endif /* FILES_H */
