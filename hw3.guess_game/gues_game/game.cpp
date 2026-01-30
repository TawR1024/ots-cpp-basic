#include <iostream>
#include <random>
#include <fstream>
#include "game.hpp"
namespace game
{
int generate_random_number (int min, int max)
{
    std::random_device              rd;
    std::mt19937                    gen (rd ());
    std::uniform_int_distribution<> dis (min, max);

    return dis (gen);
}

bool init_winner_table() {
    std::ofstream winners(WINNER_TABLE_F);

    return winners.is_open();
}

void guess_game ()
{
    std::cout << "Let's the game begin!" << std::endl;

    // prepare random num
    int hidden_number = generate_random_number (1, 100);
    int user_choice, attempts = 0;
    while (true)
    {
        std::cout << "Enter your nuber: ";
        std::cin >> user_choice;

        attempts++;

        if (user_choice == hidden_number)
        {
            std::cout << "you win! attempts = " << attempts << std::endl;
            break;
        }
        else if (user_choice < hidden_number)
        {
            std::cout << "greater than " << user_choice << std::endl;
        }
        else
        {
            std::cout << "less than " << user_choice << std::endl;
        }
    }
}
}  // namespace game
