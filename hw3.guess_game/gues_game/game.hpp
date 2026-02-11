#pragma once
#include <string.h>

#include <fstream>

namespace game
{
constexpr int                NAME_SIZE      = 32;
inline constexpr const char* WINNER_TABLE_F = "winners.db";

#pragma pack(1)  // to avoid memory alligment;
// Implements user record;
struct UserEntry
{
    char username[NAME_SIZE];
    int  score;
};
#pragma pack()

// Returns random integer in provided range.
// default [0..100]
int generate_random_number (int min, int max);

// provides interactive dialig to get username.
std::string init_user ();

// Provides interactive communication for player.
int guess_game (int max_value);

// validates that provied file exist.
// if @param create true will create new file.
bool validate_top_table_exist (bool create);

// writes winner record to WINNER_TABLE_F.
// Updates record if it exist.
void write_new_winner (std::string name, int attempts);

// print winners table.
void print_winners ();

}  // namespace game
