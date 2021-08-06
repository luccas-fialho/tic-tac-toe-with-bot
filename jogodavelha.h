#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#define MAX 3
#define INFINITO 999999

typedef struct vetor {  
    int x, y;
} vetor;

/* retorna se um numero é par ou não */
bool par(int x);

/* printa o tabuleiro */
void printaTabuleiro(char tabuleiro[][MAX]);

/* inicializa o tabuleiro com todas as casas vazias */
void inicializaTabuleiro(char tabuleiro[][MAX]);

/* verifica se o jogador fez uma jogada permitida */
bool verificaJogada(char tabuleiro[][MAX], int l, int c, int vez);

/* retorna X, O ou V dependendo de quem ganhar */
char verificaGanhador(char tabuleiro[][MAX]);

/* Retorna um vetor com as coordenadas da melhor jogada que o computador pode fazer */
vetor melhorJogada(char tabuleiro[][MAX]);

/* Função que realiza o algoritmo minimax, baseado em árvore/backtracking */
int minimax(char tabuleiro[][MAX], int profundidade, bool maximizando);

/* Retorna a melhor pontuação para determinado jogador */
int getMelhorPontuacao(char tabuleiro[][MAX], int profundidade, bool maximizando, int *melhorPontuacao);

/* Retorna o menor valor entre dois valores */
int minimo(int a, int b);

/* Retorna o maior valor entre dois valores */
int maximo(int a, int b);

/* Retorna o qual é o jogador da vez */
char jogador(int vez);

/* função principal do jogo */
void jogo(char tabuleiro[][MAX]);