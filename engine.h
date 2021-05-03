// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021

#ifndef ENGINE_H
#define ENGINE_H

typedef struct {
    char nome;
    int pedras;
    int expandir;
} Jogador;

typedef struct objeto livro, *plivro;
struct objeto
{
    char **tab;
    int linhas;
    int colunas;
    int cota;
    plivro prox;
};

// Gera um tabuleiro quadrado dinâmico do tipo char com a dimensão espcificada
// Para além disso preenche o tabueleiro com "_" que representam o espaço vazio
// Retorna um double-pointer que aponta para o início do tabuleiro 
//
// Parâmetro (dim - Dimensão do tabuleiro)
char **gerarTabuleiro(int linhas, int colunas);

// Mostra o tabuleiro no estado atual
// Pode servir para dar refresh depois de uma jogada
void mostrarTabuleiro(char **tabuleiro, int linhas, int colunas);

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

#endif /* ENGINE_H */
