// Data_Structures/hash.cpp
#include "hash.h"


Inventory::Inventory() {
    // initial stock
    items["Italian"]   = 1;
    items["White"]     = 1;
    items["Wheat"]     = 1;
    items["turkey"]    = 1;
    items["ham"]       = 1;
    items["chicken"]   = 1;
    items["cheddar"]   = 1;
    items["swiss"]     = 1;
    items["provolone"] = 1;
    items["lettuce"]   = 1;
    items["tomato"]    = 1;
    items["onion"]     = 1;
    items["mayo"]      = 1;
    items["mustard"]   = 1;
    items["special sauce"] = 5;
}

void Inventory::restock(const std::string& name, int amount) {
    items[name] += amount;
}

bool Inventory::has(const std::string& name, int amount) const {
    auto it = items.find(name);
    return it != items.end() && it->second >= amount;
}

bool Inventory::use(const std::string& name) {
    auto it = items.find(name);
    if (it == items.end()) {
        std::cout << "No " << name << " in inventory.\n";
        return false;
    }
    //if (it->second < amount) {
    //    std::cout << "Not enough " << name << " (have "
    //              << it->second << ", need " << amount << ").\n";
    //    return false;
    //}
    it->second -= 1;
    return true;
}

void Inventory::print() const {
    std::cout << "--- Inventory ---\n";
    for (const auto& pair : items) {
        const std::string& name = pair.first;
        int count               = pair.second;
        std::cout << name << ": " << count << "\n";
    }
}


