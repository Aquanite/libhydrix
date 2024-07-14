#pragma once
/// @brief The seed for the random number generator
static long int rand_seed = 0;
/// @brief Generate a random number
/// @return The random number
int Random();
/// @brief Set the seed for the random number generator
/// @param seed The seed
void SetRandomSeed(unsigned long int seed);
/// @brief Generate a random number in a range
/// @param Minimum The Minimumimum value
/// @param Maximum The Maximumimum value
/// @return The random number
int RandomWithRange(int Minimum, int Maximum);