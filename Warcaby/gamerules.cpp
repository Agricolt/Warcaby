#include "gamerules.h"

GameRules::GameRules(gameType gt)
{
    whiteFirstMove = true;
    board_size = 8;
    canKillBackwards = true;
    canKillMoreThanOnce = true;
    areKillsObligatory = true;
    if (gt == gameType::International_Polish)
    {
        board_size = 10;
    }
    else if(gt == gameType::English)
    {
        whiteFirstMove = false;
        canKillBackwards = false;
    }
}

//0 - ruch nie moze zostac wykonany
//1 - ruch moze zostac wykoanny z biciem
//2 - ruch moze zostac wykonany bez bicia
int GameRules::isFineMove(Pawn * selected_pawn, boardTile * selected_board_tile, const std::vector<std::vector<tileState>>& game_board_state
                           , const std::vector<Pawn*>& player_1_pawns, const std::vector<Pawn*>& player_2_pawns, bool whiteMove)
{
    std::vector<Pawn*> pawns_able_to_move;
    std::vector<Pawn*> pawns_able_to_kill;
    selectPawnsAbleToMove(pawns_able_to_move, pawns_able_to_kill, whiteMove, player_1_pawns, player_2_pawns, game_board_state);
    if (pawns_able_to_kill.empty() == true)
    {
        for (unsigned int i = 0; i < pawns_able_to_move.size(); i++)
        {
            if (pawns_able_to_move[i] == selected_pawn)
            {
                lista::el * el = new lista::el(selected_pawn->getPosition(), selected_board_tile->getPosition());
                bool a = findMoveInNonKillMoves(el, selected_pawn, game_board_state);
                delete el;
                if (a)
                    return 2;
                else
                    return 0;
            }
        }
    }
    else // if ((pawns_able_to_kill.empty() == false)
         // to znaczy że pionki ktore moga sie ruszyc nie maja pierwszenstwa
    {
        for (unsigned int i = 0; i < pawns_able_to_kill.size(); i++)
        {
            if (pawns_able_to_kill[i] == selected_pawn) //ruszany pionek znajduje sie w liscie pionkow ktore maja okazje bicia
            {
                lista::el * el = new lista::el(selected_pawn->getPosition(), selected_board_tile->getPosition());
                bool a = findMoveInKillMoves(el, selected_pawn, game_board_state);
                delete el;
                if (a)
                    return 1;
                else
                    return 0;
            }
        }
    }
    return false;
}

void GameRules::selectPawnsAbleToMove(std::vector <Pawn*> &pawns_able_to_move, std::vector <Pawn*> &pawns_able_to_kill, bool whiteMove, const std::vector<Pawn*>& player_1_pawns, const std::vector<Pawn*>& player_2_pawns
                                      , const std::vector<std::vector<tileState>>& game_board_state)
{
    if (whiteMove == true) //teraz ruch bialych wiec bedziemy szukac wsrod bialych pionkow
    {
        for (std::vector<Pawn*>::const_iterator i = player_1_pawns.begin(); i != player_1_pawns.end(); i++)
        {
            int wynik = checkSurrounding(*i, game_board_state);
            if (wynik == 1) //jesli pionek moze sie ruszyc to
                pawns_able_to_move.push_back(*i);
            else if (wynik == 2)
                pawns_able_to_kill.push_back(*i);
        }
    }
    else    //wsrod czarnych
    {
        for (std::vector<Pawn*>::const_iterator i = player_2_pawns.begin(); i != player_2_pawns.end(); i++)
        {
            int wynik = checkSurrounding(*i, game_board_state);
            if (wynik == 1) //jesli pionek moze sie ruszyc to
                pawns_able_to_move.push_back(*i);
            else if (wynik == 2)
                pawns_able_to_kill.push_back(*i);
        }
    }
}

