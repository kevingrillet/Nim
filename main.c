/**
 * \file main.c
 * \brief NIM Game
 * \author Kévin G.
 * \version 0.1
 * \date 23/11/2017
 */
#include "nim.h"

/**
 * \fn int main (void)
 * \brief Start of the program.
 *
 * \return EXIT_SUCCESS (0) - Successful termination.
 */
int main(void)
{
    bool iPlay = DEFAULT_VALUE;
    int iCoins = SIZE;
    int iGameMode = DEFAULT_VALUE;
    int iPlayerTurn = DEFAULT_VALUE;
    int iTurn = DEFAULT_VALUE;
    gameMainMenu();
    do
    {
        iCoins = SIZE;
        iGameMode = gameTypeMenu();
        iPlayerTurn = gameFlipTheCoin();
        do
        {
            gameDraw(iCoins);
            if (iTurn != DEFAULT_VALUE)
            {
                iPlayerTurn = (iPlayerTurn == PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE);
            }
            iTurn++;
            iCoins = gameTake(iCoins, gameTurn(iGameMode, iPlayerTurn, iCoins));
        } while (!gameAnnounceWinner(iCoins, iPlayerTurn));
        iPlay = gameReplay();
    } while (iPlay);
    return EXIT_SUCCESS;
}
