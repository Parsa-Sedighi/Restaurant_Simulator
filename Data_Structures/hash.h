// Data_Structures/hash.h
#ifndef HASH_H
#define HASH_H

#include <unordered_map>
#include <string>
#include <iostream>

struct Inventory {
    std::unordered_map<std::string, int> items;

    Inventory();  // defined in hash.cpp

    void restock(const std::string& name, int amount);
    bool has(const std::string& name, int amount = 1) const;
    bool use(const std::string& name);
    void print() const;
};

#endif // HASH_H