int GameRules::checkSurrounding(Pawn *selected_pawn, const std::vector<std::vector<tileState>>& game_board_state)
{
    int possibilities = 0;
    int x = selected_pawn->getPosition().x();
    int y = selected_pawn->getPosition().y();
    if (selected_pawn->pawn_state == tileState::WhitePawn)
    {
        x--; y--;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                possibilities = 1;
            if (checkCondition(x-1, y-1, game_board_state.size()))
            {
                if ((game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen) && game_board_state[x-1][y-1] == tileState::Empty)
                    if (game_board_state[x-1][y-1] == tileState::Empty)
                    possibilities = 2;
            }
        }
        x = x + 2;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                if (possibilities == 0)
                    possibilities = 1;
            if (checkCondition(x+1, y-1, game_board_state.size()))
            {
                if ((game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen) && game_board_state[x+1][y-1] == tileState::Empty)
                    possibilities = 2;
            }
        }
        if (this->canKillBackwards == true)
        {
            y = y + 2;
            if (checkCondition(x, y, game_board_state.size()))
            {
                if (checkCondition(x+1, y+1, game_board_state.size()))
                {
                    if ((game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen) && game_board_state[x+1][y+1] == tileState::Empty)
                        possibilities = 2;
                }
            }
            x -= 2;
            if (checkCondition(x, y, game_board_state.size()))
            {
                if (checkCondition(x-1, y+1, game_board_state.size()))
                {
                    if ((game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen) && game_board_state[x-1][y+1] == tileState::Empty)
                    possibilities = 2;
                }
            }
        }
    }
    x = selected_pawn->getPosition().x();
    y = selected_pawn->getPosition().y();
    //********************************FOR QUEENS*********************************
    if (selected_pawn->pawn_state == tileState::WhiteQueen || selected_pawn->pawn_state == tileState::BlackQueen)
    {
        tileState colour_to_kill1, colour_to_kill12;
        if (selected_pawn->pawn_state == tileState::WhiteQueen)
        {
            colour_to_kill1 = tileState::BlackPawn;
            colour_to_kill12 = tileState::BlackQueen;
        }
        else
        {
            colour_to_kill1 = tileState::WhitePawn;
            colour_to_kill12 = tileState::WhiteQueen;
        }
        //skos prawo dol
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i++, j++)
        {
            if (checkCondition(i, j, board_size))
            {
                if (game_board_state[i][j] == tileState::Empty)
                    if (possibilities == 0)
                        possibilities = 1;
            }
            if (checkCondition(i+1, j+1, game_board_state.size()))
            {
                if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                {
                    for (int i2 = i + 1, j2 = j + 1; checkCondition(i2, j2, board_size) == true; i2++, j2++)
                    {
                        if (game_board_state[i2][j2] == tileState::Empty)
                                    possibilities = 2;
                    }
                }
            }
        }
        //skos lewo dol
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i--, j++)
        {
            if (checkCondition(i, j, board_size))
            {
                if (game_board_state[i][j] == tileState::Empty)
                    if (possibilities == 0)
                        possibilities = 1;
            }
            if (checkCondition(i-1, j+1, game_board_state.size()))
            {
                if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                {
                    for (int i2 = i - 1, j2 = j + 1; checkCondition(i2, j2, board_size) == true; i2--, j2++)
                    {
                        if (game_board_state[i2][j2] == tileState::Empty)
                                    possibilities = 2;
                    }
                }
            }
        }
        //skos prawo gora
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i++, j--)
        {
            if (checkCondition(i, j, board_size))
            {
                if (game_board_state[i][j] == tileState::Empty)
                    if (possibilities == 0)
                        possibilities = 1;
            }
            if (checkCondition(i+1, j-1, game_board_state.size()))
            {
                if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                {
                    for (int i2 = i + 1, j2 = j - 1; checkCondition(i2, j2, board_size) == true; i2++, j2--)
                    {
                        if (game_board_state[i2][j2] == tileState::Empty)
                                    possibilities = 2;
                    }
                }
            }
        }
        //skos lewo gora
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i--, j--)
        {
            if (checkCondition(i, j, board_size))
            {
                 if (game_board_state[i][j] == tileState::Empty)
                     if (possibilities == 0)
                         possibilities = 1;
            }
            if (checkCondition(i-1, j-1, game_board_state.size()))
            {
                if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                {
                    for (int i2 = i - 1, j2 = j - 1; checkCondition(i2, j2, board_size) == true; i2--, j2--)
                    {
                        if (game_board_state[i2][j2] == tileState::Empty)
                                   possibilities = 2;
                    }
                }
            }
        }
    }
    //********************************FOR QUEENS********************************
    //**********************************END*************************************
    x = selected_pawn->getPosition().x();
    y = selected_pawn->getPosition().y();
    if (selected_pawn->pawn_state == tileState::BlackPawn)
    {
        x++; y++;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                possibilities = 1;
            if (checkCondition(x+1, y+1, game_board_state.size()))
            {
                if ((game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen) && game_board_state[x+1][y+1] == tileState::Empty)
                    possibilities = 2;
            }
        }

        x = x - 2;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                if (possibilities == 0)
                    possibilities = 1;
            if (checkCondition(x-1, y+1, game_board_state.size()))
            {
                if ((game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen) && game_board_state[x-1][y+1] == tileState::Empty)
                    possibilities = 2;
            }
        }
        if (this->canKillBackwards == true)
        {
            y = y - 2;
            if (checkCondition(x, y, game_board_state.size()))
            {
                if (checkCondition(x-1, y-1, game_board_state.size()))
                {
                    if ((game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen) && game_board_state[x-1][y-1] == tileState::Empty)
                        possibilities = 2;
                }
            }
            x += 2;
            if (checkCondition(x, y, game_board_state.size()))
            {
                if (checkCondition(x+1, y-1, game_board_state.size()))
                {
                    if ((game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen) && game_board_state[x+1][y-1] == tileState::Empty)
                    possibilities = 2;
                }
            }
        }
    }
    return possibilities;
}

