// main.cpp
#include <iostream>
#include "Data_Structures/tree.h"
#include "Data_Structures/hash.h"
#include "Data_Structures/Stack.h"

int main() {

    Inventory containers;     // pre-filled in Inventory constructor
    Sandwich s;
    Stack stack;
    DecisionNode* root = buildOrderingTree();

    runOrdering(root, s, containers, stack);

    std::cout << "\n--- Your Sandwich ---\n";
    std::cout << s.size << " " << s.bread << " sandwich\n";
    std::cout << "Protein: " << s.protein << "\n";
    std::cout << "Toasted: " << (s.toasted ? "Yes" : "No") << "\n";
    std::cout << "Cheese: " << (s.cheese.empty() ? "None" : s.cheese) << "\n";

    std::cout << "\nInventory after (unchanged here, unless you call use() inside runOrdering):\n";
    containers.print();

    return 0;
}