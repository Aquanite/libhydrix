#include <libhydrix/hrand/rand.h>

int Random() {
    rand_seed = rand_seed * 1103515245 + 12345;
    return (unsigned long int)(rand_seed / 65536) % 32768;
}
void SetRandomSeed(unsigned long int seed) {
    rand_seed = seed;
}
int RandomWithRange(int Minimum, int Maximum) {
    return Random() % (Maximum - Minimum) + Minimum;
}