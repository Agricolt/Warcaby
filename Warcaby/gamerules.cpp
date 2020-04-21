#include "gamerules.h"

GameRules::GameRules(gameType gt)
{
    lista_ruchow = new class lista();
    whiteFirstMove = true;
    board_size = 8;
    canMoveBackwards = false;
    canMoveForward = true;
    canKillBackwards = true;
    canKillMoreThanOnce = true;
    areKillsObligatory = true;
    isTheBestKillObligatory = true;
    canKillAfterBecQueen = false;
    isKillObligatoryAfterMovingToLastRow = true;
    canQueensMoveFurther = true;
    canJumpMoreThanOnce = false;
    canQueenJumpAfterKillAnywhere = true;
    if (gt == gameType::International_Polish)
    {
        board_size = 8;
    }
    else if(gt == gameType::English)
    {
        whiteFirstMove = false;
        canKillBackwards = false;
        canQueensMoveFurther = false;
        canQueenJumpAfterKillAnywhere = false;
        isTheBestKillObligatory = false;
    }
}

bool GameRules::checkCondition(int x, int y)
{
    if (x < 0 || x >= board_size || y < 0 || y >= board_size)
        return false;
    return true;
}

bool GameRules::checkKillsOpportunities(Pawn *selected_pawn, tileState **game_board_state)
{
    QPoint pt = selected_pawn->getPosition();
    int x = pt.x();
    int y = pt.y();

    x--; y--;
    if (checkCondition(x, y))
    {
        if (selected_pawn->pawn_state == tileState::WhitePawn) //sprawdz 2 na dole
        {
            if (game_board_state[x][y] == tileState::BlackPawn)
            {

            }
        }
    }
}


lista *GameRules::giveAllPossibleMoves(Pawn * selected_pawn, tileState **game_board_state)
{
    bool f = checkKillsOpportunities(selected_pawn, game_board_state); //sprawdz czy są możliwe jakieś bicia
    if (lista_ruchow->isEmpty()) //oznacza to że nie ma żadnych możliwych bić
    {

    }
    /*
    //Tworze dwie zmienne i od razu przypisuje je do pierwszego warunku
    QPoint pt = selected_pawn->getPosition();
    int x = pt.x() - 1;
    int y = pt.y() - 1;
    if (selected_pawn->type == pawnType::Normal)//sprawdz tylko 8 miejsc (te obok pionka) lub te za miejscem obok pionka
    {
        if (checkCondition(x, y) == true)
        {
            if (game_board_state[x][y] == tileState::Empty)
            {
                ls->add(pt, QPoint(x, y));
            }
        }
        x += 2;
        if (checkCondition(x, y) == true)
        {
            if (game_board_state[x][y] == tileState::Empty)
            {
                ls->add(pt, QPoint(x, y));
            }
        }
        y += 2;
        if (checkCondition(x, y) == true)
        {
            if (game_board_state[x][y] == tileState::Empty)
            {
                ls->add(pt, QPoint(x, y));
            }
        }
        x -= 2;
        if(checkCondition(x, y) == true)
        {
            if (game_board_state[x][y] == tileState::Empty)
            {
                ls->add(pt, QPoint(x, y));
            }
        }
    }
    else    //jesli pionek jest damka sprawdz cala plansze w 4 kierunkach
    {

    }
    */
}
