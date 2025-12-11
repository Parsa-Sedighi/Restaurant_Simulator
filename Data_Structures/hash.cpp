// Data_Structures/hash.cpp
#include "hash.h"


Inventory::Inventory() {
    // initial stock
    items["italian"]   = 2;
    items["white"]     = 2;
    items["wheat"]     = 2;
    items["turkey"]    = 1;
    items["ham"]       = 1;
    items["chicken"]   = 1;
    items["cheddar"]   = 1;
    items["swiss"]     = 1;
    items["provolone"] = 1;
    items["lettuce"]   = 4;
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
    // Categories: 0 = Bread, 1 = Protein, 2 = Cheese, 3 = Veggie, 4 = Other/Sauce
    const int NUM_CATS = 5;
    std::vector<std::string> columns[NUM_CATS];

    // Helper: to-lowercase copy
    auto toLower = [](const std::string& s) -> std::string {
        std::string out;
        out.reserve(s.size());
        for (std::size_t i = 0; i < s.size(); ++i) {
            unsigned char ch = static_cast<unsigned char>(s[i]);
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
        return out;
    };

    // Classify each ingredient into a category
    for (std::unordered_map<std::string,int>::const_iterator it = items.begin();
         it != items.end(); ++it)
    {
        const std::string& name = it->first;
        int count = it->second;

        std::string label     = name + " (" + std::to_string(count) + ")";
        std::string lname     = toLower(name);  // lowercased for comparison
        int cat               = 4;              // default = Other/Sauce

        // Bread
        if (lname == "italian" || lname == "white" || lname == "wheat") {
            cat = 0;
        }
        // Protein
        else if (lname == "turkey" || lname == "ham" ||
                 lname == "chicken" || lname == "veggie") {
            cat = 1;
        }
        // Cheese
        else if (lname == "cheddar" || lname == "swiss" || lname == "provolone") {
            cat = 2;
        }
        // Veggies
        else if (lname == "lettuce" || lname == "tomato" ||
                 lname == "onion"   || lname == "pickle") {
            cat = 3;
        }
        // Sauces / others stay in cat = 4

        columns[cat].push_back(label);
    }

    // Check if everything is empty
    bool any = false;
    for (int c = 0; c < NUM_CATS; ++c) {
        if (!columns[c].empty()) {
            any = true;
            break;
        }
    }
    if (!any) {
        std::cout << "--- Inventory: empty ---\n";
        return;
    }

    std::cout << "--- Available ingredients (grouped by category) ---\n";

    const std::string catNames[NUM_CATS] = {
        "Bread", "Protein", "Cheese", "Veggies", "Other"
    };

    const std::size_t boxInnerWidth = 16;   // width inside each box
    const std::size_t totalCols     = NUM_CATS;

    // Header row with category names aligned over columns
    {
        std::string header;
        for (std::size_t c = 0; c < totalCols; ++c) {
            std::string name = catNames[c];
            if (name.size() > boxInnerWidth) {
                name = name.substr(0, boxInnerWidth);
            }
            if (name.size() < boxInnerWidth) {
                name += std::string(boxInnerWidth - name.size(), ' ');
            }
            header += " " + name + "   ";
        }
        std::cout << header << "\n\n";
    }

    // Max number of rows among categories
    std::size_t maxRows = 0;
    for (int c = 0; c < NUM_CATS; ++c) {
        if (columns[c].size() > maxRows) {
            maxRows = columns[c].size();
        }
    }

    // Print row by row: each row has up to NUM_CATS boxes (one per category)
    for (std::size_t row = 0; row < maxRows; ++row) {
        std::string topRow;
        std::string midRow;
        std::string botRow;

        for (int c = 0; c < NUM_CATS; ++c) {
            if (row < columns[c].size()) {
                const std::string& text = columns[c][row];

                // Top border
                topRow += "+" + std::string(boxInnerWidth, '-') + "+  ";

                // Middle text
                std::string inner = text;
                if (inner.size() > boxInnerWidth) {
                    inner = inner.substr(0, boxInnerWidth);
                } else if (inner.size() < boxInnerWidth) {
                    inner += std::string(boxInnerWidth - inner.size(), ' ');
                }
                midRow += "|" + inner + "|  ";

                // Bottom border
                botRow += "+" + std::string(boxInnerWidth, '-') + "+  ";
            } else {
                // No item in this category at this row → print blank space of same width
                std::size_t blankWidth = boxInnerWidth + 4; // "+ .. +  " total
                topRow += std::string(blankWidth, ' ');
                midRow += std::string(blankWidth, ' ');
                botRow += std::string(blankWidth, ' ');
            }
        }

        std::cout << topRow << "\n";
        std::cout << midRow << "\n";
        std::cout << botRow << "\n\n";
    }
}