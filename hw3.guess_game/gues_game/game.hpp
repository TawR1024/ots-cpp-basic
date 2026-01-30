#pragma once
#include <vector>
#include <string.h>
#include <fstream>

namespace game
{
inline constexpr const char* WINNER_TABLE_F = "winners.txt";

// Returns random integer in provided range;
int generate_random_number (int min, int max);

// Provides interactive communication for player.
void guess_game ();

// Check that winner table file exists. If not cretes the new one.
bool init_winner_table();

// void write_new_winner([ name, u_int attempts);

}  // namespace game
