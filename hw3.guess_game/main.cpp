#include "gues_game/game.hpp"
#include <iostream>

int main ()
{   
    if(!game::init_winner_table()) {
        std::cout << "failed to open winners DB";
        return -1;
    }
    game::guess_game ();

    return 0;
}