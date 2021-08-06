/* 
JOGO DA VELHA FEITO POR LUCCAS FIALHO DOS SANTOS NO DIA 04/08/2021.

Utiliza conceitos de árvore para decisão e backtracking, onde se analizam todas as possibilidades de um determinado jogo.

Usando como base: minimax algorithm
https://www.youtube.com/watch?v=sfwlLZ3llFE 6:46

https://www.youtube.com/watch?v=fT3YWCKvuQE

https://www.youtube.com/watch?v=KU9Ch59-4vw

https://www.youtube.com/watch?v=cwzKjFkSyIE

https://www.youtube.com/watch?v=l-hh51ncgDI

https://youtu.be/trKjYdBASyQ code base

*/

#include "jogodavelha.h"

int main()
{
    char tabuleiro[MAX][MAX];

    jogo(tabuleiro);

    return 0;
}
