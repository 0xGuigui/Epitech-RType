#include "lib/error.h"

void exit_with_message(const std::string &message, int code) {
    std::cerr << message << std::endl;
    exit(code);
}