bool GameRules::findMoveInNonKillMoves(lista::el *el, Pawn* selected_pawn, const std::vector<std::vector<tileState>>& game_board_state)
{
    lista * lista = new class lista();
    if (selected_pawn->pawn_state == tileState::WhitePawn)
    {
        QPoint pt = selected_pawn->getPosition();
        int x = pt.x(),
            y = pt.y();
        x--;
        y--;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                lista->add(pt, QPoint(x, y));
        }
        x = x + 2;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                lista->add(pt, QPoint(x, y));
        }
    }
    else if (selected_pawn->pawn_state == tileState::BlackPawn)
    {
        QPoint pt = selected_pawn->getPosition();
        int x = pt.x(),
            y = pt.y();
        x++;
        y++;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                lista->add(pt, QPoint(x, y));
        }
        x = x - 2;
        if (checkCondition(x, y, game_board_state.size()))
        {
            if (game_board_state[x][y] == tileState::Empty)
                lista->add(pt, QPoint(x, y));
        }
    } //*********************FOR QUEENS*********************************
    else if (selected_pawn->pawn_state == tileState::BlackQueen || selected_pawn->pawn_state == tileState::WhiteQueen)
    {
        QPoint pt = selected_pawn->getPosition();
        //skos prawo dol
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i++, j++)
        {
            if (game_board_state[i][j] == tileState::Empty)
                lista->add(pt, QPoint(i, j));
        }
        //skos lewo dol
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i--, j++)
        {
            if (game_board_state[i][j] == tileState::Empty)
                lista->add(pt, QPoint(i, j));
        }
        //skos prawo gora
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i++, j--)
        {
            if (game_board_state[i][j] == tileState::Empty)
                lista->add(pt, QPoint(i, j));
        }
        //skos lewo gora
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i--, j--)
        {
            if (game_board_state[i][j] == tileState::Empty)
                lista->add(pt, QPoint(i, j));
        }
    }
    //*********************FOR QUEENS*********************************
    //************************END*************************************
    return lista->find(el->from, el->where);
}

