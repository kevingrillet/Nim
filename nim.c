/**
 * \file nim.c
 * \brief NIM Game
 * \author Kévin G.
 * \version 0.2
 * \date 06/12/2017
 */
#include "nim.h"

/**
 * \fn void gameDraw(int iCoins)
 * \brief The function displays the number of coins remaining.
 *
 * \param iCoins int, can't be NULL.
 */
void gameDraw(int iCoins)
{
    int i;
    fprintf(stdout, "--------------------------------------------------\n");
    fprintf(stdout, "There is %d coins\n", iCoins);
    for (i = 0; i < iCoins; i++)
    {
        fprintf(stdout, "|");
    }
    fprintf(stdout, "\n\n");
}

/**
 * \fn void gameMainMenu()
 * \brief The function displays a welcome message and the rules.
 */
void gameMainMenu()
{
    fprintf(stdout, "\tXXX    XX XX XXX     XXX\n");
    fprintf(stdout, "\tXXXX   XX XX XXXX   XXXX\n");
    fprintf(stdout, "\tXX XX  XX XX XX XX XX XX\n");
    fprintf(stdout, "\tXX  XX XX XX XX  XXX  XX\n");
    fprintf(stdout, "\tXX   XXXX XX XX       XX\n");
    fprintf(stdout, "\tXX    XXX XX XX       XX\n");
    fprintf(stdout, "\tXX    XXX XX XX       XX\n\n");
    fprintf(stdout, "RULES OF THE GAME:\n");
    fprintf(stdout, "1. The game start with a number of %d coins\n", SIZE);
    fprintf(stdout, "2. On each turn, players will alternately take between 1 and %d coins from the table\n", MAX_TAKE);
    fprintf(stdout, "3. The player who takes the last coin loses\n\n");
}

/**
 * \fn bool gameAnnounceWinner(int iCoins, int iPlayerTurn)
 * \brief The function is announcing the winner.
 *
 * \param iCoins int, can't be NULL.
 * \param iPlayerTurn int, can't be NULL.
 * \return TRUE (0) if the game is end, FALSE (1) if not.
 */
