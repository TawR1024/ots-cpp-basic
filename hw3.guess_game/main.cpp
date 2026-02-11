#include <cstring>  // for string comparation;
#include <iostream>

#include "gues_game/game.hpp"

inline constexpr const char* TABLE_CMD   = "-table";
inline constexpr const char* MAX_VALUE   = "-max";
const int                    DEFAULT_MAX = 100;

int main (int argc, char* argv[])
{
    int max_value = DEFAULT_MAX;

    // game::init_winners_table();

    if (argc >= 2)
    {
        if (std::strcmp (argv[1], TABLE_CMD) == 0)
        {
            if (game::validate_top_table_exist(false)) {
                game::print_winners ();
            }else {
                std::cout << "winners table does not exist" << std::endl;
            }
         
            return 0;
        }
        else if (std::strcmp (argv[1], MAX_VALUE) == 0)
        {
            if (argc > 2)
            {  // validate that 3rd arg was provided
                int user_max = std::atoi (argv[2]);
                if (user_max <= 0)
                {
                    std::cout << "max value out of range, using default " << DEFAULT_MAX;
                }
                max_value = std::atoi (argv[2]);
            }
            else
            {
                std::cout << "invalid value, will use default " << DEFAULT_MAX << std::endl;
            }
        }
        else
        {
            std::cout << "unknown arg " << argv[1];
            return -2;
        }
    }

    // start the game
    std::string user_name = game::init_user ();
    int         attempts  = game::guess_game (max_value);

    if(!game::validate_top_table_exist(true)) {
        std::cout << "winners table file corrupted"<< std::endl;
        std::cout << "result will not recoded"<< std::endl;
        return -1;
    }
    game::write_new_winner (user_name, attempts);
    game::print_winners ();

    return 0;
}