bool GameRules::findMoveInKillMoves(lista::el *el, Pawn *selected_pawn, const std::vector<std::vector<tileState> > &game_board_state)
{
    lista * lista = new class lista();
    if (selected_pawn->pawn_state == tileState::WhitePawn)
    {
        QPoint pt = selected_pawn->getPosition();
        int x = pt.x(),
            y = pt.y();
        x--;
        y--;
        if (checkCondition(x, y, game_board_state.size()) && checkCondition(x-1, y-1, game_board_state.size()))
        {
            if ((game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen) && game_board_state[x-1][y-1] == tileState::Empty)
                lista->add(pt, QPoint(x-1, y-1));
        }
        x = x + 2;
        if (checkCondition(x, y, game_board_state.size()) && checkCondition(x+1, y-1, game_board_state.size()))
        {
            if ((game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen) && game_board_state[x+1][y-1] == tileState::Empty)
                lista->add(pt, QPoint(x+1, y-1));
        }
        if (this->canKillBackwards == true)
        {
            y += 2;
            if (checkCondition(x, y, game_board_state.size()))
            {
                if (checkCondition(x+1, y+1, game_board_state.size()))
                {
                    if ((game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen) && game_board_state[x+1][y+1] == tileState::Empty)
                    {
                        lista->add(pt, QPoint(x+1, y+1));
                    }
                }
            }
            x -= 2;
            if (checkCondition(x, y, game_board_state.size()))
            {
                if (checkCondition(x-1, y+1, game_board_state.size()))
                {
                    if ((game_board_state[x][y] == tileState::BlackPawn || game_board_state[x][y] == tileState::BlackQueen) && game_board_state[x-1][y+1] == tileState::Empty)
                        lista->add(pt, QPoint(x-1, y+1));
                }
            }
        }
    }
    else if (selected_pawn->pawn_state == tileState::BlackPawn)
    {
        QPoint pt = selected_pawn->getPosition();
        int x = pt.x(),
            y = pt.y();
        x++;
        y++;
        if (checkCondition(x, y, game_board_state.size()) && checkCondition(x+1, y+1, game_board_state.size()))
        {
            if ((game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen) && game_board_state[x+1][y+1] == tileState::Empty)
                lista->add(pt, QPoint(x+1, y+1));
        }
        x = x - 2;
        if (checkCondition(x, y, game_board_state.size()) && checkCondition(x-1, y+1, game_board_state.size()))
        {
            if ((game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen) && game_board_state[x-1][y+1] == tileState::Empty)
                lista->add(pt, QPoint(x-1, y+1));
        }
        if (this->canKillBackwards == true)
        {
            y = y - 2;
            if (checkCondition(x, y, game_board_state.size()))
            {
                if (checkCondition(x-1, y-1, game_board_state.size()))
                {
                    if ((game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen) && game_board_state[x-1][y-1] == tileState::Empty)
                        lista->add(pt, QPoint(x-1, y-1));
                }
            }
            x += 2;
            if (checkCondition(x, y, game_board_state.size()))
            {
                if (checkCondition(x+1, y-1, game_board_state.size()))
                {
                    if ((game_board_state[x][y] == tileState::WhitePawn || game_board_state[x][y] == tileState::WhiteQueen) && game_board_state[x+1][y-1] == tileState::Empty)
                        lista->add(pt, QPoint(x+1, y-1));
                }
            }
        }
    } //****************************FOR QUEENS**********************************
    else if (selected_pawn->pawn_state == tileState::BlackQueen || selected_pawn->pawn_state == tileState::WhiteQueen)
    {
        QPoint pt = selected_pawn->getPosition();
        tileState colour_to_kill1, colour_to_kill12;
        if (selected_pawn->pawn_state == tileState::WhiteQueen)
        {
            colour_to_kill1 = tileState::BlackPawn;
            colour_to_kill12 = tileState::BlackQueen;
        }
        else
        {
            colour_to_kill1 = tileState::WhitePawn;
            colour_to_kill12 = tileState::WhiteQueen;
        }
        //skos prawo dol
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i++, j++)
        {
            if (checkCondition(i+1, j+1, game_board_state.size()))
            {
                if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                {
                    for (int i2 = i + 1, j2 = j + 1; checkCondition(i2, j2, board_size) == true; i2++, j2++)
                    {
                        if (game_board_state[i2][j2] == tileState::Empty)
                                    lista->add(pt, QPoint(i2, j2));
                    }
                }
            }
        }
        //skos lewo dol
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i--, j++)
        {
            if (checkCondition(i-1, j+1, game_board_state.size()))
            {
                if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                {
                    for (int i2 = i - 1, j2 = j + 1; checkCondition(i2, j2, board_size) == true; i2--, j2++)
                    {
                        if (game_board_state[i2][j2] == tileState::Empty)
                                    lista->add(pt, QPoint(i2, j2));
                    }
                }
            }
        }
        //skos prawo gora
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i++, j--)
        {
            if (checkCondition(i+1, j-1, game_board_state.size()))
            {
                if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                {
                    for (int i2 = i + 1, j2 = j - 1; checkCondition(i2, j2, board_size) == true; i2++, j2--)
                    {
                        if (game_board_state[i2][j2] == tileState::Empty)
                                    lista->add(pt, QPoint(i2, j2));
                    }
                }
            }
        }
        //skos lewo gora
        for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i--, j--)
        {
            if (checkCondition(i-1, j-1, game_board_state.size()))
            {
                if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                {
                    for (int i2 = i - 1, j2 = j - 1; checkCondition(i2, j2, board_size) == true; i2--, j2--)
                    {
                        if (game_board_state[i2][j2] == tileState::Empty)
                                    lista->add(pt, QPoint(i2, j2));
                    }
                }
            }
        }
    }
    //****************************FOR QUEENS**********************************
    //*******************************END**************************************
    return lista->find(el->from, el->where);
}

