#include "lib/random.h"

unsigned int Random::generate() {
    static std::mt19937 generator;
    static bool first = true;

    if (first) {
        generator.seed(0);
        first = false;
    }
    return generator();
}
