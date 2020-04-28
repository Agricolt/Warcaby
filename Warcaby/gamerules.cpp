#include "gamerules.h"

GameRules::GameRules(gameType gt)
{
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
        board_size = 10;
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

lista::el* GameRules::checkKillsOpportunities(Pawn *selected_pawn, std::vector<std::vector<tileState>>& game_board_state, lista* lista_ruchow)
{
    QPoint pt = selected_pawn->getPosition();
    int x = pt.x(),
        y = pt.y();
    x++;
    y++;
    if (selected_pawn->pawn_state == tileState::BlackPawn)
    {
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen)
            {
                x++;
                y++;
                if (checkCondition(x, y, game_board_state.size()))
                {
                    if(game_board_state[x][y] == tileState::Empty)
                    {
                        game_board_state[x-1][y-1] = tileState::Killed;
                        Pawn *p = new Pawn(selected_pawn->pawn_state);
                        p->setPosition(QPoint(x, y));
                        lista_ruchow->add(checkKillsOpportunities(p, game_board_state, lista_ruchow));
                        lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
        }
        x = pt.x();
        y = pt.y();
        x--;
        y++;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen)
            {
                x--;
                y++;
                if (checkCondition(x, y, game_board_state.size()))
                {
                    if(game_board_state[x][y] == tileState::Empty)
                    {
                        game_board_state[x+1][y-1] = tileState::Killed;
                        Pawn *p = new Pawn(selected_pawn->pawn_state);
                        p->setPosition(QPoint(x, y));
                        lista_ruchow->add(checkKillsOpportunities(p, game_board_state, lista_ruchow));
                        lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
                    }
                     else
                    {
                        return nullptr;
                    }
                }
            }
        }
        x = pt.x();
        y = pt.y();
        x--;
        y--;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen)
            {
                x--;
                y--;
                if (checkCondition(x, y, game_board_state.size()))
                {
                    if(game_board_state[x][y] == tileState::Empty)
                    {
                        game_board_state[x+1][y+1] = tileState::Killed;
                        Pawn *p = new Pawn(selected_pawn->pawn_state);
                        p->setPosition(QPoint(x, y));
                        lista_ruchow->add(checkKillsOpportunities(p, game_board_state, lista_ruchow));
                        lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
        }
        x = pt.x();
        y = pt.y();
        x++;
        y--;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen)
            {
                x++;
                y--;
                if (checkCondition(x, y, game_board_state.size()))
                {
                    if(game_board_state[x][y] == tileState::Empty)
                    {
                        game_board_state[x-1][y+1] = tileState::Killed;
                        Pawn *p = new Pawn(selected_pawn->pawn_state);
                        p->setPosition(QPoint(x, y));
                        lista_ruchow->add(checkKillsOpportunities(p, game_board_state, lista_ruchow));
                        lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
        }
    }

    x = pt.x();
    y = pt.y();
    x++;
    y++;

    if (selected_pawn->pawn_state == tileState::WhitePawn)
    {
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen)
            {
                x++;
                y++;
                if (checkCondition(x, y, game_board_state.size()))
                {
                    if(game_board_state[x][y] == tileState::Empty)
                    {
                        game_board_state[x-1][y-1] = tileState::Killed;
                        Pawn *p = new Pawn(selected_pawn->pawn_state);
                        p->setPosition(QPoint(x, y));
                        lista_ruchow->add(checkKillsOpportunities(p, game_board_state, lista_ruchow));
                        lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
        }
        x = pt.x();
        y = pt.y();
        x--;
        y++;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen)
            {
                x--;
                y++;
                if (checkCondition(x, y, game_board_state.size()))
                {
                    if(game_board_state[x][y] == tileState::Empty)
                    {
                        game_board_state[x+1][y-1] = tileState::Killed;
                        Pawn *p = new Pawn(selected_pawn->pawn_state);
                        p->setPosition(QPoint(x, y));
                        lista_ruchow->add(checkKillsOpportunities(p, game_board_state, lista_ruchow));
                        lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
        }
        x = pt.x();
        y = pt.y();
        x--;
        y--;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen)
            {
                x--;
                y--;
                if (checkCondition(x, y, game_board_state.size()))
                {
                    if(game_board_state[x][y] == tileState::Empty)
                    {
                        game_board_state[x+1][y+1] = tileState::Killed;
                        Pawn *p = new Pawn(selected_pawn->pawn_state);
                        p->setPosition(QPoint(x, y));
                        lista_ruchow->add(checkKillsOpportunities(p, game_board_state, lista_ruchow));
                        lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
        }
        x = pt.x();
        y = pt.y();
        x++;
        y--;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen)
            {
                x++;
                y--;
                if (checkCondition(x, y, game_board_state.size()))
                {
                    if(game_board_state[x][y] == tileState::Empty)
                    {
                        game_board_state[x-1][y+1] = tileState::Killed;
                        Pawn *p = new Pawn(selected_pawn->pawn_state);
                        p->setPosition(QPoint(x, y));
                        lista_ruchow->add(checkKillsOpportunities(p, game_board_state, lista_ruchow));
                        lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
                    }
                    else
                    {
                        return nullptr;
                    }
                }
            }
        }
    }
    return nullptr;
}

void GameRules::checkSurrounding(Pawn *selected_pawn, std::vector<std::vector<tileState> >& game_board_state, lista* lista_ruchow)
{
    int x = selected_pawn->getPosition().x();
    int y = selected_pawn->getPosition().y();
    if (selected_pawn->pawn_state == tileState::WhitePawn)
    {
        x--; y--;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
        }
        x = x + 2;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
        }
    }
    x = selected_pawn->getPosition().x();
    y = selected_pawn->getPosition().y();
    if (selected_pawn->pawn_state == tileState::BlackPawn)
    {
        x++; y++;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
        }

        x = x - 2;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                lista_ruchow->add(selected_pawn->getPosition(), QPoint(x, y));
        }
    }
}

bool GameRules::checkCondition(int x, int y, int board_size)
{
    if (x >= 0 && x < board_size && y >= 0 && y < board_size)
        return true;
    return false;
}


lista *GameRules::giveAllPossibleMoves(Pawn * selected_pawn, std::vector<std::vector<tileState>>& game_board_state)
{
    lista *lista_ruchow = new lista();
    checkKillsOpportunities(selected_pawn, game_board_state, lista_ruchow);
    if (lista_ruchow->isEmpty())
    {
        std::cout << "Nie ma mozliwosci bicia" << std::endl;
        checkSurrounding(selected_pawn, game_board_state, lista_ruchow);
    }
    else
    {
        std::cout << "Wykryto możliwe bicia:" << std::endl;
        lista_ruchow->print();
    }
    return lista_ruchow;
}
