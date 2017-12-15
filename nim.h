/**
 * \file nim.h
 * \brief NIM Game
 * \author Kévin G.
 * \version 0.1
 * \date 23/11/2017
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define MAX_TAKE 3
#define MIN_TAKE 1
#define DEFAULT_VALUE -1
#define ONE_PLAYER 1
#define TWO_PLAYERS 2
#define PLAYER_NUMBER 2
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define EXIT 1
#define REPLAY 2

/*#include <stdbool.h>*/
typedef enum {
    FALSE,
    TRUE
} bool;

void gameDraw(int iCoins);
void gameMainMenu();

bool gameAnnounceWinner(int iCoins, int iPlayerTurn);
bool gameIsEnd(int iCoins);
bool gameMoveIsLegal(int iCoins, int iTaken);
bool gameReplay();

int gameFindGoodMove(int iCoins);
int gameFlipTheCoin();
int gameTake(int iCoins, int iTaken);
int gameTurn(int iGameMode, int iPlayerTurn, int iCoins);
int gameTypeMenu();
