#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <type_traits>
#include <iostream>
#include "lib/error.h"

using std::filesystem::recursive_directory_iterator;

template<typename T>
class ResourceManager {
public:
    explicit ResourceManager(const std::string &folderPath) {
        for (const auto &entry: recursive_directory_iterator(folderPath)) {
            if (entry.is_regular_file() && entry.path().filename().string()[0] != '.') {
                T new_entry;

                if (new_entry.loadFromFile(entry.path().string())) {
                    std::string filename = entry.path().filename().string();

                    filename = filename.substr(0, filename.find_last_of('.'));
                    if (resources.find(filename) == resources.end()) {
                        resources[filename] = new_entry;
                    } else {
                        exit_with_message(std::string("Error: ")
                                                  .append(filename)
                                                  .append(" already exists in ")
                                                  .append(folderPath));
                    }
                } else {
                    exit_with_message(std::string("Error: ")
                                              .append(entry.path().filename().string())
                                              .append(" could not be loaded from ")
                                              .append(folderPath));
                }
            }
        }
    }

    void remove(const std::string &name) {
        resources.erase(name);
    }

    void add(const std::string &resourcePath) {
        T new_entry;

        if (new_entry.loadFromFile(resourcePath)) {
            resources[resourcePath] = new_entry;
        } else {
            std::cerr << "Failed to load resource: " << resourcePath << std::endl;
        }
    }

    void add(const std::string &name, const T &resource) {
        resources[name] = resource;
    }

    T &get(const std::string &name) const {
        return resources.at(name);
    }

private:
    std::map<std::string, T> resources;
};
