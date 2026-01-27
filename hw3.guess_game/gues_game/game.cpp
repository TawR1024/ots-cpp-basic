#include <iostream>
#include <random>

namespace game
{
int generate_randon_number (int min, int max)
{
    std::random_device              rd;
    std::mt19937                    gen (rd ());
    std::uniform_int_distribution<> dis (min, max);

    return dis (gen);
}

void guess_game ()
{
    std::cout << "Let's the game begin!" << std::endl;

    // prepare random num
    int hidden_number = generate_randon_number (1, 100);
    int user_choice;
    while (true)
    {
        std::cout << "Enter your nuber:";
        std::cin >> user_choice;

        if (user_choice == hidden_number)
        {
            std::cout << "You are winner !" << std::endl;
            break;
        }
        else if (user_choice < hidden_number)
        {
            std::cout << "Too low, try again !" << std::endl;
        }
        else
        {
            std::cout << "Too high, try again !" << std::endl;
        }
    }
}
}  // namespace game
