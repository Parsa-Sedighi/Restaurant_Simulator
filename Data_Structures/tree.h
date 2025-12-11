// Data_Structures/tree.h
#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include <utility>

struct Inventory;
class Stack;

// Now with veggies chosen by user
struct Sandwich {
    std::string bread;
    std::string protein;
    std::string cheese;
    std::vector<std::string> veggies; // e.g. "lettuce", "tomato", "onion"
};

struct DecisionNode {
    std::string question;
    bool isLeaf = false;
    std::vector<std::pair<std::string, DecisionNode*> > options;
};

DecisionNode* buildOrderingTree();

void runOrdering(DecisionNode* root,
                 Sandwich& s,
                 Inventory& containers,
                 Stack& stack);

#endif // TREE_H