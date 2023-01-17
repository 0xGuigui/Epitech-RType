#include "lib/error.h"

void exit_with_message(const std::string &message, int code) {
    std::cerr << message << std::endl;
    exit(code);
}

[[nodiscard]] const char *RTypeError::what() const noexcept {
    return _message.c_str();
}
