#include "saveandloadgame.h"

void saveAndLoadGame::saveTheGame(std::string player_name, const std::vector<std::vector<tileState>>& game_board_state)
{
    std::fstream file;
    std::ofstream file2;
    std::string file_name = player_name + "_save.txt";
    file2.open(file_name);
    file2.close();
    file.open(file_name, std::ios::out | std::ios::app);
    if (file.good() == true)
    {
        for (unsigned int j = 0; j < game_board_state.size(); j++)
        {
            for (unsigned int i = 0; i < game_board_state.size(); i++)
            {
                file << (int)game_board_state[i][j];
            }
        }
        file.close();
    }
    else
        throw fileSaveError();
}

std::string saveAndLoadGame::loadTheGame(std::string player_name)
{
    std::fstream file;
    std::string file_name = player_name + "_save.txt";
    std::string return_string;
    file.open(file_name, std::ios::in);
    if (file.good() == true)
    {
        std::getline(file, return_string);
        file.close();
        return return_string;
    }
    else
        throw fileLoadError();
}
