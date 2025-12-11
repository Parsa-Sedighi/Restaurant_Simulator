// Data_Structures/tree.h
#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include <utility>

// Forward declare Inventory so we can use Inventory& in function signatures
struct Inventory;
class Stack;   // 👈 this fixes "unknown type name 'Stack'"

// Sandwich the customer is ordering
struct Sandwich {
    std::string bread;
    std::string size;
    std::string protein;
    std::string cheese;
    std::vector<std::string> veggies;
    std::vector<std::string> sauces;
    bool toasted = false;
};

// One node in the decision tree
struct DecisionNode {
    std::string question;
    bool isLeaf = false;
    std::vector<std::pair<std::string, DecisionNode*>> options;
};

// Build the decision tree (you define this in tree.cpp)
DecisionNode* buildOrderingTree();

// Run the ordering process and fill Sandwich s, possibly using Inventory
void runOrdering(DecisionNode* root, Sandwich& s, Inventory& containers, Stack& stack);

#endif // TREE_H