bool GameRules::checkKillsOpportunities(Pawn *selected_pawn, std::vector<std::vector<tileState>>& game_board_state)
{
    bool canKill = false;
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
                        canKill = true;
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
                        canKill = true;
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
                        canKill = true;
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
                        canKill = true;
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
                        canKill = true;
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
                        canKill = true;
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
                        canKill = true;
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
                        canKill = true;
                    }
                }
            }
        }
    }
    //****************************FOR QUEENS**********************************
        if (selected_pawn->pawn_state == tileState::BlackQueen || selected_pawn->pawn_state == tileState::WhiteQueen)
        {
            tileState colour_to_kill1, colour_to_kill12;
            if (selected_pawn->pawn_state == tileState::WhiteQueen)
            {
                colour_to_kill1 = tileState::BlackPawn;
                colour_to_kill12 = tileState::BlackQueen;
            }
            else
            {
                colour_to_kill1 = tileState::WhitePawn;
                colour_to_kill12 = tileState::WhiteQueen;
            }
            //skos prawo dol
            for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i++, j++)
            {
                if (checkCondition(i+1, j+1, game_board_state.size()))
                {
                    if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                    {
                        for (int i2 = i + 1, j2 = j + 1; checkCondition(i2, j2, board_size) == true; i2++, j2++)
                        {
                            if (game_board_state[i2][j2] == tileState::Empty)
                                            canKill = true;
                        }
                    }
                }
            }
            //skos lewo dol
            for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i--, j++)
            {
                if (checkCondition(i-1, j+1, game_board_state.size()))
                {
                    if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                    {
                        for (int i2 = i - 1, j2 = j + 1; checkCondition(i2, j2, board_size) == true; i2--, j2++)
                        {
                            if (game_board_state[i2][j2] == tileState::Empty)
                                            canKill = true;
                        }
                    }
                }
            }
            //skos prawo gora
            for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i++, j--)
            {
                if (checkCondition(i+1, j-1, game_board_state.size()))
                {
                    if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                    {
                        for (int i2 = i + 1, j2 = j - 1; checkCondition(i2, j2, board_size) == true; i2++, j2--)
                        {
                            if (game_board_state[i2][j2] == tileState::Empty)
                                            canKill = true;
                        }
                    }
                }
            }
            //skos lewo gora
            for (int i = selected_pawn->getPosition().x(), j = selected_pawn->getPosition().y(); checkCondition(i, j, board_size) == true; i--, j--)
            {
                if (checkCondition(i-1, j-1, game_board_state.size()))
                {
                    if ((game_board_state[i][j] == colour_to_kill1 || game_board_state[i][j] == colour_to_kill12))
                    {
                        for (int i2 = i - 1, j2 = j - 1; checkCondition(i2, j2, board_size) == true; i2--, j2--)
                        {
                            if (game_board_state[i2][j2] == tileState::Empty)
                                            canKill = true;
                        }
                    }
                }
            }
        }
        //****************************FOR QUEENS**********************************
        //*******************************END**************************************
    return canKill;
}

bool GameRules::checkCondition(int x, int y, int board_size)
{
    if (x >= 0 && x < board_size && y >= 0 && y < board_size)
        return true;
    return false;
}

