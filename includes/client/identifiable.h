#pragma once

#include <string>

class Identifiable {
private:
    std::string _id;
public:
    Identifiable();

    [[nodiscard]] const std::string &getId() const;

    bool operator == (const Identifiable &identifiable) const;

    bool operator != (const Identifiable &identifiable) const;

    virtual ~Identifiable() = default;
};
