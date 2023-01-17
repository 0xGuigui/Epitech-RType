#pragma once

#include <string>
#include <iostream>
#include <utility>

void exit_with_message(const std::string &message, int code = 1);

class RTypeError : public std::exception {
private:
    const std::string _message;

public:
    explicit RTypeError(std::string message) : _message(std::move(message)) {};

    [[maybe_unused]] explicit RTypeError(const char *message) : _message(std::string(message)) {};

    [[nodiscard]] const char *what() const noexcept override;
};

class KeyboardError : RTypeError {
public:
    explicit KeyboardError(std::string message) : RTypeError(std::move(message)) {};
};
