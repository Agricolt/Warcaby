#ifndef GAMERULES_H
#define GAMERULES_H

#include "CONSTANTS_ENUMS.h"
#include "lista.h"
#include "pawn.h"

class GameRules
{
    int board_size;
    bool whiteFirstMove,
    canMoveBackwards,
    canMoveForward,
    canKillForward,
    canKillBackwards,
    canKillMoreThanOnce,
    areKillsObligatory,
    isTheBestKillObligatory,
    canKillAfterBecQueen,
    isKillObligatoryAfterMovingToLastRow,
    canQueensMoveFurther,
    canJumpMoreThanOnce,
    canQueenJumpAfterKillAnywhere;

    lista *lista_ruchow;

    bool checkKillsOpportunities(Pawn *selected_pawn, tileState** game_board_state);
    bool checkCondition(int x, int y);

public:
    GameRules(gameType gt);
    lista * giveAllPossibleMoves(Pawn * selected_pawn, tileState **game_board_state);
};

#endif // GAMERULES_H
