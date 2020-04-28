#ifndef GAMERULES_H
#define GAMERULES_H

#include <vector>
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

    //Zwraca true jesli jest mozliwe jakiekolwiek bicie
    lista::el* checkKillsOpportunities(Pawn *selected_pawn, std::vector<std::vector<tileState>>& game_board_state, lista* lista_ruchow);
    void checkSurrounding(Pawn *selected_pawn, std::vector<std::vector<tileState>>& game_board_state, lista* lista_ruchow);
    bool checkCondition(int x, int y, int board_size);

public:
    GameRules(gameType gt);
    lista * giveAllPossibleMoves(Pawn * selected_pawn, std::vector<std::vector<tileState>>& game_board_state);
};

#endif // GAMERULES_H
