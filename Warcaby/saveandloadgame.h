#ifndef SAVEANDLOADGAME_H
#define SAVEANDLOADGAME_H

#include "CONSTANTS_ENUMS.h"

#include <exceptions.h>
#include <fstream>
#include <iostream>
#include <vector>

class saveAndLoadGame
{
public:
    void saveTheGame(std::string player_name, const std::vector<std::vector<tileState>>& game_board_state);
    std::string loadTheGame(std::string player_name);
};

#endif // SAVEANDLOADGAME_H
