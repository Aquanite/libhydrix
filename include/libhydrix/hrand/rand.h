#pragma once
/// @brief The seed for the random number generator
static long int rand_seed = 0;
/// @brief Generate a random number
/// @return The random number
int rand();
/// @brief Set the seed for the random number generator
/// @param seed The seed
void srand(unsigned long int seed);
/// @brief Generate a random number in a range
/// @param min The minimum value
/// @param max The maximum value
/// @return The random number
int rand_range(int min, int max);