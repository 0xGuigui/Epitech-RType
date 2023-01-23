#pragma once

#include <string>

class Identifiable {
private:
    std::string _id;
public:
    Identifiable();

    [[maybe_unused]] const std::string &getId();

    bool operator == (const Identifiable &identifiable);

    bool operator != (const Identifiable &identifiable);

    virtual ~Identifiable() = default;
};
