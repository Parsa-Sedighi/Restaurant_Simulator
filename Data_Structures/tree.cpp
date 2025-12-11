// Data_Structures/tree.cpp
#include <iostream>
#include "tree.h"
#include "hash.h"   // now Inventory is fully known here
#include "Stack.h"

// helper to find next node
DecisionNode* findNext(DecisionNode* node, const std::string& answer) {
    for (auto& opt : node->options) {
        if (opt.first == answer) {
            return opt.second;
        }
    }
    return nullptr;
}

// Build your ordering tree (example)
DecisionNode* buildOrderingTree() {
    auto* start         = new DecisionNode{"What kind of bread would you like?"};
    auto* chooseSize    = new DecisionNode{"What size sandwich would you like?"};
    auto* hotOrCold     = new DecisionNode{"Hot or cold?"};
    auto* chooseProtein = new DecisionNode{"What protein would you like?"};
    auto* wantCheese    = new DecisionNode{"Would you like cheese?"};
    auto* chooseCheese  = new DecisionNode{"What kind of cheese?"};
    auto* finish        = new DecisionNode{"Confirming your order...", true};

    start->options = {
        {"Italian",     chooseSize},
        {"White",       chooseSize},
        {"Wheat",       chooseSize},
        {"Gluten-free", chooseSize}
    };

    chooseSize->options = {
        {"6 inch",  hotOrCold},
        {"12 inch", hotOrCold}
    };

    hotOrCold->options = {
        {"Hot",  chooseProtein},
        {"Cold", chooseProtein}
    };

    chooseProtein->options = {
        {"turkey", chooseProtein},  // we’ll adjust below
        {"ham",    chooseProtein},
        {"chicken",chooseProtein},
        {"veggie", chooseProtein}
    };

    // better: point all protein choices to wantCheese
    chooseProtein->options = {
        {"turkey", wantCheese},
        {"ham",    wantCheese},
        {"chicken",wantCheese},
        {"veggie", wantCheese}
    };

    wantCheese->options = {
        {"Yes", chooseCheese},
        {"No",  finish}
    };

    chooseCheese->options = {
        {"cheddar",   finish},
        {"swiss",     finish},
        {"provolone", finish}
    };

    // finish->isLeaf = true

    return start;
}

void runOrdering(DecisionNode* root, Sandwich& s, Inventory& containers,Stack& stack ) {
    DecisionNode* current = root;

    while (current && !current->isLeaf) {
        std::cout << current->question << "\n";
        for (auto& opt : current->options) {
            std::cout << " - " << opt.first << "\n";
        }

        std::string choice;
        std::getline(std::cin, choice);
        if (!choice.empty() && choice.back() == '\r')
            choice.pop_back();

        DecisionNode* next = findNext(current, choice);
        if (!next) {
            std::cout << "Invalid choice. Try again.\n\n";
            continue;
        }

        // Update Sandwich based on question
        if (current->question.find("bread") != std::string::npos) {
            s.bread = choice;
        } else if (current->question.find("size") != std::string::npos) {
            s.size = choice;
        } else if (current->question.find("Hot or cold") != std::string::npos) {
            s.toasted = (choice == "Hot");
        } else if (current->question.find("protein") != std::string::npos) {
            s.protein = choice;
        } else if (current->question.find("kind of cheese") != std::string::npos) {
            s.cheese = choice;
        }
        if(containers.use(choice)){
            stack.push(choice);
            stack.print();
        }
        containers.print();
        current = next;
        std::cout << "\n";
    }

    if (current && current->isLeaf) {
        std::cout << "Order complete!\n";
        // You can now optionally check inventory here using containers
        // e.g. containers.use(s.protein, 1);
    }
}