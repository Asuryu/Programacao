// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
// Tomás Gomes Silva - 2020143845

#ifndef ENGINE_H
#define ENGINE_H

// ESTRUTURA PARA GUARDAR OS JOGADORES DO JOGO
//
// Atributos (nome - nome do jogador, pedras - pedras disponíveis, expandir - expansões disponiveis)
typedef struct {
    char nome;
    int pedras;
    int expandir;
} Jogador;

// ESTRUTURA PARA GUARDAR A SUCESSÃO DO JOGO
//
// Atributos (tab - ponteiro para o tabuleiro do jogo, linhas - linhas do tabuleiro, colunas - colunas do tabuleiro, jogador - jogador que efetuou a jogada)
// Atributos (cpu - jogada efetuada pelo computador, pecaJogada - peça jogada nessa jogada, linhaJogada - linha onde foi jogada a peça, colunaJogada - coluna onde foi jogada a peça)
// Atributos (cota - representa o número da jogada, prox - ponteiro para o próximo elemento da lista ligada)
typedef struct objeto tab, *ptabuleiro;
struct objeto
{
    char **tab;
    int linhas;
    int colunas;
    int jogador;
    int cpu;
    char pecaJogada;
    int linhaJogada, colunaJogada;
    int cota;
    ptabuleiro prox;
};

// Gera um tabuleiro quadrado dinâmico do tipo char com a dimensão espcificada
// Para além disso preenche o tabueleiro com "_" que representam o espaço vazio
// Retorna um double-pointer que aponta para o início do tabuleiro 
//
// Parâmetros (linhas - Linhas do tabuleiro, colunas - Colunas do tabuleiro)
char **gerarTabuleiro(int linhas, int colunas);

// Mostra o tabuleiro no estado atual
// Pode servir para dar refresh depois de uma jogada
//
// Parâmetros (tabuleiro - Ponteiro para o tabuleiro de jogo, linhas - Linhas do tabuleiro, colunas - Colunas do tabuleiro)
// Parâmetros (switch - se o switch está a 0 limpa o ecrã antes de mostrar se não não limpa)
void mostrarTabuleiro(char **tabuleiro, int linhas, int colunas, int swtc);

// Verifica se a jogada efetuada permite ganhar o jogo
// Retorna o resultado do jogada (0 - Não vai ganhar / 1 - Ganha o jogo)
//
// Parâmetros (tabuleiro - Ponteiro duplo que aponta para o tabuleiro, cor - Cor da peça, l - Linha, c - Coluna) 
// Parâmetros (linhas - Nrº de linhas totais, colunas - Nrº de colunas totais, turno - Jogador que efetuou a jogada) 
int jogadaVencedora(char **tabuleiro, char cor, int l, int c, int linhas, int colunas, int turno);

// Coloca no tabuleiro uma peça de uma determinada cor e numa determinada posição
// Verifica se a peça pode ser colocada nessa posição
// Retorna o sucesso da operação (0 - Não permitido / 1 - Sucesso)
//
// Parâmetros (tabuleiro - Ponteiro duplo que aponta para o tabuleiro, cor - Cor da peça, l - Linha, c - Coluna) 
// Parâmetros (linhas - Nrº de linhas totais, colunas - Nrº de colunas totais) 
int colocarPeca(char **tabuleiro, char cor, int l, int c, int linhas, int colunas);

// Expande o tabuleiro em linhas ou em colunas
// Retorna um double-pointer que aponta para o início do novo tabuleiro
//
// Parâmetros (tabuleiro - Ponteiro duplo que aponta para o início do tabuleiro, linhas - Linhas para alterar, colunas - Colunas para alterar, tipo - Tipo de expansão: 'L' - Expansão de uma linha / 'C' - Expansão de uma coluna)
char **expandirTabuleiro(char **tabuleiro, int linhas, int colunas, char tipo);

// O computador efetua uma jogada
// Retorna um indicador da jogada escolhida (1 - Peça verde, 2 - Peça amarela, 3 - Peça vermelha, 4 - Pedra, 5 - Expandir linhas, 6 - Expandir colunas)
//
// Parâmetros (tabuleiro - Ponteiro duplo que aponta para o tabuleiro, linhas - Linhas do tabuleiro, colunas - Colunas do tabuleiro) 
// Parâmetros (indicador - jogada escolhida aleatoriamente, B - ponteiro para a struct do jogador B (que representa o CPU neste caso)) 
int verificaJogadaCPU(char **tabuleiro, int linhas, int colunas, int jogada, int indicador, Jogador *B);

// Verifica se uma lista está vazia
// Retorna o resultado da operação (0 - Preenchida / 1 - Vazia)
//
// Parâmetros (p - ponteiro para o início da lista ligada)
int lista_vazia(ptabuleiro p);

// Mostra o tabuleiro em todas as jogadas efetuadas
// Retorna o resultado da operação (0 - Preenchida / 1 - Vazia)
//
// Parâmetros (p - ponteiro para o início da lista ligada)
void mostra_info(ptabuleiro p);

// Procura um elemento com cota c
// Retorna o sucesso da operação (0 - Elemento encontrado / 1 - Elemento não encontrado)
//
// Parâmetros (p - ponteiro para o início da lista ligada, c - cota a ser procurada na lista ligada)
int listaInvertida(ptabuleiro p, int c);

// Preenche a lista com a informação passada nos parâmetros
//
// Parâmetros (p - ponteiro para o início da lista ligada, tabuleiro - ponteiro para o tabuleiro do jogo, l - linhas do tabuleiro, c - colunas do tabuleiro)
// Parâmetros (i - jogada, jogador - jogador que efetuou a jogada, cpu - jogada efetuada pelo computador, cor - peça jogada, lJogada - linha jogada, cJogada - coluna jogada)
void preenche(ptabuleiro p, char **tabuleiro, int l, int c, int i, int jogador, int cpu, char cor, int lJogada, int cJogada);

// Aloca memória e insere um novo elemento no final da lista ligada
// Retorna um ponteiro para o início da lista ligada com o novo elemento
//
// Parâmetros (p - ponteiro para o início da lista ligada, tabuleiro - ponteiro para o tabuleiro do jogo, l - linhas do tabuleiro, c - colunas do tabuleiro)
// Parâmetros (i - jogada, jogador - jogador que efetuou a jogada, cpu - jogada efetuada pelo computador, cor - peça jogada, lJogada - linha jogada, cJogada - coluna jogada)
ptabuleiro insere_final(ptabuleiro p, char **tabuleiro, int l, int c, int i, int jogador, int cpu, char cor, int lJogada, int cJogada);

// Obtém o número de elementos numa lista ligada
// Retorna o número de elementos na lista ligada
//
// Parâmetros (p - ponteiro para o início da lista ligada)
int nrElementos(ptabuleiro p);

// Liberta a memória alocada para a lista ligada
//
// Parâmetros (p - ponteiro para o início da lista ligada)
void liberta_lista(ptabuleiro p);

#endif /* ENGINE_H */
