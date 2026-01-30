#include "game.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
namespace game
{
int generate_random_number (int min, int max)
{
    std::random_device              rd;
    std::mt19937                    gen (rd ());
    std::uniform_int_distribution<> dis (min, max);

    return dis (gen);
}

void write_new_winner (std::string name, int attempts)
{
    std::fstream winners (WINNER_TABLE_F, std::ios::in | std::ios::out | std::ios::binary);
    if (!winners.is_open ())
    {
        std::cout << "Failed to open file for write: " << WINNER_TABLE_F << "!" << std::endl;
        return;
    }

    UserEntry user{};
    std::strncpy (user.username, name.c_str (), NAME_SIZE - 1);
    user.username[NAME_SIZE - 1] = '\0';
    user.score                   = attempts;

    // try to find user in file.
    // append new record if not exist, update otherwise.
    int       record_size = sizeof (UserEntry);
    char      buffer[record_size];
    int       cursor_p = 0;
    UserEntry rec;
    while (winners.read (buffer, record_size))
    {
        std::memcpy (&rec, buffer, record_size);  // read record to buffer;
        if (strcmp (rec.username, user.username) == 0)
        {
            rec.score = user.score;  // update attempts;

            winners.seekp (cursor_p);  // move cursor to stat of record;
            std::memcpy (buffer, &rec, record_size);
            winners.write (buffer, record_size);  // rewrite current record;
            winners.close ();
            return;
        }
        cursor_p += record_size;
    }

    // uppend file if record does not exists;
    winners.seekp (0, std::ios::end);  // move cursor to the end of file;

    std::memcpy (buffer, &user, sizeof (UserEntry));

    winners.write (buffer, sizeof (UserEntry));

    winners.close ();
}

void print_winners ()
{
    std::ifstream file (WINNER_TABLE_F, std::ios::binary);
    if (!file.is_open ())
    {
        std::cout << "Failed to open file for reading: " << WINNER_TABLE_F << "!" << std::endl;
        return;
    }

    const int record_size = sizeof (UserEntry);
    char      buffer[record_size];

    while (file.read (buffer, record_size))
    {
        UserEntry rec;
        std::memcpy (&rec, buffer, record_size);

        std::cout << rec.username << " " << rec.score << std::endl;
    }

    file.close ();
}

std::string init_user ()
{
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::string user_name;
    std::cin >> user_name;

    return user_name;
}

int guess_game (int max_value)
{
    std::cout << "Let's the game begin!" << std::endl;

    // prepare random num
    int hidden_number = generate_random_number (0, max_value);
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

    return attempts;
}

}  // namespace game
