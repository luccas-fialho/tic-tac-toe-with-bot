#include "jogodavelha.h"

bool par(int x)
{
    return (x % 2 == 0) ? true : false;
}

void printaTabuleiro(char tabuleiro[][MAX])
{
    system("cls");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            (!par(j) || j == 0) ? printf(" %c |", tabuleiro[i][j]) : printf(" %c ", tabuleiro[i][j]);
        }
        (!par(i) || i == 0) ? printf("\n-----------\n") : printf("\n");
    }
}

void inicializaTabuleiro(char tabuleiro[][MAX])
{
    int i, j;
    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
            tabuleiro[i][j] = ' ';
}

bool verificaJogada(char tabuleiro[][MAX], int l, int c, int vez)
{
    if (l < 1 || c < 1 || l > 3 || c > 3)
        return false;

    else if (tabuleiro[l - 1][c - 1] != ' ')
        return false;

    else
    {
        if (jogador(vez) == 'X')
            tabuleiro[l - 1][c - 1] = 'X';
        else
            tabuleiro[l - 1][c - 1] = 'O';

        return true;
    }
}

char verificaGanhador(char tabuleiro[][MAX])
{
    char vencedor = ' ';

    /* Verifica a horizontal */
    for (int i = 0; i < MAX; i++)
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ')
            return tabuleiro[i][0];

    /* Verifica a vertical */
    for (int i = 0; i < MAX; i++)
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ')
            return tabuleiro[0][i];

    /* Verifica a diagonal principal */
    if (tabuleiro[0][0] != ' ' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])
        return tabuleiro[0][0];

    /* Verifica a diagonal secundária */
    if (tabuleiro[2][0] != ' ' && tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][2])
        return tabuleiro[2][0];

    int vazios = 0;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (tabuleiro[i][j] == ' ')
                vazios++;
        }
    }

    // Se não existem mais espaços vazios no tabuleiro.
    if (vencedor == ' ' && vazios == 0)
        return 'V'; // V de Velha ;D
    else
        return vencedor;
}

vetor melhorJogada(char tabuleiro[][MAX])
{
    int melhorPontuacao = -INFINITO;
    vetor jogada;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (tabuleiro[i][j] == ' ')
            {
                tabuleiro[i][j] = 'X';
                int pontuacao = minimax(tabuleiro, 0, false);
                tabuleiro[i][j] = ' ';
                if (pontuacao > melhorPontuacao)
                {
                    melhorPontuacao = pontuacao;
                    jogada.x = i;
                    jogada.y = j;
                }
            }
        }
    }
    return jogada;
}

int minimax(char tabuleiro[][MAX], int profundidade, bool maximizando)
{
    // Condição de parada da recursão (haver ganhador)
    char result = verificaGanhador(tabuleiro);

    if (result != ' ')
    {
        if (result == 'X') return 1; // Possibilidade em que X ganha
        else if (result == 'O') return -1; // Possibilidade em que O ganha
        else return 0; // Possibilidade de empate
    }

    // Se não houver ganhador ainda
    if (maximizando)
    {
        int melhorPontuacao = -INFINITO;
        melhorPontuacao = getMelhorPontuacao(tabuleiro, profundidade, maximizando, &melhorPontuacao);
        return melhorPontuacao;
    }
    else
    {
        int melhorPontuacao = INFINITO;
        melhorPontuacao = getMelhorPontuacao(tabuleiro, profundidade, maximizando, &melhorPontuacao);
        return melhorPontuacao;
    }
}

int getMelhorPontuacao(char tabuleiro[][MAX], int profundidade, bool maximizando, int *melhorPontuacao)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (tabuleiro[i][j] == ' ')
            {
                if(maximizando){
                    tabuleiro[i][j] = 'X';
                    int pontuacao = minimax(tabuleiro, profundidade + 1, false);
                    tabuleiro[i][j] = ' ';
                    *melhorPontuacao = maximo(pontuacao, *melhorPontuacao);
                }
                else
                {
                    tabuleiro[i][j] = 'O';
                    int pontuacao = minimax(tabuleiro, profundidade + 1, true);
                    tabuleiro[i][j] = ' ';
                    *melhorPontuacao = minimo(pontuacao, *melhorPontuacao);
                }
            }
        }
    }
    return *melhorPontuacao;
}

int minimo(int a, int b)
{
    return (((a) < (b)) ? (a) : (b));
}

int maximo(int a, int b)
{
    return (((a) > (b)) ? (a) : (b));
}

char jogador(int vez)
{
    return par(vez) ? 'X' : 'O';
}

void jogo(char tabuleiro[][MAX])
{
    char res = 's', vencedor, bot = 'X';
    int cont_jogadas, l, c, vez = 0;

    while (res == 's')
    {
        cont_jogadas = 1;
        vez = 0;

        inicializaTabuleiro(tabuleiro);

        while (cont_jogadas <= 9)
        {
            printaTabuleiro(tabuleiro);
            if (jogador(vez) == bot) // Se é a vez do computador.
            {
                vetor jogada = melhorJogada(tabuleiro);
                l = jogada.x + 1;
                c = jogada.y + 1;
            }
            else // Jogada do usuário.
            {
                printf("Digite a linha e a coluna: ");
                scanf("%d %d", &l, &c);
            }

            if (verificaJogada(tabuleiro, l, c, vez)) // Se fez uma jogada válida.
            {
                vez++; // Passa a vez.
                cont_jogadas++;
            }
            else
            {
                printf("Jogada invalida!\n");
                system("Pause");
            }
            vencedor = verificaGanhador(tabuleiro);
            if (vencedor == 'X' || vencedor == 'O')
            {
                cont_jogadas = 10; // Se já possui um vencedor, sai do loop e termina o jogo.
            }
        }
        printaTabuleiro(tabuleiro);
        
        if (vencedor == 'V')
            printf("Jogo empatado! :c deu velha\n");
        if (vencedor == 'X')
            printf("Vencedor foi o X! (Computador)\n");
        if (vencedor == 'O')
            printf("Vencedor foi o O! (Você) Parabéns\n");
        printf("Deseja jogar novamente? [s/n]\n");
        scanf("%s", &res);
    }
}
