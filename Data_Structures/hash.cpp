// Data_Structures/hash.cpp
#include "hash.h"


Inventory::Inventory() {
    // initial stock
    items["Italian"]   = 10;
    items["White"]     = 10;
    items["Wheat"]     = 10;
    items["turkey"]    = 20;
    items["ham"]       = 20;
    items["chicken"]   = 20;
    items["cheddar"]   = 15;
    items["swiss"]     = 15;
    items["provolone"] = 15;
    items["lettuce"]   = 30;
    items["tomato"]    = 30;
    items["onion"]     = 30;
    items["mayo"]      = 10;
    items["mustard"]   = 10;
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

void drawToScene(QGraphicsScene* scene, int startX, int startY, int width, int heightPerItem) const{
    
}
