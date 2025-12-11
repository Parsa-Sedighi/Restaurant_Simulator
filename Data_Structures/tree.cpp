#include <iostream>
#include "tree.h"
#include "hash.h"
#include "Stack.h"

static DecisionNode* findNext(DecisionNode* node, const std::string& answer) {
    for (std::size_t i = 0; i < node->options.size(); ++i) {
        if (node->options[i].first == answer) {
            return node->options[i].second;
        }
    }
    return 0;
}

DecisionNode* buildOrderingTree() {
    // Allocate nodes
    DecisionNode* start         = new DecisionNode();
    DecisionNode* chooseProtein = new DecisionNode();
    DecisionNode* wantCheese    = new DecisionNode();
    DecisionNode* chooseCheese  = new DecisionNode();
    DecisionNode* askLettuce    = new DecisionNode();
    DecisionNode* askTomato     = new DecisionNode();
    DecisionNode* askOnion      = new DecisionNode();
    DecisionNode* finish        = new DecisionNode();

    start->question         = "What kind of bread would you like?";
    chooseProtein->question = "What protein would you like?";
    wantCheese->question    = "Would you like cheese?";
    chooseCheese->question  = "What kind of cheese?";
    askLettuce->question    = "Add lettuce? (Yes/No)";
    askTomato->question     = "Add tomato? (Yes/No)";
    askOnion->question      = "Add onion? (Yes/No)";
    finish->question        = "Confirming your order...";
    finish->isLeaf          = true;

    // Bread options → protein
    start->options.push_back(std::make_pair(std::string("italian"),     chooseProtein));
    start->options.push_back(std::make_pair(std::string("white"),       chooseProtein));
    start->options.push_back(std::make_pair(std::string("wheat"),       chooseProtein));

    // Protein options → wantCheese
    chooseProtein->options.push_back(std::make_pair(std::string("turkey"),  wantCheese));
    chooseProtein->options.push_back(std::make_pair(std::string("ham"),     wantCheese));
    chooseProtein->options.push_back(std::make_pair(std::string("chicken"), wantCheese));
    chooseProtein->options.push_back(std::make_pair(std::string("veggie"),  wantCheese));

    // Cheese? Yes → chooseCheese, No → veggie questions
    wantCheese->options.push_back(std::make_pair(std::string("Yes"), chooseCheese));
    wantCheese->options.push_back(std::make_pair(std::string("No"),  askLettuce));

    // Cheese type → veggie questions
    chooseCheese->options.push_back(std::make_pair(std::string("cheddar"),   askLettuce));
    chooseCheese->options.push_back(std::make_pair(std::string("swiss"),     askLettuce));
    chooseCheese->options.push_back(std::make_pair(std::string("provolone"), askLettuce));

    // Veggie chain: lettuce → tomato → onion → finish
    askLettuce->options.push_back(std::make_pair(std::string("Yes"), askTomato));
    askLettuce->options.push_back(std::make_pair(std::string("No"),  askTomato));

    askTomato->options.push_back(std::make_pair(std::string("Yes"), askOnion));
    askTomato->options.push_back(std::make_pair(std::string("No"),  askOnion));

    askOnion->options.push_back(std::make_pair(std::string("Yes"), finish));
    askOnion->options.push_back(std::make_pair(std::string("No"),  finish));

    return start;
}

void runOrdering(DecisionNode* root,
                 Sandwich& s,
                 Inventory& /*containers*/,
                 Stack& stack)
{
    DecisionNode* current = root;

    while (current && !current->isLeaf) {
        std::cout << current->question << "\n";

        for (std::size_t i = 0; i < current->options.size(); ++i) {
            std::cout << " - " << current->options[i].first << "\n";
        }

        std::string choice;
        std::getline(std::cin, choice);
        if (!choice.empty() && choice[choice.size() - 1] == '\r') {
            choice.erase(choice.size() - 1);
        }

        DecisionNode* next = findNext(current, choice);
        if (!next) {
            std::cout << "Invalid choice. Please type one of the options exactly.\n\n";
            continue;
        }

        // Record choices
        const std::string& q = current->question;

        if (q.find("bread") != std::string::npos) {
            s.bread = choice;
            stack.push(choice);
        }
        else if (q.find("protein") != std::string::npos) {
            s.protein = choice;
            stack.push(choice);
        }
        else if (q.find("What kind of cheese") != std::string::npos) {
            s.cheese = choice;
            stack.push(choice);
        }
        else if (q.find("Add lettuce") != std::string::npos) {
            if (choice == "Yes" || choice == "yes") {
                s.veggies.push_back("lettuce");
                stack.push("lettuce");
            }
        }
        else if (q.find("Add tomato") != std::string::npos) {
            if (choice == "Yes" || choice == "yes") {
                s.veggies.push_back("tomato");
                stack.push("tomato");
            }
        }
        else if (q.find("Add onion") != std::string::npos) {
            if (choice == "Yes" || choice == "yes") {
                s.veggies.push_back("onion");
                stack.push("onion");
            }
        }

        current = next;
        std::cout << "\n";
    }

    if (current && current->isLeaf) {
        std::cout << "Order complete!\n";
    }
}