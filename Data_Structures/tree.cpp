#include <iostream>
#include <string>
#include <vector>
#include <utility>   // std::pair
#include <algorithm> // std::find_if



// Stores the customer's choices
struct Sandwich {
    std::string bread;
    std::string size;
    std::string protein;
    std::string cheese;      // empty = none
    std::string sauce;       // empty = none
    bool toasted = false;
};

// One node in the decision tree
struct DecisionNode {
    std::string question;   // text to show the customer
    bool isLeaf = false;    // true when we’re done asking questions

    // For non-leaf nodes:
    //  each option = { answer text, pointer to next node }
    std::vector<std::pair<std::string, DecisionNode*>> options;
};

DecisionNode* buildOrderingTree() {
    // Allocate nodes
    auto* start          = new DecisionNode{"What kind of bread would you like?"};
    auto* chooseSize     = new DecisionNode{"What size sandwich would you like?"};
    auto* hotOrCold      = new DecisionNode{"Hot or cold?"};
    auto* chooseProtein  = new DecisionNode{"What protein would you like?"};
    auto* wantCheese     = new DecisionNode{"Would you like cheese?"};
    auto* chooseCheese   = new DecisionNode{"What kind of cheese?"};
    auto* wantSauce      = new DecisionNode{"Would you like sauce?"};
    auto* chooseSauce    = new DecisionNode{"What kind of sauce?"};
    auto* finish         = new DecisionNode{"Confirming your order...", true};

    // Start: bread options
    start->options = {
        {"White",        chooseSize},
        {"Wheat",        chooseSize},
        {"Italian",      chooseSize},
        {"Gluten-free",  chooseSize}
    };

    // Size
    chooseSize->options = {
        {"6 inch",  hotOrCold},
        {"12 inch", hotOrCold}
    };

    // Hot/Cold
    hotOrCold->options = {
        {"Hot",  chooseProtein},
        {"Cold", chooseProtein}
    };

    // Protein
    chooseProtein->options = {
        {"Turkey", chooseProtein},   // we'll move to cheese afterwards in logic
        {"Ham",    chooseProtein},
        {"Chicken",chooseProtein},
        {"Veggie", chooseProtein}
    };
    // NOTE: we'll special-case moving to wantCheese in the traversal
    // (or you could point all of these directly to wantCheese).

    chooseProtein->options = {   // better: point all to wantCheese
        {"Turkey", wantCheese},
        {"Ham",    wantCheese},
        {"Chicken",wantCheese},
        {"Veggie", wantCheese}
    };

    // Cheese? Yes/No
    wantCheese->options = {
        {"Yes", chooseCheese},
        {"No",  wantSauce}
    };

    // Cheese choices
    chooseCheese->options = {
        {"Swiss",     wantSauce},
        {"Cheddar",   wantSauce},
        {"Provolone", wantSauce}
    };

    // Sauce? Yes/No
    wantSauce->options = {
        {"Yes", chooseSauce},
        {"No",  finish}
    };

    // Sauce choices
    chooseSauce->options = {
        {"Mayo",         finish},
        {"Mustard",      finish},
        {"Special sauce",finish}
    };

    // finish->isLeaf is already true

    return start;  // root of the tree
}

// Helper: find the next node for a given answer text
DecisionNode* findNext(DecisionNode* node, const std::string& answer) {
    for (auto& opt : node->options) {
        if (opt.first == answer) {
            return opt.second;
        }
    }
    return nullptr;
}

void runOrdering(DecisionNode* root, Sandwich& s) {
    DecisionNode* current = root;

    while (current && !current->isLeaf) {
        std::cout << current->question << "\n";

        // Show options
        for (auto& opt : current->options) {
            std::cout << " - " << opt.first << "\n";
        }

        std::string choice;
        std::getline(std::cin, choice);

        // Trim simple trailing \r (Windows) just in case
        if (!choice.empty() && choice.back() == '\r')
            choice.pop_back();

        DecisionNode* next = findNext(current, choice);
        if (!next) {
            std::cout << "Sorry, I didn't understand. Please type one of the options exactly.\n\n";
            continue;
        }

        // Record the choice into the Sandwich based on which question we're at
        if (current->question.find("bread") != std::string::npos) {
            s.bread = choice;
        } else if (current->question.find("size") != std::string::npos) {
            s.size = choice;
        } else if (current->question.find("Hot or cold") != std::string::npos) {
            s.toasted = (choice == "Hot");
        } else if (current->question.find("protein") != std::string::npos) {
            s.protein = choice;
        } else if (current->question.find("cheese?") != std::string::npos) {
            if (choice == "No") s.cheese.clear();
        } else if (current->question.find("kind of cheese") != std::string::npos) {
            s.cheese = choice;
        } else if (current->question.find("sauce?") != std::string::npos) {
            if (choice == "No") s.sauce.clear();
        } else if (current->question.find("kind of sauce") != std::string::npos) {
            s.sauce = choice;
        }

        current = next;
        std::cout << "\n";
    }

    if (current && current->isLeaf) {
        std::cout << "Order complete!\n";
    }
}