bool gameAnnounceWinner(int iCoins, int iPlayerTurn)
{
    if (gameIsEnd(iCoins))
    {
        if (iCoins == 0)
        {
            fprintf(stdout, "Game is end, you took the last coin.\n");
            fprintf(stdout, "Player %d win.\n\n", iPlayerTurn == PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE);
            fprintf(stdout, "==================================================\n");
            return TRUE;
        }
        else if (iCoins == 1)
        {
            fprintf(stdout, "Game is end, there is 1 remaining coin.\n");
            fprintf(stdout, "Player %d win.\n\n", iPlayerTurn);
            fprintf(stdout, "==================================================\n");
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * \fn bool gameIsEnd(int iCoins)
 * \brief The function check the end of the game.
 *
 * \param iCoins int, can't be NULL.
 * \return TRUE (0) if the game is end, FALSE (1) if not.
 */
bool gameIsEnd(int iCoins)
{
    return (iCoins == 0 || iCoins == 1);
}

/**
 * \fn bool gameMoveIsLegal(int iCoins, int iTaken)
 * \brief The function checks if the move is legal.
 *
 * \param iCoins int, can't be NULL.
 * \param iTaken int, can't be NULL.
 * \return TRUE (0) if the move is legal, FALSE (1) if not.
 */
bool gameMoveIsLegal(int iCoins, int iTaken)
{
    return ((iTaken >= MIN_TAKE) && (iTaken <= MAX_TAKE) && (iTaken <= iCoins));
}

/**
 * \fn bool gameReplay()
 * \brief The function asks if the player wants to replay.
 *
 * \return TRUE (0) if the player wants to replay, FALSE (1) if not.
 */
bool gameReplay()
{
    int iReplay = DEFAULT_VALUE;
    fprintf(stdout, "Select replay option:\n");
    fprintf(stdout, "1. Exit\n");
    fprintf(stdout, "2. Replay\n");
    fprintf(stdout, "Enter option: ");
    fscanf(stdin, "%d", &iReplay);
    while (iReplay != EXIT && iReplay != REPLAY)
    {
        fseek(stdin, 0, SEEK_END);
        fprintf(stdout, "Option invalid.\n");
        fprintf(stdout, "Enter option: ");
        fscanf(stdin, "%d", &iReplay);
    }
    fprintf(stdout, "\n\n");
    return (iReplay == 2);
}

/**
 * \fn int gameFindGoodMove(int iCoins)
 * \brief The function returns a good move.
 *
 * \param iCoins int, can't be NULL.
 * \return int.
 */
int gameFindGoodMove(int iCoins)
{
    int iMin = MIN_TAKE;
    int iMax = MAX_TAKE;
    srand(time(NULL));
    if (iCoins > MAX_TAKE)
    {
        return (iCoins % (MAX_TAKE + 1) != 0) ? iCoins % (MAX_TAKE + 1) : rand() % (iMax - iMin) + iMin;
    }
    return iCoins - 1;
}

/**
 * \fn int gameFlipTheCoin()
 * \brief The function returns who will start.
 *
 * \return int, PLAYER_ONE (1) or PLAYER_TWO (2).
 */
int gameFlipTheCoin()
{
    int iMin = 1;
    int iMax = PLAYER_NUMBER;
    srand(time(NULL));
    return rand() % (iMax - iMin) + iMin;
}

/**
 * \fn int gameTake(int iCoins, int iTaken)
 * \brief The function that removes coins.
 *
 * \param iCoins int, can't be NULL.
 * \param iTaken int, can't be NULL.
 * \return int, number of remaining coins.
 */
int gameTake(int iCoins, int iTaken)
{
    if (gameMoveIsLegal(iCoins, iTaken))
    {
        return iCoins -= iTaken;
    }
    else
    {
        return iCoins;
    }
}

/**
 * \fn int gameTurn(int iGameMode, int iPlayerTurn, int iCoins)
 * \brief The function of a turn, if it's player turn, he will choose a number of coins.
 *
 * \param iGameMode int, can't be NULL.
 * \param iPlayerTurn int, can't be NULL.
 * \param iCoins int, can't be NULL.
 * \return int, ONE_PLAYER (1) or TWO_PLAYERS (2).
 */
int gameTurn(int iGameMode, int iPlayerTurn, int iCoins)
{
    int iTaken = DEFAULT_VALUE;
    if (iGameMode == ONE_PLAYER && iPlayerTurn == PLAYER_TWO)
    {
        fprintf(stdout, "Computer turn\n\n");
        return gameFindGoodMove(iCoins);
    }
    else
    {
        fprintf(stdout, "Player %d turn\n", iPlayerTurn);
        fprintf(stdout, "Choose how man coins you want to take (1-%d): ", MAX_TAKE);
        scanf("%d", &iTaken);
        while (!gameMoveIsLegal(iCoins, iTaken))
        {
            fseek(stdin, 0, SEEK_END);
            fprintf(stdout, "Option invalid\n");
            fprintf(stdout, "Enter option: ");
            fscanf(stdin, "%d", &iTaken);
        }
        fprintf(stdout, "\n");
        return iTaken;
    }
}

/**
 * \fn int gameTypeMenu()
 * \brief The function asks if the player wants to play against computer or another player.
 *
 * \return int, ONE_PLAYER (1) or TWO_PLAYERS (2).
 */
int gameTypeMenu()
{
    int iGameMode = DEFAULT_VALUE;
    fprintf(stdout, "Please select the number of players:\n");
    fprintf(stdout, "1. One player\n");
    fprintf(stdout, "2. Two players\n");
    fprintf(stdout, "Enter option: ");
    fscanf(stdin, "%d", &iGameMode);
    while (iGameMode != ONE_PLAYER && iGameMode != TWO_PLAYERS)
    {
        fseek(stdin, 0, SEEK_END);
        fprintf(stdout, "Option invalid\n");
        fprintf(stdout, "Enter option: ");
        fscanf(stdin, "%d", &iGameMode);
    }
    fprintf(stdout, "\n\n");
    return iGameMode;
}
