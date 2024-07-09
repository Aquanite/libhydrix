#include <libhydrix/hrand/rand.h>

int rand() {
    rand_seed = rand_seed * 1103515245 + 12345;
    return (unsigned long int)(rand_seed / 65536) % 32768;
}
void srand(unsigned long int seed) {
    rand_seed = seed;
}
int rand_range(int min, int max) {
    return rand() % (max - min) + min;
}