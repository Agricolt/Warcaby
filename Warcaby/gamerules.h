#ifndef GAMERULES_H
#define GAMERULES_H

#include <vector>
#include <iterator>
#include "CONSTANTS_ENUMS.h"
#include "lista.h"
#include "pawn.h"
#include "boardtile.h"

class GameRules
{
public:
    int board_size;
    bool whiteFirstMove, //used
    canKillBackwards, //used
    canKillMoreThanOnce, //can be used
    areKillsObligatory;  //TODO

    //Głowna funkcja - sprawdza czy ruch wyslany przez silnik moze zostac wykonany
    bool isFineMove(Pawn * selected_pawn, boardTile * selected_board_tile, const std::vector<std::vector<tileState>>& game_board_state
                    , const std::vector<Pawn*>& player_1_pawns, const std::vector<Pawn*>& player_2_pawns, bool whiteMove);
    //Wybiera pionki ktore moga sie ruszyc badz zbic innego pionka. W przypadku gdy sa pionki ktore moga bic, pionki ktore sie moga ruszyc sa nieistotne
    void selectPawnsAbleToMove(std::vector <Pawn*> &pawns_able_to_move, std::vector <Pawn*> &pawns_able_to_kill, bool whiteMove, const std::vector<Pawn*>& player_1_pawns
                               , const std::vector<Pawn*>& player_2_pawns, const std::vector<std::vector<tileState>>& game_board_state);
    /*Sprawdza otoczenie pionka (najpierw sprawdza czy sa wolne pola a nastepnie czy sa przeciwnicy i jesli sa to sprawdza czy mozna ich zbic
    0 - pionek nie moze sie ruszyc ani bic, 1 -  pionek moze sie ruszyc bez bicia 2 - pionek moze zbic przeciwnika*/
    int checkSurrounding(Pawn *selected_pawn, const std::vector<std::vector<tileState>>& game_board_state);
    //Pobiera ruch a nastepnie sprawdza czy dany pionek moze sie poruszyc w wybranym kierunku
    bool findMoveInNonKillMoves(lista::el* el, Pawn* selected_pawn, const std::vector<std::vector<tileState>>& game_board_state);
    //Pobiera ruch a nastepnie sprawdza czy dany pionek moze wykonac dane bicie
    bool findMoveInKillMoves(lista::el* el, Pawn* selected_pawn, const std::vector<std::vector<tileState>>& game_board_state);
    //Zwraca true jesli jest mozliwe jakiekolwiek bicie wokol pionka
    bool checkKillsOpportunities(Pawn *selected_pawn, std::vector<std::vector<tileState>>& game_board_state);
    //Sprawdza czy nie wychodzimy poza tablice - zapobiega błędom krytycznym
    bool checkCondition(int x, int y, int board_size);
    GameRules(gameType gt);
};

#endif // GAMERULES_H
